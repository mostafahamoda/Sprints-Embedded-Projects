/*
 * LCD_head.h
 *
 * Created: 3/1/2019 4:08:59 PM
 *  Author: mostafahamoda1995
 */ 


#ifndef LCD_HEAD_H_
#define LCD_HEAD_H_
#define RS 1
#define RW 2 
#define EN 3 
#define LCD_4
typedef unsigned char uint8 ;
void sendfallingedge(void) ;
void LCD_vClear(void) ;
void LCD_vSendCmd(char cmd) ;
void LCD_vMoveCursor( uint8 row , uint8 col) ;
void LCD_vPrintchar(char Data) ;
void LCD_vPrintstring(char * ptr) ;
void LCD_vInit(void) ;
#endif /* LCD_HEAD_H_ */