/*
 * DIO.h
 *
 * Created: 11/1/2019 5:06:53 PM
 *  Author: A.Elkady
 */ 


#ifndef DIO_H_
#define DIO_H_

/*
*	Header files inclusions
*/
#include "Data_Types.h"
#include "DIO_CONFIG.h"
#include "DIO_Ret_Val.h"
/*
*	Used macros
*/
#define LOW 0u
#define HIGH 1u

#define INPUT 0u
#define OUTPUT 1u

/** 
 * \brief  DIO_Pin_Write : Making a certain pin LOW or HIGH 
 *
 * \param  u8Pin_number (Input) : The micro controller pin number (A0 ... D7)
 * \param  u8Value (Input) : LOW or HIGH (Macros) (If other values except for HIGH or LOW is entered the function does nothing)
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/     
extern Error DIO_Pin_Write(u8 u8Pin_number , u8 u8Value);

/** 
 * \brief  DIO_Pin_Read : Reading a certain pin if it's LOW or HIGH and put the vale in the passed address
 *
 * \param  u8Pin_number (Input) : The micro controller pin number (A0 ... D7)
 * \param  *pu8Reading (OUTPUT) : The pin state will be stored in the space that this pointer points to
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/  
extern Error DIO_Pin_Read(u8 u8Pin_number , u8 *pu8Reading);

/** 
 * \brief DIO_Pin_Init : Making a certain pin Input or OUTPUT
 *
 * \param u8Pin_number (Input) : The micro controller pin number (A0 ... D7)
 * \param u8State (Input) : Determine the state of the chosen pin whether it's INPUT or OUTPUT (macros) 
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/     
extern Error DIO_Pin_Init(u8 u8Pin_number , u8 u8State);

/** 
 * \brief DIO_Pin_Activate_pull_up : Activating the pull up resistor of a certain input pin (The chosen pin has to be an input or the function will be meaningless)
 *
 * \param u8Pin_number (Input) : The micro controller pin number (A0 ... D7)
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/     
extern Error DIO_Pin_Activate_pull_up(u8 u8Pin_number);

/** 
 * \brief  DIO_Port_Write : Making a certain port LOW or HIGH 
 *
 * \param  u8Port_index (Input) : The micro controller port number (A , B , C , D)
 * \param  u8Value (Input) : Writes a certain value to the port
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/    
extern Error DIO_Port_Write(u8 u8Port_index , u8 u8Value);

/** 
 * \brief  DIO_Port_Read : Reads the value of a chosen port
 *
 * \param  u8Port_index (Input) : The micro controller port number (A , B , C , D)
 * \param  *pu8Reading (Output) : The port value will bes stored in it
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/   
extern Error DIO_Port_Read(u8 u8Port_index , u8 *pu8Reading);

/** 
 * \brief  DIO_Port_Direction : Makes the port input or output
 *
 * \param  u8Port_index (Input) : The micro controller port number (A , B , C , D)
 * \param  u8State (Input) : Chosen state INPUT or OUTPUT (macros)
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/  
extern Error DIO_Port_Direction(u8 u8Port_index , u8 u8State);
   
/** 
 * \brief DIO_Port_Activate_pull_up : Activating the pull up resistor of a certain input port (The chosen port has to be an input or the function will be meaningless)
 *
 * \param u8Port_index (Input) : The micro controller port number (A , B , C ,D)
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/   
extern Error DIO_Port_Activate_pull_up(u8 u8Port_index);

/** 
 * \brief DIO_Pin_Toggle : A function that toggle a particular pin ( It has to be output )
 *
 * \param u8Pin_index : The micro controller pin number (A0 ... D7) 
 * \return u8 : The return of this function will be an indication of the execution
 *
 **/     
extern Error DIO_Pin_Toggle(u8 u8Pin_number) ;

#endif /* DIO_H_ */