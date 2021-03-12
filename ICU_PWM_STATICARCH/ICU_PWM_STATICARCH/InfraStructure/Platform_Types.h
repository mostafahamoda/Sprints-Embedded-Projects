/*
 * Platform_Types.h
 *
 * Created: 11/6/2019 3:03:13 PM
 *  Author: mostafahamoda1995
 */ 


#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_
/*
 * CPU register type width
 */
#define CPU_TYPE_8                                  (8U)
#define CPU_TYPE_16                                 (16U)
#define CPU_TYPE_32                                 (32U)

/*
 * Bit order definition
 */
#define MSB_FIRST                   (0u)        /* Big endian bit ordering        */
#define LSB_FIRST                   (1u)        /* Little endian bit ordering     */

/*
 * Byte order definition
 */
#define HIGH_BYTE_FIRST             (0u)        /* Big endian byte ordering       */
#define LOW_BYTE_FIRST              (1u)        /* Little endian byte ordering    */

/*
 * Platform type and endianess definitions, specific for AVR
 */
#define CPU_TYPE            CPU_TYPE_8

#define CPU_BIT_ORDER       LSB_FIRST
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST

/*
 * Boolean Values
 */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

typedef unsigned char         boolean;


typedef unsigned char         u8;          /*           0 .. 255             */
typedef signed char           su8;
typedef unsigned short        u16;
typedef signed short          su16;
typedef unsigned long         u32;
typedef signed long           su32;
typedef unsigned long long    u64;
typedef signed long long      su64;
typedef float                 f32;
typedef double                f64;

/*
typedef signed long long      suint64_t;
typedef unsigned long long    uint64_t;
typedef signed long           suint32_t;        
typedef unsigned long         uint32_t;         
typedef signed short          suint16_t; 
typedef unsigned short        uint16_t;
typedef signed char           suint8_t;
typedef unsigned char         uint8_t;  */       
#endif /* PLATFORM_TYPES_H_ */