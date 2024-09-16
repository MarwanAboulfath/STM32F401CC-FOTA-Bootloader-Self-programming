/*
 * MFDI_Program.c
 *
 *  Created on: 23-05-2024
 *   Author: Marwan Aboulfath
 *
 */

/*****************************************************/
/*					FILES INCLUSIONS				 */
/*****************************************************/
/************************LIB**************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
/************************MCAL*************************/
#include "../include/MCAL/MFDI/MFDI_Interface.h"
#include "../include/MCAL/MFDI/MFDI_Config.h"
#include "../include/MCAL/MFDI/MFDI_Private.h"



void MFDI_voidEraseSector(u8 Copy_u8SectorNum)
{
	// Make sure Busy flag is not raised
	while(GET_BIT(FDI->SR, 16) == 1);
	// Check CTRL register (Locked or Unlocked)
	if(GET_BIT(FDI->CR, 31) == 1)
	{
		FDI->KEYR = KEY_1;
		FDI->KEYR = KEY_2;
	}
	else
	{
		// DO NOTHING
	}

	// Set sector number
	// Clear sector number bits
	FDI->CR &= ~(0b1111 << 3);
	FDI->CR |= (Copy_u8SectorNum << 3);
	// Activate sector erase mode
	SET_BIT(FDI->CR, 1);
	// Clear mass erase
	CLR_BIT(FDI->CR, 2);
	// Start Erase Operation
	SET_BIT(FDI->CR, 16);
	// Wait for busy flag
	while(GET_BIT(FDI->SR, 16) == 1);
	// Clear EOF end of operation flag
	SET_BIT(FDI->SR, 0);
	// Deactivate Operated mode
	CLR_BIT(FDI->CR, 16);
	// Deactivate sector erase mode
	CLR_BIT(FDI->CR, 1);

}

void MFDI_voidEraseAppSector(void)
{
	for(u8 i = 1; i < 6; i++)
	{
		MFDI_voidEraseSector(i);
	}
}

void MFDI_voidWrite(u32 Copy_u32Address, u16 *Copy_pu16PtrToData, u8 Copy_u8Length)
{
	// Make sure Busy flag is not raised
	while(GET_BIT(FDI->SR, 16) == 1);
	// Check CTRL register (Locked or Unlocked)
	if(GET_BIT(FDI->CR, 31) == 1)
	{
		FDI->KEYR = KEY_1;
		FDI->KEYR = KEY_2;
	}
	else
	{
		// DO NOTHING
	}

	// Select Half word mode -> Psize
	FDI->CR &= ~(0b11 << 8);
	FDI->CR |= (HALF_WORD << 8);

	for(u8 i=0; i<Copy_u8Length; i++)
	{
		// Set programming mode
		SET_BIT(FDI->CR, 0);
		*(u16*)Copy_u32Address = Copy_pu16PtrToData[i];
		Copy_u32Address += 2;
		// Wait for busy flag
		while(GET_BIT(FDI->SR, 16) == 1);
		// Clear EOF end of operation flag
		SET_BIT(FDI->SR, 0);
		// Deactivate programming mode
		CLR_BIT(FDI->CR, 0);
	}
}






