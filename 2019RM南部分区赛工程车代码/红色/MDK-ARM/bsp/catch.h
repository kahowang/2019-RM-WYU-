#ifndef __CATCH_H
#define __CATCH_H
#include "allheader.h"
extern int32_t ref_angle0;//��ȡ����
extern int32_t ref_angle1;//��ȡ���� 
extern int32_t catching_time;
void pid_catching_fcn(void);  //˫�ջ�����
void Sin_up_y_calc_catch(void);
void Sin_down_y_calc_catch(void);
void Step_up_y_calc_catch(void);    //��ȡ�ǶȵĽ�Ծ����
void keyboard_remote_control_catching(void);  //��"Q"���м�ȡ��ת����
void catch_action(void);
#endif