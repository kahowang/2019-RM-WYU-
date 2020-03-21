#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_
#include "pid.h"
#include "bsp_can.h"     
#include "mytype.h" 
#include "motor_ctr.h"
#include "Remote_Control.h"
#include "usart.h"
#include "mainpp.h" 
#include "config.h"
#include "tim.h"
#include "bsp_uart.h" 

#define  perspective_catch         1  //ץȡ�ӽ�
#define  perspective_embrace      -1  //�����ӽ�

extern int32_t  ref_perspective_angle;
extern int32_t  ref_perspective_angle_back ;   //���ӽǶ� 180
extern int32_t  ref_perspective_angle_front ;   //ǰ�ӽǶ� 0
void pid_perspective_fcn(void);

#endif