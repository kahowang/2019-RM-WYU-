#include "imu.h"
int low;   // ����λ
int High;  // ����λ
int int_angle;
float float_angle;
float imu_angle;
/*ѹ��BCD��תΪʮ������*/

int zipBCD(uint8_t n)  
{
	low = n & 15;          //  n & 00001111  ȡ������λ
	High = (n >> 4) * 10; //   n ������λ��ȡ������λ���ٳ�10
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