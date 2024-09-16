/*
 * MFDI_Private.h
 *
 *  Created on: 23-05-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MFDI_PRIVATE_H_
#define MFDI_PRIVATE_H_

#define FDI_BASE_ADDRESS			0x40023C00

typedef struct
{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;
}FDI_t;

#define FDI							((volatile FDI_t*)FDI_BASE_ADDRESS)


#define KEY_1						0x45670123
#define KEY_2						0xCDEF89AB
#define HALF_WORD					0b01


#endif /* MFDI_PRIVATE_H_ */
