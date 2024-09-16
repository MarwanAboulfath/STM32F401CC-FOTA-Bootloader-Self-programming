/*
 * BIT_map.h
 *
 *  Created on: Aug 14, 2023
 *      Author: Marwa
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(var, Bit_num)                 var |= (1<<Bit_num)
#define CLR_BIT(var, Bit_num)                 var &= (~(1<<Bit_num))
#define TOGGLE_BIT(var, Bit_num)              var ^= (1<<Bit_num)
#define GET_BIT(var, Bit_num)                 ((var>>Bit_num)&1)


#endif /* BIT_MATH_H_ */
