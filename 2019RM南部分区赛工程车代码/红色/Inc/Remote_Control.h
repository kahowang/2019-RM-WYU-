/**
  ******************************************************************************
  * @file    Remote_Control.h
  * @author  Ginger
  * @version V1.0.0
  * @date    2015/11/14
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
	
#ifndef __RC__
#define __RC__
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#define RC_Frame_Lentgh		18

#define KEY_W 				((uint16_t)1 << 0)&remote_control.keyBoard.key_code
#define KEY_S 				((uint16_t)1 << 1)&remote_control.keyBoard.key_code 
#define KEY_A 				((uint16_t)1 << 2)&remote_control.keyBoard.key_code
#define KEY_D 				((uint16_t)1 << 3)&remote_control.keyBoard.key_code
#define KEY_SHIFT 		((uint16_t)1 << 4)&remote_control.keyBoard.key_code
#define KEY_CTRL 			((uint16_t)1 << 5)&remote_control.keyBoard.key_code
#define KEY_Q 				((uint16_t)1 << 6)&remote_control.keyBoard.key_code
#define KEY_E 				((uint16_t)1 << 7)&remote_control.keyBoard.key_code
#define KEY_R 				((uint16_t)1 << 8)&remote_control.keyBoard.key_code
#define KEY_F 				((uint16_t)1 << 9)&remote_control.keyBoard.key_code
#define KEY_G 				((uint16_t)1 << 10)&remote_control.keyBoard.key_code
#define KEY_Z 				((uint16_t)1 << 11)&remote_control.keyBoard.key_code
#define KEY_X 				((uint16_t)1 << 12)&remote_control.keyBoard.key_code
#define KEY_C 				((uint16_t)1 << 13)&remote_control.keyBoard.key_code
#define KEY_V 				((uint16_t)1 << 14)&remote_control.keyBoard.key_code
#define KEY_B 				((uint16_t)1 << 15)&remote_control.keyBoard.key_code

typedef struct {
	int16_t ch1;	//each ch value from -364 -- +364
	int16_t ch2;
	int16_t ch3;
	int16_t ch4;
	
	uint8_t switch_left;	//3 value
	uint8_t switch_right;
	
	struct {
		int16_t x;
		int16_t y;
		int16_t z;
	
		uint8_t press_left;
		uint8_t press_right;
	}mouse;
	
	struct {
		uint16_t key_code;
/**********************************************************************************
   * ¼üÅÌÍ¨µÀ:15   14   13   12   11   10   9   8   7   6     5     4   3   2   1
   *          V    C    X	  Z    G    F    R   E   Q  CTRL  SHIFT  D   A   S   W
************************************************************************************/

	}keyBoard;
	

}RC_Type;



enum{
	Switch_Up = 1,
	Switch_Middle = 3,
	Switch_Down = 2,
};

enum{
	Key_W,
	Key_S,
	//...
};

//remote data process
typedef struct
{
    int16_t forward_back_ref;
    int16_t left_right_ref;
    int16_t rotate_ref;
}ChassisSpeed_Ref_t;

extern RC_Type remote_control;
extern ChassisSpeed_Ref_t ChassisSpeedRef;
void Callback_RC_Handle(RC_Type* rc, uint8_t* buff);
#endif


