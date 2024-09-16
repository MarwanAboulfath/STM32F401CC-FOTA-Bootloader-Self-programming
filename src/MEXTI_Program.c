/*
 * MEXTI_Program.c
 *
 *  Created on: 24-04-2024
 *   Author: Marwan Aboulfath
 *
 */


#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"

#include "../include/MCAL/MEXTI/MEXTI_Config.h"
#include "../include/MCAL/MEXTI/MEXTI_Interface.h"
#include "../include/MCAL/MEXTI/MEXTI_private.h"



extern MEXTI_Configurations MEXTI_Config[MEXTI_NUMBER];

static PtrToFunc_void MEXTI_callBack[MEXTI_TOTAL_NUMBER];



void MEXTI_voidInit (void)
{
	/*initialize an iterator to iterate on the EXTIs in configuration source file*/
	u8 local_u8Iterator = 0;
	for (local_u8Iterator = 0 ; local_u8Iterator < MEXTI_NUMBER ; local_u8Iterator++)
	{
		/*Set the EXTI port*/
		MEXTI_voidSelectPort(MEXTI_Config[local_u8Iterator].Line , MEXTI_Config[local_u8Iterator].Port);
		/*Set the EXTI mode*/
		if (MEXTI_Config[local_u8Iterator].Mode == MEXTI_FALLING_EDGE)
		{
			SET_BIT(EXTI->FTSR , MEXTI_Config[local_u8Iterator].Line);
			CLR_BIT(EXTI->RTSR , MEXTI_Config[local_u8Iterator].Line);
		}
		else if (MEXTI_Config[local_u8Iterator].Mode == MEXTI_RISING_EDGE)
		{
			SET_BIT(EXTI->RTSR , MEXTI_Config[local_u8Iterator].Line);
			CLR_BIT(EXTI->FTSR , MEXTI_Config[local_u8Iterator].Line);
		}
		else
		{
			SET_BIT(EXTI->FTSR , MEXTI_Config[local_u8Iterator].Line);
			SET_BIT(EXTI->RTSR , MEXTI_Config[local_u8Iterator].Line);
		}
		/*Set state of EXTI based on the given Intial Value*/
		if (MEXTI_Config[local_u8Iterator].State == MEXTI_ENABLED)
		{
			SET_BIT(EXTI->IMR , MEXTI_Config[local_u8Iterator].Line);
		}
		else
		{
			CLR_BIT(EXTI->IMR , MEXTI_Config[local_u8Iterator].Line);
		}
	}

}

void MEXTI_voidEnableEXTILine (MEXTI_Line A_MEXTI_Line)
{
	/*Set the corresponding bit to enable the entered EXTI*/
	SET_BIT(EXTI->IMR , A_MEXTI_Line);
}

void MEXTI_voidDisableEXTILine (MEXTI_Line A_MEXTI_Line)
{
	/*Clear the corresponding bit to disable the entered EXTI*/
	CLR_BIT(EXTI->IMR , A_MEXTI_Line);
}

void MEXTI_voidSetCallBack (MEXTI_Line A_MEXTI_Line , PtrToFunc_void A_CallBackFunc)
{
	/*Set the entered function to the entered EXTI Callback function pointer*/
	MEXTI_callBack[A_MEXTI_Line] = A_CallBackFunc;
}

void MEXTI_voidSoftwareInterrputRequest (MEXTI_Line A_MEXTI_Line)
{
	/*Set the corresponding bit to trigger an interrupt request*/
	SET_BIT(EXTI->SWIER , A_MEXTI_Line);
}

void MEXTI_voidClearPendingFlag (MEXTI_Line A_MEXTI_Line)
{
	/*Set the corresponding bit to clear the pending flag*/
	SET_BIT(EXTI->PR , A_MEXTI_Line);
}

void MEXTI_voidSelectPort (MEXTI_Line A_MEXTI_Line , MEXTI_Port A_MEXTI_Port)
{
	/*Set those bits based on the entered port and EXTI*/
	SYSCFG->EXTICR[(A_MEXTI_Line/4)] &= ~(FOUR_BIT_MASK << ((A_MEXTI_Line%4)*4));
	SYSCFG->EXTICR[(A_MEXTI_Line/4)] |=  (A_MEXTI_Port << ((A_MEXTI_Line%4)*4));
}

