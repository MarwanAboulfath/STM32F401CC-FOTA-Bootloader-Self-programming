/*
 * MRCC_Program.c
 *
 *  Created on: Apr 21, 2024
 *      Author: Marwan
 */

/*****************************************************/
/*					FILES INCLUSIONS				 */
/*****************************************************/
/************************LIB**************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"

/************************MCAL*************************/
#include "../include/MCAL/MRCC/MRCC_Config.h"
#include "../include/MCAL/MRCC/MRCC_Interface.h"
#include "../include/MCAL/MRCC/MRCC_Private.h"

/************************HAL**************************/



/******************FUNCTIONS DEFENITIONS******************/
void MRCC_voidInit(void)
{
	/* Check SYS_CLK configuration parameter to configure CLOCK */
#if SYS_CLK == RCC_HSI
	/* SET CR_HSI_ON bit in CR register to enable HSI */
	SET_BIT(RCC->CR, CR_HSI_ON);
	/* Busy wait until CR_HSI_RDY bit is set (Clock is ready) */
	while(GET_BIT(RCC->CR, CR_HSI_RDY) == RCC_NOT_READY);
	/* Mask First two bits in CFGR to clear them */
	RCC->CFGR &= ~(TWO_BIT_MASK<<SW_B0);
	/* Clear first two bits in CFGR to select HSI as processor clock input source */
	RCC->CFGR |= (SWI_HSI<<SW_B0);

#elif SYS_CLK == RCC_HSE
	/* SET CR_HSE_ON bit in CR register to enable HSE */
	SET_BIT(RCC->CR, CR_HSE_ON);
	/* Busy wait until CR_HSE_RDY bit is set (Clock is ready) */
	while(GET_BIT(RCC->CR, CR_HSE_RDY) == RCC_NOT_READY);
	/* Mask First two bits in CFGR to clear them */
	RCC->CFGR &= ~(TWO_BIT_MASK<<SW_B0);
	/* Set first bit and clear second bit in CFGR to select HSE as processor clock input source */
	RCC->CFGR |= (SWI_HSE<<SW_B0);


#elif SYS_CLK == RCC_PLL
	/* SET CR_PLL_ON bit in CR register to enable PLL */
	SET_BIT(RCC->CR, CR_PLL_ON);
	/* Busy wait until CR_PLL_RDY bit is set (Clock is ready) */
	while(GET_BIT(RCC->CR, CR_PLL_RDY) == RCC_NOT_READY);
	/* Mask First two bits in CFGR to clear them */
	RCC->CFGR &= ~(TWO_BIT_MASK<<SW_B0);
	/* Clear first bit and Set second bit in CFGR to select PLL as processor clock input source */
	RCC->CFGR |= (SWI_PLL<<SW_B0);
#else
	/* In case SYS_CLK is not within the specified parameters */
#error	"Wrong SYS_CLK configuration parameter!"
#endif


	/* Check RCC_CLK_SECURITY_SYSTEM configuration parameter to configure CLOCK SECURITY SYSTEM */
#if RCC_CLK_SECURITY_SYSTEM == RCC_CSS_ON
	/* Set CR_CSSON bit in CR register to turn on Clock security system feature */
	SET_BIT(RCC->CR, CR_CSSON);


#elif RCC_CLK_SECURITY_SYSTEM == RCC_CSS_OFF
	/* Clear CR_CSSON bit in CR register to turn off Clock security system feature */
	CLR_BIT(RCC->CR, CR_CSSON);
#else
	/* In case RCC_CLK_SECURITY_SYSTEM is not within the specified parameters */
#error "Wrong RCC_CLK_SECURITY_SYSTEM configuration parameter!"

#endif
}


void MRCC_voidEnablePeripheral(u32 copy_u32BusAddress, u32 copy_u32Peripheral)
{
	/* Validate Input parameters */
	// copy_u32BusAddress parameter value should be less than number of peripheral busses
	// copy_u32Peripheral parameter value should be less than number of peripheral bits in each register
	if(copy_u32BusAddress < RCC_NUMBER_OF_BUSSES && copy_u32Peripheral < BITS_PER_REGISTER)
	{
		/* Switch on copy_u32BusAddress to select desired PERIPHERAL BUS */
		switch(copy_u32BusAddress)
		{
		case RCC_APB1:
			/* Set specified peripheral bit on APB1ENR register to enable peripheral's clock */
			SET_BIT(RCC->APB1ENR,copy_u32Peripheral);
			break;
		case RCC_APB2:
			/* Set specified peripheral bit on APB2ENR register to enable peripheral's clock */
			SET_BIT(RCC->APB2ENR,copy_u32Peripheral);
			break;

		case RCC_AHB1:
			/* Set specified peripheral bit on AHB1ENR register to enable peripheral's clock */
			SET_BIT(RCC->AHB1ENR,copy_u32Peripheral);
			break;

		case RCC_AHB2:
			/* Set specified peripheral bit on AHB2ENR register to enable peripheral's clock */
			SET_BIT(RCC->AHB2ENR,copy_u32Peripheral);
			break;

		case AHB1_LP:
			SET_BIT(RCC->AHB1LPENR,copy_u32Peripheral);
			break;

		default:
			/* Wrong Peripheral bus parameter */
			break;
		}
	}
	else
	{
		/* DO NOTHING */
	}
}

