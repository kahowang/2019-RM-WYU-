#include "judge_send.h"
client_custom_data_t client_custom_data;

uint8_t tx_buffer[28] = {0};
uint8_t seq = 0;
uint8_t crc8;
uint8_t crc8_check;
uint16_t wcrc; 

void  judge_send_display_init(void)
{
	 	//client_custom_data.data1 = 3.0f;
		client_custom_data.data2 = 0.0f;
		//client_custom_data.data3 = 10.0f;   
		//client_custom_data.masks = 0;    //修改灯
		crc8 = Get_CRC8_Check_Sum(&tx_buffer[0],5-1,CRC8_INIT);   
		wcrc = Get_CRC16_Check_Sum(tx_buffer,28-2,CRC_INIT);       
		tx_buffer[0] = 0xA5;
		tx_buffer[1] = 19;
		tx_buffer[2] = 0x00;
		tx_buffer[3] = 1;
  	tx_buffer[4] = crc8;
		
		tx_buffer[5] = 0x01;
		tx_buffer[6] = 0x03;
		tx_buffer[7] = 0x80;
		tx_buffer[8] = 0xD1;
		tx_buffer[9] = 12;      //2为红色(工程)，12为蓝色(工程)
		tx_buffer[10] = 0;
		tx_buffer[11] = 0x12;       //0x12为蓝色工程，0x02为红色工程
		tx_buffer[12] = 0x01;
		Float_to_Byte(&client_custom_data.data1,tx_buffer,13);
		Float_to_Byte(&client_custom_data.data2,tx_buffer,17);
		Float_to_Byte(&client_custom_data.data3,tx_buffer,21);
		tx_buffer[25] = client_custom_data.masks;
		tx_buffer[26] = wcrc& 0x00ff;;
		tx_buffer[27] =(wcrc >> 8) & 0xff;
		crc8_check=Verify_CRC8_Check_Sum(tx_buffer,5);
}


void 	judge_send_display(void)  //裁判系统界面交互，包括传输ROS是否断开，电磁铁是否开启的提示
{
	  judge_send_display_init();      //裁判系统界面交互参数初始化
		display_select_change();
		HAL_UART_Transmit_DMA(&huart4,tx_buffer,28);
}

void display_select_change(void)
{
    /*检测是否伸缩*/
	  detection_stretch_catch();
		/*检测ROS是否连上，中间light3-4的灯*/
    detection_ros_connected();
	  /*检测光电*/
	  detection_embrace_ps();
	 /*检测是否打开电磁铁*/
	  detection_Relay_S();
}



void Float_to_Byte(float *target,unsigned char *buf,unsigned char beg)
{
    unsigned char *point;
    point = (unsigned char*)target;
    buf[beg]   = point[0];
    buf[beg+1] = point[1];
    buf[beg+2] = point[2];
    buf[beg+3] = point[3];
}

void detection_stretch_catch(void)
{
		if(stretch_catch == 1)  //缩
		{
			 client_custom_data.data1 = 0.0f;
		}else if (stretch_catch == -1){
			 client_custom_data.data1 = 1.0f;
		}
}

void detection_ros_connected(void)
{
		if (ros_connected == 0)     //没连上灯全红
		{
			 client_custom_data.masks = client_custom_data.masks & Light_Off3 & Light_Off4;      //灭
		}else if (ros_connected == 1){
			 client_custom_data.masks = client_custom_data.masks | Light_On3 | Light_On4;      //light 3-4 亮ROS连上	
		}
}

void  detection_Relay_S(void)
{
	   if(Relay_S_ON_OFF == 1)  //关闭继电器
	 {
	     client_custom_data.data3 = 0.0f;
	 }else if(Relay_S_ON_OFF == -1)  {//开启继电器
			 client_custom_data.data3 = 1.0f; 
	 }
}