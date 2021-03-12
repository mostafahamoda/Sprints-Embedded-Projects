/*
 * Key_pad_1.h
 *
 * Created: 2/26/2019 6:49:38 PM
 *  Author: mostafahamoda1995
 */ 


#ifndef KEY_PAD_1_H_
#define KEY_PAD_1_H_
#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=~(1<<bit)
#define READ_BIT(reg,bit) ((reg&(1<<bit))>>bit)
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define ROR(REG,BIT) ((REG>>BIT) | (REG<<(8-BIT)))
#define ROL(REG,BIT) ((REG<<BIT) | (REG<<BIT))
typedef unsigned int uint32 ;
typedef unsigned short uint16 ;
typedef unsigned char uint8 ;
void KeyPad_vInit(void) ;
uint32 KeyPad_vScan(void) ;
#endif /* KEY_PAD_1_H_ */