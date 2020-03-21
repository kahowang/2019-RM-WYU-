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

#define  perspective_catch         1  //抓取视角
#define  perspective_embrace      -1  //抱柱视角

extern int32_t  ref_perspective_angle;
extern int32_t  ref_perspective_angle_back ;   //后视角度 180
extern int32_t  ref_perspective_angle_front ;   //前视角度 0
void pid_perspective_fcn(void);

#endif