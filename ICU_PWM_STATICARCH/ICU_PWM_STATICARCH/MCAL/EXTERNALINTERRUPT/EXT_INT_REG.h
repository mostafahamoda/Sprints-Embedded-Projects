/*
 * EXT_INT_REG.h
 *
 * Created: 1/11/2020 5:23:24 PM
 *  Author: mostafahamoda1995
 */ 


#ifndef EXT_INT_REG_H_
#define EXT_INT_REG_H_
#include "Platform_Types.h"
#include "Common_Macros.h"
#define MCUCR_REG (*(volatile u8 * const)0x0055)
#define MCUCSR_REG (*(volatile u8 * const)0x0054)
#define GIFR_REG (*(volatile u8 * const)0x005A)
#define GICR_REG (*(volatile u8 * const)0x005B)
#define SREG_EXT_INT_REG  (*(volatile u8 * const)0x005F)
#define INT_ZERO 0 
#define INT_ONE 1 
#define INT_TWO 2 
#define RISING_EDGE 1 
#define FALLING_EDGE 0
#define ANY_EDGE 2
#define ISC00 0 
#define ISC01 1
#define ISC10 2 
#define ISC11 3 
#define ISC2 6
#define INT0 6 
#define INT1 7
#define INT2 5
#define INTF1 7
#define INTF0 6 
#define INTF2 5
#define I_EXT_INT 7
#endif /* EXT_INT_REG_H_ */