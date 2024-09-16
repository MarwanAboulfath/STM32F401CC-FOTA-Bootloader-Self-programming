/*
 * MNVIC_Interface.h
 *
 *  Created on: 24-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MNVIC_INTERFACE_H_
#define MNVIC_INTERFACE_H_



typedef enum{
	Group16_NoSub=3	,
	Groups8_Sub2	,
	Groups4_Sub4	,
	Groups2_Sub8	,
	NoGroup_Sub16
}MNVIC_Group_t;


/*********************GENERAL MACROS*******************/
#define	WWDG_IRQ					0
#define EXTI16_IRQ					1
#define PVD_IRQ						1
#define EXTI21_IRQ					2
#define TAMP_STAMP_IRQ				2
#define EXTI22_IRQ					3
#define RTC_WKUP_IRQ				3
#define	FLASH_IRQ					4
#define RCC_IRQ						5
#define EXTI0_IRQ					6
#define EXTI1_IRQ					7
#define EXTI2_IRQ					8
#define EXTI3_IRQ					9
#define EXTI4_IRQ					10
#define DMA1_STREAM0_IRQ			11
#define DMA1_STREAM1_IRQ			12
#define DMA1_STREAM2_IRQ			13
#define DMA1_STREAM3_IRQ			14
#define DMA1_STREAM4_IRQ			15
#define DMA1_STREAM5_IRQ			16
#define DMA1_STREAM6_IRQ			17
#define ADC_IRQ						18
#define EXTI9_5_IRQ					23
#define TIM1_BRK_TIM9_IRQ			24
#define	TIM1_UP_TIM10_IRQ			25
#define	TIM1_TRG_COM_TIM11_IRQ		26
#define	TIM1_CC_IRQ					27
#define	TIM2_IRQ					28
#define	TIM3_IRQ					29
#define	TIM4_IRQ					30
#define	I2C1_EV_IRQ					31
#define	I2C1_ER_IRQ					32
#define	I2C2_EV_IRQ					33
#define	I2C2_ER_IRQ					34
#define	SPI1_IRQ					35
#define SPI2_IRQ					36
#define USART1_IRQ					37
#define	USART2_IRQ					38
#define	EXTI15_10_IRQ				40
#define	EXTI17_IRQ					41
#define	RTC_Alarm_IRQ				41
#define EXTI18_IRQ					42
#define OTG_FS_WKUP_IRQ				42
#define DMA1_Stream7_IRQ			47
#define	SDIO_IRQ					49
#define	TIM5_IRQ					50
#define	SPI3_IRQ					51
#define DMA2_Stream0_IRQ			56
#define DMA2_Stream1_IRQ			57
#define DMA2_Stream2_IRQ			58
#define DMA2_Stream3_IRQ			59
#define DMA2_Stream4_IRQ			60
#define OTG_FS_IRQ					67
#define DMA2_Stream5_IRQ			68
#define DMA2_Stream6_IRQ			69
#define DMA2_Stream7_IRQ			70
#define USART6_IRQ					71
#define I2C3_EV_IRQ					72
#define I2C3_ER_IRQ					73
#define FPU_IRQ						81
#define SPI4_IRQ					84


/************************************************************************************************/
/*									FUNCTIONS API's												*/
/************************************************************************************************/

void MNVIC_voidEnablePeripheralInterrupt(u8 copy_u8Peripheral);
void MNVIC_voidDisablePeripheralInterrupt(u8 copy_u8Peripheral);

void MNVIC_voidEnablePeripheralInterruptPending(u8 copy_u8Peripheral);
void MNVIC_voidDisablePeripheralInterruptPending(u8 copy_u8Peripheral);

void MNVIC_voidGetInterruptState(u8 copy_u8Peripheral, u8 *p_Read);

void MNVIC_voidSetInterruptGroupMode(MNVIC_Group_t MNVIC_GroupMode);
void MNVIC_voidSetInterruptPriority(u8 copy_u8Peripheral,u8 copy_u8GroupNumber, u8 copy_u8SubGroupNumber);





#endif /* MNVIC_INTERFACE_H_ */
