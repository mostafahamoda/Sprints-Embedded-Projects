/*
 * ADC_Head.h
 *
 * Created: 3/5/2019 4:31:59 PM
 *  Author: mostafahamoda1995
 */ 


#ifndef ADC_HEAD_H_
#define ADC_HEAD_H_
typedef unsigned short uint16 ;
void ADC_vInit_manual(char x) ;
uint16 ADC_vRead_manual(void) ;
char ADC_vRead_manual_8bits(void) ;
#endif /* ADC_HEAD_H_ */