/*
 * Timers_Regs.h
 *
 * Created: 11/7/2019 8:55:21 AM
 *  Author: mostafahamoda1995
 */ 


#ifndef TIMERS_REGS_H_
#define TIMERS_REGS_H_
# include "Std_Types.h"
# include "Common_Macros.h"
# include "Platform_Types.h"
/*General Registers*/
# define TIMSK_Reg (*(volatile u8 * const)0x0059)
# define TIFR_Reg (*(volatile u8 * const)0x0058)
# define SREG_REG (*(volatile u8 * const)0x005F)
/*Timer0 Registers*/
# define CS00_Reg 0		
# define CS01_Reg 1 
# define CS02_Reg 2
# define OCF0_Reg 1 
# define WGM01_Reg 3 
# define COM00_Reg 4
# define OC0_Reg 3 
# define COM01_Reg 5 
# define WGM00_Reg 6 
# define FOC0_Reg  7
# define OCF0_reg 1
# define TOV0_Reg 0
# define OCIE0_reg 1
# define TOIE0_reg 0
# define Sei_Reg 7
# define TCCR0_Reg (*(volatile u8 * const) 0x0053) 
# define TCNT0_Reg (*(volatile u8 * const)0x0052) 
# define OCR0_Reg (*(volatile u8 * const)0x005C)
/*Timer 1 Registers*/
#define TCCR1A_Reg (*(volatile u8 * const)0x004F)
#define TCCR1B_Reg (*(volatile u8 * const)0x004E)
#define TCNT1H_Reg (*(volatile u8 * const)0x004D)
#define TCNT1L_Reg (*(volatile u8 * const)0x004C)
#define TCNT1_Reg (*(volatile u16 * const)0x004C)
#define OCR1AH_Reg (*(volatile u8 * const)0x004B)
#define OCR1AL_Reg (*(volatile u8 * const)0x004A)
#define OCR1A (*(volatile u16 * const)0x004A)
#define OCR1BH_Reg (*(volatile u8 * const)0x0049)
#define OCR1BL_Reg (*(volatile u8 * const)0x0048)
#define TIMSK_Reg (*(volatile u8 * const)0x0059)
#define OCF1A_Reg 4
#define WGM10_Reg 0
#define WGM11_Reg 1
#define WGM12_Reg 3
#define WGM13_Reg 4
#define CS10_Reg 0
#define CS11_Reg 1
#define CS12_Reg 2
#define TOIE1_Reg 2
#define OCIE1A_Reg 4
#define COM1A1_Reg 7
#define COM1A0_Reg 6
#define FOC1A_Reg 3
#define FOC1B_Reg 2
/*Timer 2 Registers*/
# define CS20_Reg 0
# define CS21_Reg 1
# define CS22_Reg 2
# define OCF2_Reg 7
# define WGM21_Reg 3
# define COM20_Reg 4
# define COM21_Reg 5
# define WGM20_Reg 6
# define FOC2_Reg  7
# define OCF2_reg 7
# define TOV2_Reg 6
# define OCIE2_reg 7
# define TOIE2_reg 6
# define OC2_Reg 7
# define Sei_Reg 7
# define TCCR2_Reg (*(volatile u8 * const) 0x0045)
# define TCNT2_Reg (*(volatile u8 * const)0x0044)
# define OCR2_Reg (*(volatile u8 * const)0x0043)
#endif /* TIMERS_REGS_H_ */