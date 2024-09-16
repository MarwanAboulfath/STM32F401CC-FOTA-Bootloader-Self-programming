
/*****************************************************/
/*					FILES INCLUSIONS				 */
/*****************************************************/

/************************LIB**************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/ARM_Delay.h"
/************************MCAL*************************/
#include "../include/MCAL/MRCC/MRCC_Interface.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"
#include "../include/MCAL/MNVIC/MNVIC_Interface.h"
#include "../include/MCAL/MFDI/MFDI_Interface.h"
#include "../include/MCAL/MUSART/USART_INTERFACE.h"
/************************HAL**************************/
#include "../include/HAL/HESP/ESP8266_INTERFACE.h"
/************************APP**************************/
#include "../include/APP/AHEXAPARSING/AHEXAPARSING_Interface.h"
/************************************************************************/
/*							ENTRY POINT <main>							*/
/************************************************************************/
/************************** MACROS DEFENITION ***************************/
#define CURRENT_VERSION_ADDRESS 			0x08004000
#define CURRENT_VERSION_NUMBER 				*((volatile u16*)CURRENT_VERSION_ADDRESS)
#define APP_SECTOR_FIRST_LOCATION_ADDRESS 	0x08008000
#define APP_SECTOR_FIRST_LOCATION			*((volatile u32*)APP_SECTOR_FIRST_LOCATION_ADDRESS)

/*************************** GLOBAL VARIABLES ****************************/
volatile u8 u8WriteReq = 1  ;
volatile u8 Glob_u8EndOfFile = 0 ;
volatile u8 RecordReady = 0;
volatile u8 UpdateVersion = 0;
volatile u16 Online_Version = 0;


typedef void (*APP_Call)(void) ;
APP_Call Add_to_Called=0;

/* FUNCTIONS DEFENITION */
void App_voidToBurn(void);
void MUSART_CallBack ( void );
void Fota_CheckForUpdate(void);
void Fota_Update(void);



/************************************************************************/
/*							ENTRY POINT <main>							*/
/************************************************************************/
void main(void)
{

	/***********************Clock initialization*************************/
	/* Initialize RCC */
	MRCC_voidInit();
	MRCC_voidEnablePeripheral(AHB1_LP,RCC_AHB1__LP_FDI);//FDI
	MRCC_voidEnablePeripheral(RCC_APB2,RCC_APB2_USART1);//UART
	MRCC_voidEnablePeripheral(RCC_AHB1,RCC_AHB1_GPIOA);//GPIOA
	/* Configure UART pins  */
	MGPIO_voidSetPinMode(GPIO_PORTA,GPIO_PIN9,GPIO_ALT_FUNC);
	MGPIO_voidSetPinMode(GPIO_PORTA,GPIO_PIN10,GPIO_ALT_FUNC);
	//Enable Alternative Line for UART1 pins
	MGPIO_voidSetAF(GPIO_PORTA,GPIO_PIN9,7);
	MGPIO_voidSetAF(GPIO_PORTA,GPIO_PIN10,7);
	/* Configure Led pins */
	MGPIO_voidSetPinMode(GPIO_PORTA,GPIO_PIN0,GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA,GPIO_PIN4,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA,GPIO_PIN0,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA,GPIO_PIN4,GPIO_PUSH_PULL,GPIO_MEDIUM_SPEED);
	//Indicate execution of BootLoader Section in Flash
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_HIGH);

	/* Set USART1 CallBack To Receive The Response Of The ESP8266 */
	MUSART1_VidSetCallBack( MUSART_CallBack );

	/* Enable NVIC For USART1 */
	MNVIC_voidEnablePeripheralInterrupt(USART1_IRQ);

	/* Initialize UART */
	MUSART_VidInit();
	/* Initialize ESP8266 */
	ESP8266_VidInit();

	/* Reset version Current version value first time only in Flash memory (When no application version is Flashed) */
	if (CURRENT_VERSION_NUMBER == 0xFFFF)
	{
		MFDI_voidWrite(CURRENT_VERSION_ADDRESS, (u16*)&Online_Version, 1);
	}

	/* Connect To WIFI Network */
	ESP8266_VidConnectToWiFi((u8*)"DESKTOP-3BBBL7U3833",(u8*)"033t34OR");

	/*********************************** CHECK FOR VERSION UPDATE ON SERVER ******************************************/

	Fota_CheckForUpdate();

	/******************************* DOWNLOAD AND FLASH NEW SOFTWARE ON FLASH MEMORY *********************************/
	Fota_Update();

	/* Call/Jump to application */
	Delay_MS(1);
	/* Flash memory application sector contains data or erased */
	if(APP_SECTOR_FIRST_LOCATION != 0xFFFFFFFF)
	{
		Delay_MS(1);
		App_voidToBurn();
	}
	/* Application sector is erased contains no application */
	else
	{
		/* DO NOTHING */
	}

}



/***** Functions Implementation ********/
/* Jump to application function */
void App_voidToBurn(void)
{
	/* Switch off boot-loader Leds */
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN4,GPIO_PIN_LOW);
	//move vector table
#define SCB_VTOR    *((volatile u32*)0xE000ED08)
	SCB_VTOR=0x08008000;  //Starting from sector2 in flash
	Add_to_Called=*(APP_Call*)0x08008004;//Address of Reset Handler
	Add_to_Called();
}

