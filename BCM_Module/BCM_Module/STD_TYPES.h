/*
 * STD_TYPES.h
 *
 *  Created on: Nov 23, 2019
 *      Author: Mario
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#define HIGH 1
#define LOW 0

#define OUTPUT 1
#define INPUT 0

#define ERROR_OK     0
#define ERROR_NOK    1

typedef signed char					ERROR_CHECKING;

typedef unsigned char                uint8_t;							/*Define Type of 1  Unsigned Byte*/
typedef signed char                  sint8_t;							/*Define Type of 1  signed Byte*/
typedef unsigned  int           uint16_t;							/*Define Type of 2  Unsigned Byte*/
typedef signed  int             sint16_t;							/*Define Type of 2  signed Byte*/
typedef unsigned long int            uint32_t ;							/*Define Type of 4  Unsigned Byte*/
typedef signed long int              sint32_t ;							/*Define Type of 4  signed Byte*/
typedef unsigned long long int       uint64_t ;							/*Define Type of 8  Unsigned Byte*/
typedef signed long long int         sint64_t ;							/*Define Type of 8  signed Byte*/
typedef float                        float32_t ;                        /*Define Type of 4  Float Byte */
typedef double                       double64_t ;                       /*Define Type of 8  Double Byte*/

#define NULL  0

#define NULL_POINTER (void *)NULL

#define NULL_CHR NULL

#endif /* STD_TYPES_H_ */
