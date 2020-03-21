#include "bsp_uart.h"



UART_TypeDef  uart1;

extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;



void Uart_Rx_Dma(void)	
{
  
  
	if(__HAL_UART_GET_IT_SOURCE(&huart1,UART_IT_IDLE) != RESET)
	{
	    HAL_UART_DMAStop(&huart1);
		
		  uart1.Uart_Rx_len = ( Uart_Rx_buf_len - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx));
		
		  HAL_UART_Receive_DMA(&huart1,uart1.Uart__Rx_buf,Uart_Rx_buf_len);
		
		  uart1.Uart_Rx_Status = 1;		 		 
	}
	
	__HAL_UART_CLEAR_IDLEFLAG(&huart1);
}


void Uart_Rx_Init()
{	
		__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);	
	 HAL_UART_Receive_DMA(&huart1,uart1.Uart__Rx_buf,Uart_Rx_buf_len);

}
