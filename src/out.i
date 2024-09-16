# 1 "HLEDMRX_Program.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "HLEDMRX_Program.c"
# 10 "HLEDMRX_Program.c"
# 1 "../include/LIB/BIT_MATH.h" 1
# 11 "HLEDMRX_Program.c" 2
# 1 "../include/LIB/STD_TYPES.h" 1



typedef enum
{
 E_OK,
 E_NOK,
 E_NOK_NULL_PTR,
 E_NOK_OUT_OF_RANGE,
 E_NOK_TIME_OUT
}ReturnType_State_t;


typedef enum
{
 IDLE,
 BUSY
}Module_State_t;
typedef unsigned char u8 ;
typedef unsigned long int u32;
typedef unsigned long long int u64;
typedef unsigned short int u16;

typedef signed char s8 ;
typedef signed long int s32;
typedef signed long long int s64;
typedef signed short int s16;


typedef float f32;
typedef double f64;
typedef long double f128;

typedef u8 boolean;






typedef void(* PtrToFunc_void)(void);
# 12 "HLEDMRX_Program.c" 2

# 1 "../include/MCAL/MGPIO/MGPIO_Interface.h" 1
# 94 "../include/MCAL/MGPIO/MGPIO_Interface.h"
void MGPIO_voidSetPinMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Mode);
void MGPIO_voidSetPinOutputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8OutputMode , u8 copyu8Speed);
void MGPIO_voidSetPinInputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8InputMode);
void MGPIO_voidSetPinValue(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Output);
void MGPIO_voidGetPinValue(u8 copyu8Port, u8 copyu8Pin, u8 *pu8Return);
void MGPIO_voidSetResetPin(u8 copyu8Port, u8 copyu8Pin, u8 copyu8SetResetValue);

void MGPIO_voidSetHalfPortMode(u8 copyu8Port, u16 copyu16Mode);
void MGPIO_voidSetHalfPortOutputMode(u8 copyu8Port, u8 copyu8OutputMode , u16 copyu16Speed);
void MGPIO_voidSetHalfPortInputMode(u8 copyu8Port, u16 copyu16InputMode);
void MGPIO_voidSetHalfPortValue(u8 copyu8Port, u8 copyu8Output);
void MGPIO_voidGetHalfPortValue(u8 copyu8Port, u8 *pu8Return);
void MGPIO_voidSetResetHalfPort(u8 copyu8Port, u8 copyu8SetResetValue);
# 14 "HLEDMRX_Program.c" 2
# 1 "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h" 1
# 17 "../include/MCAL/MSYSTICK/MSYSTICK_Interface.h"
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
# 15 "HLEDMRX_Program.c" 2

# 1 "../include/HAL/LEDMRX/HLEDMRX_Interface.h" 1
# 12 "../include/HAL/LEDMRX/HLEDMRX_Interface.h"
void HLEDMRX_voidInit(void);
void HLEDMRX_voidSendPattern(u8* Copy_pu8ptr);
# 17 "HLEDMRX_Program.c" 2
# 1 "../include/HAL/LEDMRX/HLEDMRX_Config.h" 1
# 25 "../include/HAL/LEDMRX/HLEDMRX_Config.h"
                        G
# 18 "HLEDMRX_Program.c" 2
# 1 "../include/HAL/LEDMRX/HLEDMRX_Private.h" 1
# 14 "../include/HAL/LEDMRX/HLEDMRX_Private.h"
;static void HLEDMRX_voidDisableColumns(void);

static void HLEDMRX_voidGetRowValue(u8 Copy_u8RowValue);
# 19 "HLEDMRX_Program.c" 2


static void HLEDMRX_voidDisableColumns(void)
{
 MGPIO_voidSetPinValue(0, 0, 1);
 MGPIO_voidSetPinValue(0, 1, 1);
 MGPIO_voidSetPinValue(0, 2, 1);
 MGPIO_voidSetPinValue(0, 3, 1);
 MGPIO_voidSetPinValue(0, 4, 1);
 MGPIO_voidSetPinValue(0, 5, 1);
 MGPIO_voidSetPinValue(0, 6, 1);
 MGPIO_voidSetPinValue(0, 7, 1);
}


