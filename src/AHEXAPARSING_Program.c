/*
 * AHEXAPARSING_Program.c
 *
 *  Created on: 26-05-2024
 *   Author: Marwan Aboulfath
 *
 */

/************************LIB**************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
/************************MCAL*************************/
#include "../include/MCAL/MFDI/MFDI_Interface.h"
/************************APP**************************/
#include "../include/APP/AHEXAPARSING/AHEXAPARSING_Interface.h"
#include "../include/APP/AHEXAPARSING/AHEXAPARSING_Config.h"
#include "../include/APP/AHEXAPARSING/AHEXAPARSING_Private.h"

u32 Global_u32FullAddress = 0x08000000;
u16 Global_u16DataBuffer[100];

static u8 Ascii_u8ToHex(u8 Copy_u8Ascii)
{
	u8 Local_u8Result = 0;
	if((Copy_u8Ascii >= 48) && (Copy_u8Ascii <= 57))
	{
		Local_u8Result = Copy_u8Ascii - '0';
	}
	else
	{
		Local_u8Result = (Copy_u8Ascii - 'A') + 10;
	}
	return Local_u8Result;
}


void Hexa_voidParseData(u8 *Copy_u8DataPtr)
{
	u8 Local_u8CCHighNipple = 0;
	u8 Local_u8CCLowNipple = 0;
	u8 Local_u8CCTotal = 0;
	u8 Local_u8Digit0 = 0;
	u8 Local_u8Digit1 = 0;
	u8 Local_u8Digit2 = 0;
	u8 Local_u8Digit3 = 0;
	u16 Local_u16LowPartofAddress = 0;
	u16 Local_u16DataHalfWord = 0;

	Local_u8CCHighNipple = Ascii_u8ToHex(Copy_u8DataPtr[1]);	// High digit
	Local_u8CCLowNipple = Ascii_u8ToHex(Copy_u8DataPtr[2]);	// Low DigitS

	Local_u8CCTotal = (Local_u8CCHighNipple << 4) | (Local_u8CCLowNipple);	// Full Character count
	// Each variable holds a digit of four digits of the address
	Local_u8Digit0 = Ascii_u8ToHex(Copy_u8DataPtr[3]);
	Local_u8Digit1 = Ascii_u8ToHex(Copy_u8DataPtr[4]);
	Local_u8Digit2 = Ascii_u8ToHex(Copy_u8DataPtr[5]);
	Local_u8Digit3 = Ascii_u8ToHex(Copy_u8DataPtr[6]);
	// Low part of address
	Local_u16LowPartofAddress = (Local_u8Digit0 << 12) |
								(Local_u8Digit1 << 8) |
								(Local_u8Digit2 << 4) |
								(Local_u8Digit3 << 0);

	Global_u32FullAddress &= 0xFFFF0000;
	Global_u32FullAddress |= Local_u16LowPartofAddress;

	for(u8 i = 0; i <  (Local_u8CCTotal/2); i++)
	{
		Local_u8Digit0 = Ascii_u8ToHex(Copy_u8DataPtr[(i*4)+9]);
		Local_u8Digit1 = Ascii_u8ToHex(Copy_u8DataPtr[(i*4)+10]);
		Local_u8Digit2 = Ascii_u8ToHex(Copy_u8DataPtr[(i*4)+11]);
		Local_u8Digit3 = Ascii_u8ToHex(Copy_u8DataPtr[(i*4)+12]);

		/* Rearrange the LSB then the MSB in the u16 variable	(D2-D3 -> MSB, D0-D1 -> LSB) */
		Local_u16DataHalfWord = (Local_u8Digit2 << 12) |
								(Local_u8Digit3 << 8) |
								(Local_u8Digit0 << 4) |
								(Local_u8Digit1 << 0);
		/* Insert the data in the data buffer */
		Global_u16DataBuffer[i] = Local_u16DataHalfWord;
	}

	MFDI_voidWrite(Global_u32FullAddress, Global_u16DataBuffer, (Local_u8CCTotal/2));
}

u8 Hexa_voidParseRecord(u8 *Copy_u8Record)
{
	u8 EndOfFile = 0;
	switch(Copy_u8Record[8])
	{
	case '0':	Hexa_voidParseData(Copy_u8Record);	/*Data record*/		break;
	case '1':	EndOfFile = 1;						/* END OF FILE */	break;
	case '5':		/* FULL ADDRESS */									break;
	}
	return EndOfFile;
}








