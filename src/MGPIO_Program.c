/*
 * MGPIO_Program.c
 *
 *  Created on: 22-04-2024
 *   Author: Marwan Aboulfath
 *
 */

/************************************************************************/
/*							FILES INCLUSIONS							*/
/************************************************************************/
/*******************************LIB**************************************/
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_Types.h"
/*******************************MCAL*************************************/
#include "../include/MCAL/MGPIO/MGPIO_Private.h"
#include "../include/MCAL/MGPIO/MGPIO_Config.h"
#include "../include/MCAL/MGPIO/MGPIO_Interface.h"

/**************************Functions Definitions***********************/
void MGPIO_voidSetPinMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Mode)
{
	if((copyu8Port == GPIO_PORTA) && ((copyu8Pin == GPIO_PIN13) ||(copyu8Pin == GPIO_PIN14)||(copyu8Pin == GPIO_PIN15)))
	{
		/*Do Nothing*/
	}

	else if((copyu8Port == GPIO_PORTB) && ((copyu8Pin == GPIO_PIN3) ||(copyu8Pin == GPIO_PIN4)))
	{
		/*Do Nothing*/
	}

	else
	{
		switch(copyu8Port)
		{
		case GPIO_PORTA:
			GPIOA->MODER &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOA->MODER |= (copyu8Mode<<(copyu8Pin *2));
			break;

		case GPIO_PORTB:
			GPIOB->MODER &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOB->MODER |= (copyu8Mode<<(copyu8Pin *2));
			break;

		case GPIO_PORTC:
			GPIOC->MODER &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOC->MODER |= (copyu8Mode<<(copyu8Pin *2));
			break;

		default:
			break;
		}
	}
}

void MGPIO_voidSetPinOutputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8OutputMode , u8 copyu8Speed)
{
	if((copyu8Port == GPIO_PORTA) && ((copyu8Pin == GPIO_PIN13) ||(copyu8Pin == GPIO_PIN14)||(copyu8Pin == GPIO_PIN15)))
	{
		/*Do Nothing*/
	}

	else if((copyu8Port == GPIO_PORTB) && ((copyu8Pin == GPIO_PIN3) ||(copyu8Pin == GPIO_PIN4)))
	{
		/*Do Nothing*/
	}

	else
	{
		switch(copyu8Port)
		{
		case GPIO_PORTA:
			/*Set speed*/
			GPIOA->OSPEEDR &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOA->OSPEEDR |= (copyu8Speed<<(copyu8Pin *2));

			/*Set pin output mode*/
			GPIOA->OTYPER &= ~(ONE_BIT_MASK <<(copyu8Pin));
			GPIOA->OTYPER |= (copyu8OutputMode<<(copyu8Pin));
			break;

		case GPIO_PORTB:
			GPIOB->OSPEEDR &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOB->OSPEEDR |= (copyu8Speed<<(copyu8Pin *2));

			GPIOB->OTYPER &= ~(ONE_BIT_MASK <<(copyu8Pin));
			GPIOB->OTYPER |= (copyu8OutputMode<<(copyu8Pin));
			break;

		case GPIO_PORTC:
			GPIOC->OSPEEDR &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOC->OSPEEDR |= (copyu8Speed<<(copyu8Pin *2));

			GPIOC->OTYPER &= ~(ONE_BIT_MASK <<(copyu8Pin));
			GPIOC->OTYPER |= (copyu8OutputMode<<(copyu8Pin));
			break;

		default:
			break;
		}
	}

}

void MGPIO_voidSetPinInputMode(u8 copyu8Port, u8 copyu8Pin, u8 copyu8InputMode)
{
	if((copyu8Port == GPIO_PORTA) && ((copyu8Pin == GPIO_PIN13) ||(copyu8Pin == GPIO_PIN14)||(copyu8Pin == GPIO_PIN15)))
	{
		/*Do Nothing*/
	}

	else if((copyu8Port == GPIO_PORTB) && ((copyu8Pin == GPIO_PIN3) ||(copyu8Pin == GPIO_PIN4)))
	{
		/*Do Nothing*/
	}

	else
	{
		switch(copyu8Port)
		{
		case GPIO_PORTA:
			GPIOA->PUPDR &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOA->PUPDR |= (copyu8InputMode<<(copyu8Pin *2));
			break;

		case GPIO_PORTB:
			GPIOB->PUPDR &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOB->PUPDR |= (copyu8InputMode<<(copyu8Pin *2));
			break;

		case GPIO_PORTC:
			GPIOC->PUPDR &= ~(TWO_BIT_MASK <<(copyu8Pin *2));
			GPIOC->PUPDR |= (copyu8InputMode<<(copyu8Pin *2));
			break;

		default:
			break;
		}
	}
}

