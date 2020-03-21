#ifndef __CATCH_H
#define __CATCH_H
#include "allheader.h"
extern int32_t ref_angle0;//夹取机构
extern int32_t ref_angle1;//夹取机构 
extern int32_t catching_time;
void pid_catching_fcn(void);  //双闭环调速
void Sin_up_y_calc_catch(void);
void Sin_down_y_calc_catch(void);
void Step_up_y_calc_catch(void);    //夹取角度的阶跃输入
void keyboard_remote_control_catching(void);  //按"Q"进行夹取翻转动作
void catch_action(void);
#endif