/*
 * common_macros.h
 *
 *  Created on: Nov 23, 2019
 *      Author: Mario
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_


#define SET_BIT(REG,BIT)	(REG|=(1<<BIT))

#define CLEAR_BIT(REG,BIT)	(REG&=(~(1<<BIT)))

#define TOGGLE_BIT(REG,BIT)	(REG^=(1<<BIT))

#define BIT_IS_SET(REG,BIT)	(REG&(1<<BIT))

#define BIT_IS_CLEAR(REG,BIT)	(!(REG &(1<<BIT)))

#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )


#endif /* COMMON_MACROS_H_ */
