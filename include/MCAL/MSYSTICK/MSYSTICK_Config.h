/*
 * MSYSTICK_Config.h
 *
 *  Created on: 30-04-2024
 *   Author: Marwan Aboulfath
 *
 */
#ifndef MSYSTICK_CONFIG_H_
#define MSYSTICK_CONFIG_H_

#define SYSTEM_CLOCK		16000000UL

/* CLK_SRC
 * 1- SYSTICK_AHB_PRESCALER_BY_1
 * 2- SYSTICK_AHB_PRESCALER_BY_8
 */

#define CLK_SRC				SYSTICK_AHB_PRESCALER_BY_8


#endif /* MSYSTICK_CONFIG_H_ */