void MGPIO_voidSetAF(u8 copy_u8PORT, u8 copy_u8PIN, u8 copy_u8AlternateFunctionNo)
{
	switch (copy_u8PORT)
	{
	case GPIO_PORTA:
		if (copy_u8PIN<8)
		{
			GPIOA->AFRL |= (copy_u8AlternateFunctionNo<<(copy_u8PIN*4));
		}
		else
		{
			GPIOA->AFRH |= (copy_u8AlternateFunctionNo<<((copy_u8PIN-8)*4));
		}
		break;
	case GPIO_PORTB:
		if (copy_u8PIN<8)
		{
			GPIOB->AFRL |= (copy_u8AlternateFunctionNo<<(copy_u8PIN*4));
		}
		else
		{
		}
	}
}


void MGPIO_voidSetPinValue(u8 copyu8Port, u8 copyu8Pin, u8 copyu8Output)
{
	if((copyu8Port == GPIO_PORTA) && ((copyu8Pin == GPIO_PIN13) ||(copyu8Pin == GPIO_PIN14)||(copyu8Pin == GPIO_PIN15)))
	{
		/*Do Nothing*/
	}

	else if((copyu8Port == GPIO_PORTB) && ((copyu8Pin == GPIO_PIN3) ||(copyu8Pin == GPIO_PIN4)))
	{
		/*Do Nothing*/
	}

	else
	{
		switch(copyu8Port)
		{
		case GPIO_PORTA:
			switch(copyu8Output)
			{
			case GPIO_PIN_HIGH:
				SET_BIT(GPIOA->ODR , copyu8Pin);
				break;

			case GPIO_PIN_LOW:
				CLR_BIT(GPIOA->ODR , copyu8Pin);
				break;

			default:
				break;
			}
			break;

			case GPIO_PORTB:
				switch(copyu8Output)
				{
				case GPIO_PIN_HIGH:
					SET_BIT(GPIOB->ODR , copyu8Pin);
					break;

				case GPIO_PIN_LOW:
					CLR_BIT(GPIOB->ODR , copyu8Pin);
					break;

				default:
					break;
				}
				break;

				case GPIO_PORTC:
					switch(copyu8Output)
					{
					case GPIO_PIN_HIGH:
						SET_BIT(GPIOC->ODR , copyu8Pin);
						break;

					case GPIO_PIN_LOW:
						CLR_BIT(GPIOC->ODR , copyu8Pin);
						break;

					default:
						break;
					}
					break;

					default:
						break;
		}
	}
}

void MGPIO_voidGetPinValue(u8 copyu8Port, u8 copyu8Pin, u8 *pu8Return)
{
	if((copyu8Port == GPIO_PORTA) && ((copyu8Pin == GPIO_PIN13) ||(copyu8Pin == GPIO_PIN14)||(copyu8Pin == GPIO_PIN15)))
	{
		/*Do Nothing*/
	}

	else if((copyu8Port == GPIO_PORTB) && ((copyu8Pin == GPIO_PIN3) ||(copyu8Pin == GPIO_PIN4)))
	{
		/*Do Nothing*/
	}

	else
	{
		switch(copyu8Port)
		{
		case GPIO_PORTA:
			*pu8Return = GET_BIT(GPIOA->IDR ,copyu8Pin);
			break;

		case GPIO_PORTB:
			*pu8Return = GET_BIT(GPIOB->IDR ,copyu8Pin);
			break;

		case GPIO_PORTC:
			*pu8Return = GET_BIT(GPIOC->IDR ,copyu8Pin);
			break;

		default:
			break;
		}
	}
}

