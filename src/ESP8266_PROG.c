
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/ARM_Delay.h"
#include "../include/MCAL/MUSART/USART_INTERFACE.h"
#include "../include/HAL/HESP/ESP8266_INTERFACE.h"

u8 volatile Iterator = 0  ;
u8 volatile DataCome[200] ;

u8 HexFileReceiveStarted = 0;
u8 GettingVersion = 0;



void ESP8266_VidInit ( void ){



	MUSART1_VidSendStringSynch( (u8 *)"ATE0\r\n" );

	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	MUSART1_VidSendStringSynch( (u8 *)"AT\r\n" );



	Delay_MS( 3000 );

	/* Clear ESP8266 Buffer */
	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *)"AT+CWMODE=3\r\n" );
	Delay_MS( 3000 );

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *)"AT+CIPMODE=0\r\n" );
	Delay_MS( 3000 );

}

void ESP8266_VidConnectToWiFi ( u8 * SSID , u8 * Password ){

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "AT+CWJAP=\"" );
	MUSART1_VidSendStringSynch( (u8 *) SSID );
	MUSART1_VidSendStringSynch( (u8 *) "\",\"" );
	MUSART1_VidSendStringSynch( (u8 *) Password);
	MUSART1_VidSendStringSynch( (u8 *) "\"\r\n");
	Delay_MS( 8000 );

}


void ESP8266_VidConnectToSrvTcp ( u8 * Copy_u8Domain , u8 * Copy_u8Port ){

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "AT+CIPSTART=\"TCP\",\"" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8Domain );
	MUSART1_VidSendStringSynch( (u8 *) "\"," );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8Port );
	MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
//	Delay_MS( 2000 );

}

void ESP8266_VidSendHttpReq( u8 * Copy_u8Key , u8 * Copy_u8Data , u8 * Copy_u8Length ){

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "AT+CIPSEND=" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8Length );
	MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
	Delay_MS( 4000 );

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "GET /update?api_key=" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8Key );
	MUSART1_VidSendStringSynch( (u8 *) "&field1=" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8Data );
	MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
	Delay_MS( 20000 );

}

void   ESP8266_u8ReceiveHttpReq(  u8* Copy_u8ChannelID , u8* Copy_u8ptrFilePath, u8* Copy_u8Length ){

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "AT+CIPSEND=" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8Length );
	MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
	Delay_MS( 4000 );

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "GET http://" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8ChannelID );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8ptrFilePath );
	MUSART1_VidSendStringSynch( (u8 *) "\r\n" );



	HexFileReceiveStarted = 1;


	//Delay_MS( 2000 );

	ESP8266_VidConnectToSrvTcp( (u8 *)"185.176.43.108" , (u8 *)"80" );

	/*For yrabiot3.freevar.com ( Value Array Index )*/
	//return DataCome [31] ;

}

u16   ESP8266_u8ReceiveHttpReqVersion( u8 * Copy_u8ChannelID , u8 * Copy_u8ptrFilePath, u8 * Copy_u8Length ){

	u16 version_number = 0;
	u8 i = 0;

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "AT+CIPSEND=" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8Length );
	MUSART1_VidSendStringSynch( (u8 *) "\r\n" );
	Delay_MS( 4000 );

	ESP8266_VidClearBuffer();

	MUSART1_VidSendStringSynch( (u8 *) "GET http://" );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8ChannelID );
	MUSART1_VidSendStringSynch( (u8 *) Copy_u8ptrFilePath );
	MUSART1_VidSendStringSynch( (u8 *) "\r\n" );

	GettingVersion = 1;

//	MUSART1_VidSendStringSynch( (u8 *) "/ARM_DRIVERS.hex\r\n" );

//	HexFileReceiveStarted = 1;


	Delay_MS( 2000 );

//	ESP8266_VidConnectToSrvTcp( (u8 *)"185.176.43.108" , (u8 *)"80" );

	/**/
	while(DataCome [i] != 'C' && DataCome [i] != '\n')
	{
		if(DataCome[i] >= '0' && DataCome[i] <= '9')
		{
			version_number = (version_number * 10) + (DataCome[i] - '0');
		}
		i++;
	}
//	version_number = (DataCome [0] - 48);
	return version_number ;

}

void ESP8266_VidClearBuffer ( void ){

	u8 LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 150 ; LOC_u8Iterator1++ ){

		DataCome[ LOC_u8Iterator1 ] = 0 ;

	}

}