void HLEDMRX_voidInit(void)
{


 MGPIO_voidSetPinMode(0, 0, 0b01);
 MGPIO_voidSetPinOutputMode(0, 0, 0b0, 0b00);
 MGPIO_voidSetPinMode(0, 1, 0b01);
 MGPIO_voidSetPinOutputMode(0, 1, 0b0, 0b00);
 MGPIO_voidSetPinMode(0, 2, 0b01);
 MGPIO_voidSetPinOutputMode(0, 2, 0b0, 0b00);
 MGPIO_voidSetPinMode(0, 3, 0b01);
 MGPIO_voidSetPinOutputMode(0, 3, 0b0, 0b00);
 MGPIO_voidSetPinMode(0, 4, 0b01);
 MGPIO_voidSetPinOutputMode(0, 4, 0b0, 0b00);
 MGPIO_voidSetPinMode(0, 5, 0b01);
 MGPIO_voidSetPinOutputMode(0, 5, 0b0, 0b00);
 MGPIO_voidSetPinMode(0, 6, 0b01);
 MGPIO_voidSetPinOutputMode(0, 6, 0b0, 0b00);
 MGPIO_voidSetPinMode(0, 7, 0b01);
 MGPIO_voidSetPinOutputMode(0, 7, 0b0, 0b00);

 MGPIO_voidSetPinMode(1, 0, 0b01);
 MGPIO_voidSetPinOutputMode(0, 0, 0b0, 0b00);
 MGPIO_voidSetPinMode(1, 1, 0b01);
 MGPIO_voidSetPinOutputMode(0, 1, 0b0, 0b00);
 MGPIO_voidSetPinMode(1, 2, 0b01);
 MGPIO_voidSetPinOutputMode(0, 2, 0b0, 0b00);
 MGPIO_voidSetPinMode(1, 5, 0b01);
 MGPIO_voidSetPinOutputMode(0, 5, 0b0, 0b00);
 MGPIO_voidSetPinMode(1, 6, 0b01);
 MGPIO_voidSetPinOutputMode(0, 6, 0b0, 0b00);
 MGPIO_voidSetPinMode(1, 7, 0b01);
 MGPIO_voidSetPinOutputMode(0, 7, 0b0, 0b00);
 MGPIO_voidSetPinMode(1, 8, 0b01);
 MGPIO_voidSetPinOutputMode(0, 8, 0b0, 0b00);
 MGPIO_voidSetPinMode(1, 9, 0b01);
 MGPIO_voidSetPinOutputMode(0, 9, 0b0, 0b00);
}

void HLEDMRX_voidSendPattern(u8* Copy_pu8ptr)
{

 HLEDMRX_voidDisableColumns();


 HLEDMRX_voidGetRowValue(Copy_pu8ptr[0]);
 MGPIO_voidSetPinValue(0, 0, 0);
 MSYSTICK_voidSetBusyWait(5000);

 HLEDMRX_voidGetRowValue(Copy_pu8ptr[1]);
 MGPIO_voidSetPinValue(0, 1, 0);
 MSYSTICK_voidSetBusyWait(5000);

 HLEDMRX_voidGetRowValue(Copy_pu8ptr[2]);
 MGPIO_voidSetPinValue(0, 2, 0);
 MSYSTICK_voidSetBusyWait(5000);

 HLEDMRX_voidGetRowValue(Copy_pu8ptr[3]);
 MGPIO_voidSetPinValue(0, 3, 0);
 MSYSTICK_voidSetBusyWait(5000);

 HLEDMRX_voidGetRowValue(Copy_pu8ptr[4]);
 MGPIO_voidSetPinValue(0, 4, 0);
 MSYSTICK_voidSetBusyWait(5000);

 HLEDMRX_voidGetRowValue(Copy_pu8ptr[5]);
 MGPIO_voidSetPinValue(0, 5, 0);
 MSYSTICK_voidSetBusyWait(5000);

 HLEDMRX_voidGetRowValue(Copy_pu8ptr[6]);
 MGPIO_voidSetPinValue(0, 6, 0);
 MSYSTICK_voidSetBusyWait(5000);

 HLEDMRX_voidGetRowValue(Copy_pu8ptr[7]);
 MGPIO_voidSetPinValue(0, 7, 0);
 MSYSTICK_voidSetBusyWait(5000);
}

static void HLEDMRX_voidGetRowValue(u8 Copy_u8RowValue)
{

 u8 Reading;
 Reading = ((Copy_u8RowValue>>0)&1);
 MGPIO_voidSetPinValue(1,0, Reading);
 Reading = ((Copy_u8RowValue>>1)&1);
 MGPIO_voidSetPinValue(1,1, Reading);
 Reading = ((Copy_u8RowValue>>2)&1);
 MGPIO_voidSetPinValue(1,2, Reading);
 Reading = ((Copy_u8RowValue>>3)&1);
 MGPIO_voidSetPinValue(1,5, Reading);
 Reading = ((Copy_u8RowValue>>4)&1);
 MGPIO_voidSetPinValue(1,6, Reading);
 Reading = ((Copy_u8RowValue>>5)&1);
 MGPIO_voidSetPinValue(1,7, Reading);
 Reading = ((Copy_u8RowValue>>6)&1);
 MGPIO_voidSetPinValue(1,8, Reading);
 Reading = ((Copy_u8RowValue>>7)&1);
 MGPIO_voidSetPinValue(1,9, Reading);

}
