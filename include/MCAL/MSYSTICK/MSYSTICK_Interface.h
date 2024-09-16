/*
 * MSYSTICK_Interface.h
 *
 *  Created on: 30-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MSYSTICK_INTERFACE_H_
#define MSYSTICK_INTERFACE_H_


/************************************************************************************************/
/*									FUNCTIONS API's												*/
/************************************************************************************************/


void MSYSTICK_voidInit(void);

void MSYSTICK_voidSetBusyWait(u32 copy_u32Ticks);
void MSYSTICK_voidSetBusyWait_ms(u16 copy_u16TimePeriod);
void MSYSTICK_voidSetBusyWait_us(u32 copy_u32TimePeriod);

void MSYSTICK_voidSetSingleInterval(u32 copy_u32Ticks,PtrToFunc_void copy_callBackFunc);
void MSYSTICK_voidSetSingleInterval_ms(u16 copy_u16TimePeriod,PtrToFunc_void copy_callBackFunc);
void MSYSTICK_voidSetSingleInterval_us(u32 copy_u32TimePeriod,PtrToFunc_void copy_callBackFunc);

void MSYSTICK_voidSetPeriodicInterval(u32 copy_u32Ticks,PtrToFunc_void copy_callBackFunc);
void MSYSTICK_voidSetPeriodicInterval_ms(u16 copy_u16TimePeriod,PtrToFunc_void copy_callBackFunc);
void MSYSTICK_voidSetPeriodicInterval_us(u32 copy_u32TimePeriod,PtrToFunc_void copy_callBackFunc);

u32 MSYSTICK_u32GetElapsedTime(void);
u16 MSYSTICK_u16GetElapsedTime_ms(void);

u32 MSYSTICK_u32GetRemainingTime(void);
u16 MSYSTICK_u16GetRemainingTime_ms(void);

void MSYSTICK_voidDelayms(u32 Copy_u32TimeINms);
void MSYSTICK_voidDelayus(u32 Copy_u32TimeINus);

#endif /* MSYSTICK_INTERFACE_H_ */
