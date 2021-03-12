/*
 * ADC_h1.h
 *
 * Created: 12/29/2018 11:33:41 AM
 *  Author: mostafahamoda1995
 */ 


#ifndef ADC_H1_H_
#define ADC_H1_H_
void ADC_vInit(void) ;
unsigned short ADC_u16Read(void) ;
#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=~(1<<bit)
#define READ_BIT(reg,bit) ((reg&(1<<bit))>>bit)
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define uint8 unsigned int
#define ROR(reg,n) (reg=((reg<<(REG_BIT-n))|(reg>>n)))
#define ROL(reg,n) (reg=((reg>>(REG_BIT-n))|(reg<<n)))
#endif /* ADC_H1_H_ */