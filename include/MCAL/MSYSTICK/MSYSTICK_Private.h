/*
 * MSYSTICK_Private.h
 *
 *  Created on: 30-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MSYSTICK_PRIVATE_H_
#define MSYSTICK_PRIVATE_H_

/****************************************************************************/
/*						PERIPHERALS BASE ADDRESS							*/
#define SYSTICK_BASE_ADDRESS			0xE000E010


/****************************************************************************/
/*						REGISTERS STRUCTURE									*/
/****************************************************************************/

typedef struct{
	u32 STK_CTRL;
	u32	STK_LOAD;
	u32 STK_VAL;
}SYSTICK_type;

/****************************************************************************/
/*								PERIPHERALS 								*/
/****************************************************************************/

#define SYSTICK			((volatile SYSTICK_type*)SYSTICK_BASE_ADDRESS)

/*SYSTICK_CTRL Bits*/
#define STK_CTRL_ENABLE			0
#define STK_CTRL_TICKINT		1
#define STK_CTRL_CLKSOURCE		2
#define STK_CTRL_COUNTFLAG		16

/****************************************************************************/
/*						       PRIVATE MACROS								*/
/****************************************************************************/

#define SYSTICK_AHB_PRESCALER_BY_1				1
#define SYSTICK_AHB_PRESCALER_BY_8				2

#define SINGLE				1
#define PERIODIC			2

#define CLEAR_VALUE			0x000000

#define SYSTICK_COUNTING	0
#define SYSTICK_FINISHED	1


#endif /* MSYSTICK_PRIVATE_H_ */
