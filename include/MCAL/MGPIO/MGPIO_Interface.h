/*
 * MGPIO_Interface.h
 *
 *  Created on: 22-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_


/*************************General Macros******************************/
/***********************Ports**************************/
#define GPIO_PORTA			0
#define GPIO_PORTB			1
#define GPIO_PORTC			2
/* Half Ports */
#define GPIO_PORTA_FIRST_HALF			3
#define GPIO_PORTB_SECOND_HALF			4

/***********************Pins**************************/
#define GPIO_PIN0			0
#define GPIO_PIN1			1
#define GPIO_PIN2			2
#define GPIO_PIN3			3
#define GPIO_PIN4			4
#define GPIO_PIN5			5
#define GPIO_PIN6			6
#define GPIO_PIN7			7
#define GPIO_PIN8			8
#define GPIO_PIN9			9
#define GPIO_PIN10			10
#define GPIO_PIN11			11
#define GPIO_PIN12			12
#define GPIO_PIN13			13
#define GPIO_PIN14			14
#define GPIO_PIN15			15


/*******************Pin Mode**************************/
#define GPIO_INPUT			0b00
#define GPIO_OUTPUT			0b01
#define GPIO_ALT_FUNC		0b10
#define GPIO_ANALOG			0b11

#define GPIO_HALF_PORT_INPUT					0x0000
#define GPIO_HALF_PORT_OUTPUT					0x5555
#define GPIO_HALF_PORT_ALTERNATE_FUNCTION		0xAAAA
#define GPIO_HALF_PORT_ANALOG					0xFFFF

/***************Output Speed Modes*******************/
#define GPIO_LOW_SPEED		0b00
#define GPIO_MEDIUM_SPEED	0b01
#define GPIO_HIGH_SPEED		0b10
#define GPIO_VHIGH_SPEED	0b11

#define GPIO_HALF_PORT_LOW_SPEED		0x0000
#define GPIO_HALF_PORT_MEDIUM_SPEED		0x5555
#define GPIO_HALF_PORT_HIGH_SPEED		0xAAAA
#define GPIO_HALF_PORT_VHIGH_SPEED	    0xFFFF


/**************Input Modes****************************/
#define GPIO_NOPUPD			0b00
#define GPIO_PULLUP			0b01
#define GPIO_PULLDOWN		0b10

#define GPIO_HALF_PORT_NOPUPD			0x0000
#define GPIO_HALF_PORT_PULLUP			0x5555
#define GPIO_HALF_PORT_PULLDOWN			0xAAAA

/**********Output Modes*******************************/
#define GPIO_PUSH_PULL		0b0
#define GPIO_OPEN_DRAIN		0b1

#define GPIO_HALF_PORT_PUSH_PULL		0x00
#define GPIO_HALF_PORT_OPEN_DRAIN		0xFF

/***********Pin Values*******************************/
#define GPIO_PIN_LOW		0
#define GPIO_PIN_HIGH		1
/***********Half Port Values*******************************/
#define GPIO_HALF_PORT_LOW		0
#define GPIO_HALF_PORT_HIGH		0xFF

/***********Pin Set Reset*******************************/
#define GPIO_SET		1
#define GPIO_RESET		0

#define GPIO_HALF_PORT_SET		0xFF
#define GPIO_HALF_PORT_RESET	0

/**************************Functions Prototypes***********************/
void MGPIO_voidSetPinMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Mode);
void MGPIO_voidSetPinOutputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8OutputMode , u8 copyu8Speed);
void MGPIO_voidSetPinInputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8InputMode);
void MGPIO_voidSetPinValue(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Output);
void MGPIO_voidGetPinValue(u8 copyu8Port, u8 copyu8Pin, u8 *pu8Return);
void MGPIO_voidSetResetPin(u8 copyu8Port, u8 copyu8Pin, u8 copyu8SetResetValue);
void MGPIO_voidSetAF(u8 copy_u8PORT, u8 copy_u8PIN, u8 copy_u8AlternateFunctionNo);

void MGPIO_voidSetHalfPortMode(u8 copyu8Port, u16 copyu16Mode);
void MGPIO_voidSetHalfPortOutputMode(u8 copyu8Port, u8 copyu8OutputMode , u16 copyu16Speed);
void MGPIO_voidSetHalfPortInputMode(u8 copyu8Port, u16 copyu16InputMode);
void MGPIO_voidSetHalfPortValue(u8 copyu8Port, u8 copyu8Output);
void MGPIO_voidGetHalfPortValue(u8 copyu8Port, u8 *pu8Return);
void MGPIO_voidSetResetHalfPort(u8 copyu8Port, u8 copyu8SetResetValue);

#endif /* MGPIO_INTERFACE_H_ */
