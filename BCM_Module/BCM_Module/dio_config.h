/*
 * dio_config.h
 *
 *  Created on: Nov 23, 2019
 *      Author: Mario
 */

#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_


#define BITS_PER_REGISTER 8
#define MAX_PINS 32
#define MAX_PORTS 4
#define INPUTS 0x00
#define OUTPUTS 0xFF
#define MAX 0xFF

#define PORTA (*((volatile unsigned char *)0x3B))
#define DDRA (*((volatile unsigned char *)0x3A))
#define PINA (*((volatile unsigned char *)0x39))

#define PORTB (*((volatile unsigned char *)0x38))
#define DDRB (*((volatile unsigned char *)0x37))
#define PINB (*((volatile unsigned char *)0x36))

#define PORTC (*((volatile unsigned char *)0x35))
#define DDRC (*((volatile unsigned char *)0x34))
#define PINC (*((volatile unsigned char *)0x33))

#define PORTD (*((volatile unsigned char *)0x32))
#define DDRD (*((volatile unsigned char *)0x31))
#define PIND (*((volatile unsigned char *)0x30))

/*#define DDR(X)  (*((volatile uint8*) (0x3A- X*3)))
#define PIN(X)  (*((volatile const uint8*) (0x39- X*3)))
#define PORT(X) (*((volatile uint8*) (0x3B- X*3)))*/

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15
#define C0 16
#define C1 17
#define C2 18
#define C3 19
#define C4 20
#define C5 21
#define C6 22
#define C7 23
#define D0 24
#define D1 25
#define D2 26
#define D3 27
#define D4 28
#define D5 29
#define D6 30
#define D7 31



/* typedef enum PIN_NUMBERS {
	A0=0,A1,A2,A3,A4,A5,A6,A7,
	B0  ,B1,B2,B3,B4,B5,B6,B7,
	C0  ,C1,C2,C3,C4,C5,C6,C7,
	D0  ,D1,D2,D3,D4,D5,D6,D7
    }PIN_NUMBERS; */

/*typedef enum PORT_NUMBER {
	PORT_A=0 ,
	PORT_B,
	PORT_C,
	PORT_D
}PORT_NUMBER;*/







#endif /* DIO_CONFIG_H_ */