void MRCC_voidDisablePeripheral(u32 copy_u32BusAddress, u32 copy_u32Peripheral)
{
	/* Validate Input parameters */
	// copy_u32BusAddress parameter value should be less than number of peripheral busses
	// copy_u32Peripheral parameter value should be less than number of peripheral bits in each register
	if(copy_u32BusAddress < RCC_NUMBER_OF_BUSSES && copy_u32Peripheral < BITS_PER_REGISTER)
	{
		/* Switch on copy_u32BusAddress to select desired PERIPHERAL BUS */
		switch(copy_u32BusAddress)
		{
		case RCC_APB1:
			/* Clear specified peripheral bit on APB1ENR register to disable peripheral's clock */
			CLR_BIT(RCC->APB1ENR,copy_u32Peripheral);
			break;
		case RCC_APB2:
			/* Clear specified peripheral bit on APB2ENR register to disable peripheral's clock */
			CLR_BIT(RCC->APB2ENR,copy_u32Peripheral);
			break;

		case RCC_AHB1:
			/* Clear specified peripheral bit on AHB1ENR register to disable peripheral's clock */
			CLR_BIT(RCC->AHB1ENR,copy_u32Peripheral);
			break;

		case RCC_AHB2:
			/* Clear specified peripheral bit on AHB2ENR register to disable peripheral's clock */
			CLR_BIT(RCC->AHB2ENR,copy_u32Peripheral);
			break;

		case AHB1_LP:
			CLR_BIT(RCC->AHB1LPENR,copy_u32Peripheral);
			break;

		default:
			/* Wrong Peripheral bus parameter */
			break;
		}
	}
	else
	{
		/* DO NOTHING */
	}
}


void MRCC_voidSetAPB1Prescaler (u8 A_u8APB1Prescaler)
{
	/* Input Validation */
	if (A_u8APB1Prescaler <= RCC_APB_PRESCALER_BY_16)
	{
		/*Clear bits 10,11,12 using MASKING*/
		RCC->CFGR &= ~(THREE_BIT_MASK << CR_PPRE1);
		/*Set bits 10,11,12 based on the entered prescaler*/
		RCC->CFGR |= (A_u8APB1Prescaler << CR_PPRE1);
	}
}
void MRCC_voidSetAPB2Prescaler (u8 A_u8APB2Prescaler)
{
	/* Input Validation */
	if (A_u8APB2Prescaler <= RCC_APB_PRESCALER_BY_16)
	{
		/*Clear bits 13,14,15 using MASKING*/
		RCC->CFGR &= ~(THREE_BIT_MASK << CR_PPRE2);
		/*Set bits 13,14,15 based on the entered prescaler*/
		RCC->CFGR |= (A_u8APB2Prescaler << CR_PPRE2);
	}
}
void MRCC_voidSetAHBPrescaler (u8 A_u8AHBPrescaler)
{
	/* Input Validation */
	if (A_u8AHBPrescaler <= RCC_AHB_PRESCALER_BY_512)
	{
		/*Clear bits 4, 5, 6, 7 using MASKING*/
		RCC->CFGR &= ~(FOUR_BIT_MASK << CR_HPRE);
		/*Set bits 4, 5, 6, 7 based on the entered prescaler*/
		RCC->CFGR |= (A_u8AHBPrescaler << CR_HPRE);
	}
}

u16 MRCC_voidGetAHBPrescaler (void)
{
	u8 A_u8AHBPrescaler;
	u16 Local_u16AHBPrescalar=0;


	A_u8AHBPrescaler = ((RCC->CFGR & 0x000000F0)>>CR_HPRE);

	if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_2)
	{
		Local_u16AHBPrescalar = 2;
	}
	else if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_4)
	{
		Local_u16AHBPrescalar = 4;
	}
	else if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_8)
	{
		Local_u16AHBPrescalar = 8;
	}
	else if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_16)
	{
		Local_u16AHBPrescalar = 16;
	}
	else if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_64)
	{
		Local_u16AHBPrescalar = 64;
	}
	else if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_128)
	{
		Local_u16AHBPrescalar = 128;
	}
	else if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_256)
	{
		Local_u16AHBPrescalar = 256;
	}
	else if(A_u8AHBPrescaler == RCC_AHB_PRESCALER_BY_512)
	{
		Local_u16AHBPrescalar = 512;
	}
	else
	{
		Local_u16AHBPrescalar = 1;
	}

	return (Local_u16AHBPrescalar);
}



