/*
 * Interrupt.h
 *
 * Created: 11/23/2019 12:07:22 AM
 *  Author: A.Elkady
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/* Special register */ 
#define S_REG    ( *((volatile unsigned char *) (0x5F) ) )    /*GICR*/

/* Definition of the general interrupt bit */
#define GI 7

/** 
 * \brief Enable_Global_Interrupt : A function that enable the global interrupt 
 *
 * \param void
 * \return void
 *
 **/     
extern void Enable_GlobalInterrupt();

/** 
 * \brief Disable_Global_Interrupt : A function that disable the global interrupt 
 *
 * \param void
 * \return void
 *
 **/ 
extern void Disable_GlobalInterrupt();

#endif /* INTERRUPT_H_ */