/* UART call back function to handle received data from server(ESP8266) */
void MUSART_CallBack ( void ){

	static u8 IPDFlag = 0;
	static u8 CheckRecord = 0;

	/* Data buffer to store data received */
	DataCome[ Iterator ] = MUSART1_u8ReadDataRegister();

	/* Handle Data ESP8266 replies other than Hex file records or versions ("OK", "Connected", "FAILED", etc...) */
	if(DataCome[ Iterator ] == '\n' && HexFileReceiveStarted != 1 && GettingVersion != 1)
	{
		Iterator = 0;
	}
	/* Handle "+IPDx,y:" written before reception of data */
	else if(DataCome[ Iterator ] == '+')
	{
		IPDFlag = 1;
	}
	/* Handle "+IPDx,y:" written before reception of data */
	else if(IPDFlag == 1 && DataCome[ Iterator ] != ':')
	{
		/* Do nothing */
	}
	/* Handle "+IPDx,y:" written before reception of data */
	else if(DataCome[ Iterator ] == ':' && IPDFlag == 1)
	{
		IPDFlag = 0;
		/* Handle case of incomplete record because of "+IPDx,y:" sent in the middle of sending a record */
		if(CheckRecord == 1)
		{
			Iterator -= 1;
			CheckRecord = 0;
		}
	}
	/* Handle receiving a version number string */
	else if(GettingVersion == 1 && DataCome[ Iterator ] == '\n')
	{
		Iterator = 0;
	}
	/* Handle receiving a version number string */
	else if(GettingVersion == 1 && DataCome[ Iterator ] == 'C')
	{
		GettingVersion = 0;

	}
	/* Handle data sent before records ("SEND OK", "busy", etc....") */
	else if(DataCome[ Iterator ] == '\n' && DataCome[ 0 ] != ':' && HexFileReceiveStarted == 1)
	{
		Iterator = 0;
		ESP8266_VidClearBuffer();
	}
	/* Handle receiving of a full record */
	else if(DataCome[ 0 ] == ':' && DataCome[ Iterator ] == '\n' && HexFileReceiveStarted == 1)
	{
		/* set check record flag */
		CheckRecord = 1;
	}
	/* Check if a record is full and complete or not */
	else if(CheckRecord == 1 && (DataCome[ Iterator ] == ':' || DataCome[ Iterator ] == 'C'))
	{
		/* Clear check record flag */
		CheckRecord = 0;
		DataCome[ Iterator ] = '\n';
		Iterator = 1;
		/* Set record ready flag */
		RecordReady = 1;
	}
	/* Check for case of incomplete record due to "+IPDx,y:" */
	else if(CheckRecord == 1 && DataCome[ Iterator ] == '+')
	{
		/* Set Ipd flag */
		IPDFlag = 1;
	}
	/* Data is still incomplete increment iterator */
	else
	{
		Iterator++;
	}

	/* Clear flags */
	MUSART1_VidClearFlags();

}

/* Function to Check for version on server and compare with current version */
void Fota_CheckForUpdate(void)
{
	/* Connecting To SERVER    marwan1.atwebpages.com/ */
	ESP8266_VidConnectToSrvTcp((u8*)"185.176.43.108",(u8*)"80");
	/* Delay until connection to server is established */
	Delay_MS(2000);
	/* Receiving Version information from server */
	Online_Version = ESP8266_u8ReceiveHttpReqVersion((u8*)"marwan1.atwebpages.com", (u8*)"/Version.txt",(u8*)"47");

	/* Check if software version value on server is newer than current software version */
	if (Online_Version > CURRENT_VERSION_NUMBER)
	{
		MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN4,GPIO_PIN_HIGH);
		/* Set update version Flag */
		UpdateVersion = 1;
	}
}

/* Function to Update version in case an update is available */
void Fota_Update(void)
{
	/* Check if Update version is required to download and flash the new software version */
	if(UpdateVersion == 1)
	{

		Delay_MS(1000);

		/* Connecting To SERVER    marwan1.atwebpages.com/ */
		ESP8266_VidConnectToSrvTcp((u8*)"185.176.43.108",(u8*)"80");
		/* Delay until connection to server is established */
		Delay_MS(2000);

		/* Erase the application sector from Flash before receiving the new Hex file */
		if(u8WriteReq==1)
		{
			//Erase Application area
			MFDI_voidEraseAppSector();
			u8WriteReq=0;
		}

		/* Connecting receive data from SERVER marwan1.atwebpages.com / Start receiving of HEX file */
		ESP8266_u8ReceiveHttpReq((u8*)"marwan1.atwebpages.com",(u8*)"/Application.hex",(u8*)"52");

		while(Glob_u8EndOfFile != 1 )
		{
			MGPIO_voidSetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_PIN_HIGH);

			/* Check if record is ready to be Flashed on Flash memory */
			if(RecordReady == 1)
			{
				/* Clear record ready flag to be ready for next record */
				RecordReady = 0;
				/* Send Record string to be parsed and flashed to flash memory */
				Glob_u8EndOfFile = Hexa_voidParseRecord((u8*)&DataCome);

				/* Indicate End of Hex File received */
				if(Glob_u8EndOfFile == 1)
				{
					/* Clear Receiving Hex file flag */
					HexFileReceiveStarted = 0;
					/* Update value of Current version in Flash memory */
					MFDI_voidWrite(CURRENT_VERSION_ADDRESS, (u16*)&Online_Version, 1);
					/* Clear Update version flag to be ready for next update*/
					UpdateVersion = 0;

				}
			}
		}
	}
}



