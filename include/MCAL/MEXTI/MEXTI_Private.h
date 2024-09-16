/*
 * MEXTI_Private.h
 *
 *  Created on: 24-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MEXTI_PRIVATE_H_
#define MEXTI_PRIVATE_H_



/***************************EXT**************************************/
#define EXTI_BASE_ADDRESS	(0x40013C00)


typedef struct
{
	u32 IMR	 ;
	u32 EMR	 ;
	u32 RTSR ;
	u32 FTSR ;
	u32 SWIER;
	u32 PR	 ;
}EXTI_t;


#define EXTI	((volatile EXTI_t*)EXTI_BASE_ADDRESS)

/**************************SYSCFG************************************/
#define SYSCFG_BASE_ADDRESS		(0x40013800)

typedef struct
{
	u32 MEMRMP	  ;
	u32 PMC		  ;
	u32 EXTICR[4] ;
	u32 CMPCR	  ;
}SYSCFG_t;

#define SYSCFG	((volatile SYSCFG_t*)SYSCFG_BASE_ADDRESS)

/***********************************************************************/
/*************************MEXTI MACROS**********************************/
#define MEXTI_TOTAL_NUMBER		16
#define FOUR_BIT_MASK			0b1111

/*******************MEXTI Configuration Struct**************************/
typedef struct
{
	MEXTI_Line Line ;
	MEXTI_Port Port ;
	MEXTI_Mode Mode ;
	MEXTI_State State ;
}MEXTI_Configurations;




#endif /* MEXTI_PRIVATE_H_ */