void MGPIO_voidSetResetPin(u8 copyu8Port, u8 copyu8Pin, u8 copyu8SetResetValue)
{
	if((copyu8Port == GPIO_PORTA) && ((copyu8Pin == GPIO_PIN13) ||(copyu8Pin == GPIO_PIN14)||(copyu8Pin == GPIO_PIN15)))
	{
		/*Do Nothing*/
	}

	else if((copyu8Port == GPIO_PORTB) && ((copyu8Pin == GPIO_PIN3) ||(copyu8Pin == GPIO_PIN4)))
	{
		/*Do Nothing*/
	}

	else
	{
		switch(copyu8Port)
		{
		case GPIO_PORTA:
			switch(copyu8SetResetValue)
			{
			case GPIO_SET:
				GPIOA->BSRR = (1 <<copyu8Pin);
				break;

			case GPIO_RESET:
				GPIOA->BSRR = (1 <<(copyu8Pin +16));
				break;

			default:
				break;
			}
			break;

			case GPIO_PORTB:
				switch(copyu8SetResetValue)
				{
				case GPIO_SET:
					GPIOB->BSRR = (1 <<copyu8Pin);
					break;

				case GPIO_RESET:
					GPIOB->BSRR = (1 <<(copyu8Pin +16));
					break;

				default:
					break;
				}
				break;

				case GPIO_PORTC:
					switch(copyu8SetResetValue)
					{
					case GPIO_SET:
						GPIOC->BSRR = (1 <<copyu8Pin);
						break;

					case GPIO_RESET:
						GPIOC->BSRR = (1 <<(copyu8Pin +16));
						break;

					default:
						break;
					}
					break;

					default:
						break;
		}
	}
}



void MGPIO_voidSetHalfPortMode(u8 copyu8Port, u16 copyu16Mode)
{
	switch(copyu8Port)
	{
	case GPIO_PORTA_FIRST_HALF:

		GPIOA->MODER &= ~(SIXTEEN_BITS_MASK);
		GPIOA->MODER |= copyu16Mode;

//		if(GPIO_INPUT == copyu16Mode)
//		{
//			GPIOA->MODER &= ~(SIXTEEN_BITS_MASK);
//		}
//		else if(GPIO_OUTPUT == copyu16Mode)
//		{
//			GPIOA->MODER &= ~(SIXTEEN_BITS_MASK);
//			GPIOA->MODER |= HALF_PORT_OUTPUT;
//		}
//		else if(GPIO_ALT_FUNC == copyu16Mode)
//		{
//			GPIOA->MODER &= ~(SIXTEEN_BITS_MASK);
//			GPIOA->MODER |= HALF_PORT_ALTERNATE_FUNCTION;
//		}
//		else if(GPIO_ANALOG == copyu16Mode)
//		{
//			GPIOA->MODER &= ~(SIXTEEN_BITS_MASK);
//			GPIOA->MODER |= HALF_PORT_ANALOG;
//		}
//		else
//		{
//			GPIOA->MODER &= ~(SIXTEEN_BITS_MASK);
//			GPIOA->MODER |= copyu16Mode
//		}
		break;

//	case GPIO_PORTB_SECOND_HALF:
//
//		GPIOB->MODER &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
//		GPIOB->MODER |= (copyu16Mode << SIXTEEN_BIT_OFFSET);
//
////		if(GPIO_INPUT == copyu16Mode)
////		{
////			GPIOB->MODER &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
////		}
////		else if(GPIO_OUTPUT == copyu16Mode)
////		{
////			GPIOB->MODER &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
////			GPIOB->MODER |= (GPIO_HALF_PORT_OUTPUT << SIXTEEN_BIT_OFFSET);
////		}
////		else if(GPIO_ALT_FUNC == copyu16Mode)
////		{
////			GPIOB->MODER &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
////			GPIOB->MODER |= (GPIO_HALF_PORT_ALTERNATE_FUNCTION << SIXTEEN_BIT_OFFSET);
////		}
////		else if(GPIO_ANALOG == copyu16Mode)
////		{
////			GPIOB->MODER &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
////			GPIOB->MODER |= (GPIO_HALF_PORT_ANALOG << SIXTEEN_BIT_OFFSET);
////		}
////		else
////		{
////			GPIOB->MODER &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
////			GPIOB->MODER |= (copyu16Mode << SIXTEEN_BIT_OFFSET);
////		}
//		break;

	default:
		break;
	}
}

