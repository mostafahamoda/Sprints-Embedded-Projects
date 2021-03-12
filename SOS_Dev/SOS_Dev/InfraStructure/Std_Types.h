/*
 * Std_Types.h
 *
 * Created: 11/6/2019 3:07:23 PM
 *  Author: mostafahamoda1995
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include "Platform_Types.h"


typedef u8  Std_ReturnType;

#define STD_HIGH        0x01U       /* Standard HIGH */
#define STD_LOW         0x00U       /* Standard LOW */

#define STD_ACTIVE      0x01U       /* Logical state active */
#define STD_IDLE        0x00U       /* Logical state idle */

#define STD_ON          0x01U       /* Standard ON */
#define STD_OFF         0x00U       /* Standard OFF */

#define E_OK            ((Std_ReturnType)0x00U)      /* Function Return OK */
#define E_NOT_OK        ((Std_ReturnType)0x01U)      /* Function Return NOT OK */

#endif /* STD_TYPES_H_ */