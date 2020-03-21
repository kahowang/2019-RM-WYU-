#ifndef _JUDGE_SEND_H_
#define _JUDGE_SEND_H_
#include "allheader.h"
extern uint8_t tx_buffer[28];

typedef struct
{
	float data1;
	float data2;
	float data3;
	uint8_t masks;
}client_custom_data_t;

typedef enum 
{
  Light_On1 = 1,
	Light_On2 = 2,
  Light_On3 = 4,
	Light_On4 = 8, 
	Light_On5 = 16,
	Light_On6 = 32,
}Light_On_TypeDef;

typedef enum 
{
  Light_Off1 = 254,
	Light_Off2 = 253,
  Light_Off3 = 251,
  Light_Off4 = 247,
	Light_Off5 = 239,
	Light_Off6 = 223,
}Light_Off_TypeDef;

extern client_custom_data_t client_custom_data;
void 	judge_send_display(void);
void  judge_send_display_init(void);
void display_select_change(void);
void detection_stretch_catch(void);
void detection_ros_connected(void);
void detection_Relay_S(void);

void Float_to_Byte(float *target,unsigned char *buf,unsigned char beg);
#endif