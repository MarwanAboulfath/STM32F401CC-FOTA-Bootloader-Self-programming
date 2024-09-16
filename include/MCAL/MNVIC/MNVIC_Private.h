/*
 * MNVIC_Private.h
 *
 *  Created on: 24-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MNVIC_PRIVATE_H_
#define MNVIC_PRIVATE_H_



/****************************************************************************/
/*						PERIPHERALS BASE ADDRESS							*/
#define NVIC_BASE_ADDRESS	0xE000E100

/****************************************************************************/
/*						REGISTERS STRUCTURE									*/
/****************************************************************************/


typedef struct{
	u32	ISER[8]			;
	u32 RESERVED1[24]	;
	u32	ICER[8]			;
	u32 RESERVED2[24]	;
	u32	ISPR[8]			;
	u32 RESERVED3[24]	;
	u32	ICPR[8]			;
	u32 RESERVED4[24]	;
	u32 IABR[8]		;
	u32 RESERVED5[56]	;
	u8	IPR[240]		;
	u32	RESERVED6[580]	;
	u32 STIR			;
}NVIC_t;



/****************************************************************************/
/*								PERIPHERALS 								*/
/****************************************************************************/

#define NVIC		((volatile NVIC_t*)NVIC_BASE_ADDRESS)
#define SCB_AIRCR	(*(volatile u32*)0xE000ED0C)


/****************************************************************************/
/*						       PRIVATE MACROS								*/
/****************************************************************************/

#define	SCB_WRITE_VECTKEY	0x5FA0000
#define SCB_READ_VECTKEY	0xFA050000

#define AICIR_PROIGROUP_B0	8
#define BITS_IN_REGISTER	32


#endif /* MNVIC_PRIVATE_H_ */