void MEXTI_voidSetMode (MEXTI_Line A_MEXTI_Line , MEXTI_Mode A_MEXTI_Mode)
{
	/*Set those bits based on the entered mode and EXTI*/
	if (A_MEXTI_Mode == MEXTI_FALLING_EDGE)
	{
		SET_BIT(EXTI->FTSR , A_MEXTI_Line);
		CLR_BIT(EXTI->RTSR , A_MEXTI_Line);
	}
	else if (A_MEXTI_Mode == MEXTI_RISING_EDGE)
	{
		SET_BIT(EXTI->RTSR , A_MEXTI_Line);
		CLR_BIT(EXTI->FTSR , A_MEXTI_Line);
	}
	else
	{
		SET_BIT(EXTI->FTSR , A_MEXTI_Line);
		SET_BIT(EXTI->RTSR , A_MEXTI_Line);
	}
}



/****************EXTI handlers*********************/
void EXTI0_IRQHandler(void)
{
	if(MEXTI_callBack[0] != NULL_ptr){
		MEXTI_callBack[0]();
	}
	SET_BIT(EXTI -> PR, 0);
}


void EXTI1_IRQHandler(void)
{
	if(MEXTI_callBack[1] != NULL_ptr){
		MEXTI_callBack[1]();
	}
	SET_BIT(EXTI -> PR, 1);
}


void EXTI2_IRQHandler(void)
{
	if(MEXTI_callBack[2] != NULL_ptr){
		MEXTI_callBack[2]();
	}
	SET_BIT(EXTI -> PR, 2);
}


void EXTI3_IRQHandler(void)
{
	if(MEXTI_callBack[3] != NULL_ptr){
		MEXTI_callBack[3]();
	}
	SET_BIT(EXTI -> PR, 3);
}


void EXTI4_IRQHandler(void)
{
	if(MEXTI_callBack[4] != NULL_ptr){
		MEXTI_callBack[4]();
	}
	SET_BIT(EXTI -> PR, 4);
}

void EXTI9_5_IRQHandler(void)
{
	if(MEXTI_callBack[5] != NULL_ptr){
		MEXTI_callBack[5]();
	}
	SET_BIT(EXTI -> PR, 5);
}

void EXTI6_IRQHandler(void)
{
	if(MEXTI_callBack[6] != NULL_ptr){
		MEXTI_callBack[6]();
	}
	SET_BIT(EXTI -> PR, 6);
}

void EXTI7_IRQHandler(void)
{
	if(MEXTI_callBack[7] != NULL_ptr){
		MEXTI_callBack[7]();
	}
	SET_BIT(EXTI -> PR, 7);
}

void EXTI8_IRQHandler(void)
{
	if(MEXTI_callBack[8] != NULL_ptr){
		MEXTI_callBack[8]();
	}
	SET_BIT(EXTI -> PR, 8);
}


void EXTI9_IRQHandler(void)
{
	if(MEXTI_callBack[9] != NULL_ptr){
		MEXTI_callBack[9]();
	}
	SET_BIT(EXTI -> PR, 9);
}

void EXTI15_10_IRQHandler(void)
{
	if(MEXTI_callBack[10] != NULL_ptr){
		MEXTI_callBack[10]();
	}
	SET_BIT(EXTI -> PR, 10);
}

void EXTI11_IRQHandler(void)
{
	if(MEXTI_callBack[11] != NULL_ptr){
		MEXTI_callBack[11]();
	}
	SET_BIT(EXTI -> PR, 11);
}

void EXTI12_IRQHandler(void)
{
	if(MEXTI_callBack[12] != NULL_ptr){
		MEXTI_callBack[12]();
	}
	SET_BIT(EXTI -> PR, 12);
}

void EXTI13_IRQHandler(void)
{
	if(MEXTI_callBack[13] != NULL_ptr){
		MEXTI_callBack[13]();
	}
	SET_BIT(EXTI -> PR, 13);
}

void EXTI14_IRQHandler(void)
{
	if(MEXTI_callBack[14] != NULL_ptr){
		MEXTI_callBack[14]();
	}
	SET_BIT(EXTI -> PR, 14);
}

void EXTI15_IRQHandler(void)
{
	if(MEXTI_callBack[15] != NULL_ptr){
		MEXTI_callBack[15]();
	}
	SET_BIT(EXTI -> PR, 15);
}
