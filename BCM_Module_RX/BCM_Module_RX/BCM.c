/*
 * BCM.c
 *
 * Created: 12/24/2019 7:20:04 AM
 *  Author: mostafahamoda1995
 */ 
#include "BCM.h"
uint32_t BCM_State ;
uint32_t i_count =0 ;
uint32_t Data_Length_BCM ;
static uint32_t Address_Data ;
uint8_t* REC_Address ;
uint32_t * REC_Length ; 
uint32_t i_count_RX ;
typedef struct {
		uint8_t ID ;	
		uint16_t Data_length ;
		uint32_t Address ;
		uint8_t CHECK_SUM ;
		uint8_t LOCKED_S ;
	} BCM_CONFIG_BUFFER;
BCM_CONFIG_BUFFER BCM_CNFG_BUFF ;
/******************Writing BCM_INIT*********************************/
BCM_ERROR BCM_Init(strBCM_Cfg* BCM_Config)
{	
	if(BCM_CNFG_BUFF.LOCKED_S == LOCKED)
	{
		return ERROR_NOK ;
	}
	/************Initializing the UART ********************/
	strUART_Config CFG_STRUCT_1 ;
	CFG_STRUCT_1.u16_BaudRate = BCM_Config->BaudRate ;
	CFG_STRUCT_1.u8_DataBits = DATA_BITS ;
	CFG_STRUCT_1.u8_Duplex = FULL_DUPLEX ;
	CFG_STRUCT_1.u8_Interrupt = INTERRUPT_MODE ;
	CFG_STRUCT_1.u8_Parity = PARITY_DISABLED ;
	CFG_STRUCT_1.u8_SpeedMode = DOUBLE_SPEED ;
	CFG_STRUCT_1.u8_StopBits = ONE_STOP ;
	CFG_STRUCT_1.u8_Sync = ASYNCHRONOUS ;
	strUART_Config *CFG_STRUCT_2 = &CFG_STRUCT_1 ;
	UART_init(CFG_STRUCT_2) ;
	/***********Copying the Data Address and the ID *******/
	BCM_CNFG_BUFF.Address = BCM_Config->Address ;
	BCM_CNFG_BUFF.Data_length = BCM_Config->Data_length ;
	/******************************************************/	
	BCM_CNFG_BUFF.ID = BCM_Config->ID ;
	BCM_CNFG_BUFF.LOCKED_S = LOCKED ;
	Data_Length_BCM = BCM_CNFG_BUFF.Data_length + FRAME_SIZE ;
	return ERROR_OK;
}
/***********************Configuring the Dispatcher*******************/
BCM_STATE BCM_DISPATCHER(void)
{
	BCM_STATE VAL;
	char* Address_G;
	char Data_Send;
	switch(BCM_State)
	{
		case IDLE:
		VAL = IDLE ; 
		break;
		case SENDING_BYTE:
		/********Checking that the Frame Sent is Completed********/
		if(i_count<FRAME_SIZE)
		{
			Address_G = &BCM_CNFG_BUFF ;
			Data_Send = *(Address_G+i_count);
			BCM_CNFG_BUFF.CHECK_SUM = BCM_CNFG_BUFF.CHECK_SUM + Data_Send ;
			UART_sendByte(Data_Send);
		}
		else if((i_count>=FRAME_SIZE)&&(i_count<Data_Length_BCM))
		{
			Address_G = BCM_CNFG_BUFF.Address ;
			Data_Send = *(Address_G+i_count-FRAME_SIZE);
			BCM_CNFG_BUFF.CHECK_SUM = BCM_CNFG_BUFF.CHECK_SUM + Data_Send ;
			UART_sendByte(Data_Send);
		}
		else if(i_count>=Data_Length_BCM)
		{
			BCM_State = FRAME_COMPLETE ;
		}
		VAL = SENDING_BYTE ;
		break ;
		case SENDING_COMPLETE:
		/********Checking that the Frame Sent is Completed********/
		if(i_count<FRAME_SIZE)
		{
			Address_G = &BCM_CNFG_BUFF ;
			Data_Send = *(Address_G+i_count);
			//PORTB = Data_Send ;
			BCM_CNFG_BUFF.CHECK_SUM = BCM_CNFG_BUFF.CHECK_SUM + Data_Send ;
			UART_sendByte(Data_Send);
		}
		else if((i_count>=FRAME_SIZE)&&(i_count<Data_Length_BCM))
		{
			Address_G = BCM_CNFG_BUFF.Address ;
			Data_Send = *(Address_G+i_count-FRAME_SIZE);
			BCM_CNFG_BUFF.CHECK_SUM = BCM_CNFG_BUFF.CHECK_SUM + Data_Send ;
			UART_sendByte(Data_Send);
		}
		else if(i_count>=Data_Length_BCM)
		{
			BCM_State = FRAME_COMPLETE ;
		}
		VAL = SENDING_COMPLETE ;
		break;
		case FRAME_COMPLETE:
		BCM_CNFG_BUFF.LOCKED_S = UNLOCKED ; 
		VAL =  BCM_CNFG_BUFF.CHECK_SUM ;
		break;
		default:
		break;
	}
	return ERROR_OK ;
}
/*********************BCM SEND*****************************/
BCM_ERROR BCM_Send(uint32_t ID)
{
	uint8_t Data_Send ;
	//Data_Length_BCM = BCM_CNFG_BUFF.Data_length + FRAME_SIZE ; 
	Address_Data = BCM_CNFG_BUFF.Address ;
	char * Address_G = &BCM_CNFG_BUFF ; 
	/************Constructing the Transmition Frame*************/
	Data_Send = *(Address_G); /*******Accessing the Data in Address*/
	UART_sendByte(Data_Send);/********Sending the UART Through the UART Channel**/
	return ERROR_OK ;
} 
/**********The Setup Function For Storing */
BCM_ERROR BCM_Setup_RX(uint32_t *Address_RX,uint32_t Data_Length_RX)
{
	/**********Storing the Addresses in the Global Variables**/
	/*****Storing the Data Reception Adress*/
	REC_Address = Address_RX ;
	/*****Storing the Data Length Address***/
	REC_Length = Data_Length_RX ;
}
/************Dispatcher for Filling the Buffer Array****/
BCM_STATE BCM_DISPATCHER_RX(void) 
{
	/***********The Return Value of the Function********/
	BCM_STATE VAL;
	/********Checking if the Data Counter is in Range***/
	if(i_count_RX<REC_Length)
	{
		UART_recieveByte((REC_Address+i_count_RX)) ;
		PORTB = *(REC_Address+i_count_RX) ;
		VAL = ERROR_OK ;
	}
	else
	{
		VAL = ERROR_OK ;
	}
}
