#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "allheader.h"



#define Uart_Rx_buf_len   50u


typedef struct
{
	uint8_t Uart__Rx_buf[Uart_Rx_buf_len];
	
	uint8_t Uart_Rx_len:8;
	
	uint8_t Uart_Rx_Status:1;
	
	
	
  uint8_t Head_Com:8;
	
	uint8_t Head_Com_Len:8;
	
	uint8_t Address:8;
	
	uint8_t Com_Code:8;
	
	uint8_t User_Data1:8;
	
	uint8_t User_Data2:8;
	
	uint8_t User_Data3:8;
	
	uint8_t CRC_Sum:8;
	
	
}UART_TypeDef;


extern UART_TypeDef  uart1;




void Uart_Rx_Init(void);


void Uart_Rx_Dma(void);	

#endif