void MGPIO_voidSetHalfPortOutputMode(u8 copyu8Port, u8 copyu8OutputMode , u16 copyu16Speed)
{
	switch(copyu8Port)
	{
	case GPIO_PORTA_FIRST_HALF:

		GPIOA->OSPEEDR &= ~(SIXTEEN_BITS_MASK);
		GPIOA->OSPEEDR |= copyu16Speed;

		GPIOA->OTYPER &= ~(EIGHT_BITS_MASK);
		GPIOA->OTYPER |= copyu8OutputMode;

		break;

//	case GPIO_PORTB_SECOND_HALF:
//
//		GPIOB->OSPEEDR &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
//		GPIOB->OSPEEDR |= (copyu16Speed << SIXTEEN_BIT_OFFSET);
//
//		GPIOB->OTYPER &= ~(EIGHT_BITS_MASK << SIXTEEN_BIT_OFFSET);
//		GPIOB->OTYPER |= (copyu8OutputMode << SIXTEEN_BIT_OFFSET);
//
//		break;

	default:
		break;
	}
}

void MGPIO_voidSetHalfPortInputMode(u8 copyu8Port, u16 copyu16InputMode)
{
	switch(copyu8Port)
	{
	case GPIO_PORTA_FIRST_HALF:

		GPIOA->PUPDR &= ~(SIXTEEN_BITS_MASK);
		GPIOA->PUPDR |= copyu16InputMode;

		break;

//	case GPIO_PORTB_SECOND_HALF:
//
//		GPIOB->PUPDR &= ~(SIXTEEN_BITS_MASK << SIXTEEN_BIT_OFFSET);
//		GPIOB->PUPDR |= (copyu16InputMode << SIXTEEN_BIT_OFFSET);
//
//		break;

	default:
		break;
	}
}

void MGPIO_voidSetHalfPortValue(u8 copyu8Port, u8 copyu8Output)
{
	switch(copyu8Port)
	{
	case GPIO_PORTA_FIRST_HALF:
		if(GPIO_HALF_PORT_LOW == copyu8Output)
		{
			GPIOA->ODR &= ~(EIGHT_BITS_MASK);
		}
		else
		{
			GPIOA->ODR &= ~(EIGHT_BITS_MASK);
			GPIOA->ODR |= copyu8Output;
		}
		break;
//	case GPIO_PORTB_SECOND_HALF:
//		if(GPIO_HALF_PORT_LOW == copyu8Output)
//		{
//			GPIOB->ODR &= ~(EIGHT_BITS_MASK<<EIGHT_BITS_OFFSET);
//		}
//		else
//		{
//			GPIOB->ODR &= ~(EIGHT_BITS_MASK<<EIGHT_BITS_OFFSET);
//			GPIOB->ODR |= (copyu8Output<<EIGHT_BITS_OFFSET);
//		}
//		break;

	default:
		break;
	}
}

void MGPIO_voidGetHalfPortValue(u8 copyu8Port, u8 *pu8Return)
{

	switch (copyu8Port) {
	case GPIO_PORTA_FIRST_HALF:
		*pu8Return = (u8)GPIOA->IDR;
		break;

//	case GPIO_PORTB_SECOND_HALF:
//		*pu8Return = ((u8)(GPIOB->IDR >> EIGHT_BITS_OFFSET));
//		break;

	default:
		break;
	}
}




void MGPIO_voidSetResetHalfPort(u8 copyu8Port, u8 copyu8SetResetValue)
{
	switch(copyu8Port)
	{
	case GPIO_PORTA_FIRST_HALF:
		if(GPIO_HALF_PORT_LOW == copyu8SetResetValue)
		{
			GPIOA->BSRR = (EIGHT_BITS_MASK << SIXTEEN_BIT_OFFSET);
		}
		else
		{
			GPIOA->BSRR = (EIGHT_BITS_MASK << SIXTEEN_BIT_OFFSET);
			GPIOA->BSRR = copyu8SetResetValue;
		}
		break;
//	case GPIO_PORTB_SECOND_HALF:
//		if(GPIO_HALF_PORT_RESET == copyu8SetResetValue)
//		{
//			GPIOB->BSRR = (EIGHT_BITS_MASK << (SIXTEEN_BIT_OFFSET + EIGHT_BITS_OFFSET));
//		}
//		else
//		{
//			GPIOB->BSRR = (EIGHT_BITS_MASK << (SIXTEEN_BIT_OFFSET + EIGHT_BITS_OFFSET));
//			GPIOB->BSRR = (copyu8SetResetValue << EIGHT_BITS_OFFSET);
//		}
//		break;

	default:
		break;
	}
}







