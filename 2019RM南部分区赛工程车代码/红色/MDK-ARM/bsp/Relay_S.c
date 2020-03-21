#include "Relay_S.h"  
int Relay_S_ON_OFF = 1;
int Relay_S_count_time;

void Relay_S(void)
{
   if(Relay_S_ON_OFF == 1)  //关闭继电器
	 {
	     HAL_GPIO_WritePin(Relay_S_GPIO_Port, Relay_S_Pin, GPIO_PIN_RESET);
	 }else if(Relay_S_ON_OFF == -1)  {//开启继电器
			 HAL_GPIO_WritePin(Relay_S_GPIO_Port, Relay_S_Pin, GPIO_PIN_SET); 
	 }
}


void keyboard_rescue(void)
{
   if((KEY_V)&&(Relay_S_count_time>15))  //1500ms消抖
	 {
			 Relay_S_ON_OFF = -Relay_S_ON_OFF;
		   Relay_S_count_time = 0; //消抖复位
	 }
	 Relay_S();
	 
}