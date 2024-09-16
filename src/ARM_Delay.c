/*
 * ARM_Delay.c
 *
 *  Created on: Apr 28, 2024
 *      Author: Marwan
 */

/* Delay Function */
void Delay_MS(unsigned long long n)
{
	volatile unsigned long long count = 0;
	while(count++ < (665 * n) );
}


