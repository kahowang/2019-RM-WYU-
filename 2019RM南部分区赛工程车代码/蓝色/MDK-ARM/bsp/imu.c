#include "imu.h"
int low;   // 低四位
int High;  // 高四位
int int_angle;
float float_angle;
float imu_angle;
/*压缩BCD码转为十进制数*/

int zipBCD(uint8_t n)  
{
	low = n & 15;          //  n & 00001111  取出低四位
	High = (n >> 4) * 10; //   n 右移四位，取出高四位，再乘10
	return High + low;
}

void  imu_data_get(void)
{
		if(uart1.Uart_Rx_Status == 1)  
	{
	  uart1.Uart_Rx_Status = 0;
		int_angle   =   zipBCD(uart1.Uart__Rx_buf[4])*100 +  zipBCD(uart1.Uart__Rx_buf[5]);
		float_angle =   zipBCD(uart1.Uart__Rx_buf[6])*0.01 ;
		imu_angle =  int_angle + float_angle;		
	  //printf("the imu_angle is %f\r\n",imu_angle);  
	}
}