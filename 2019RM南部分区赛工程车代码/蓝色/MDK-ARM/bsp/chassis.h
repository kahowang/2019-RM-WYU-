#ifndef _CHASSIS_H_
#define _CHASSIS_H_  
#include "allheader.h"
#define ON  1
#define OFF 0
extern ramp_function_source_t  set_spd_shift_ramp;
/*���� W A S D б��*/
extern ramp_function_source_t  set_spd_w_ramp; 
extern  ramp_function_source_t  set_spd_a_ramp;   
extern  ramp_function_source_t  set_spd_s_ramp; 
extern  ramp_function_source_t  set_spd_d_ramp;

extern int32_t motor0_angle;
extern int32_t motor1_angle;
extern int32_t motor2_angle;
extern int32_t motor3_angle;

extern int32_t ROS_ON_OFF; 
void pid_chassis_fcn(void);    //PID���Ƽ���
void pid_chassis_setcurrent_fcn(void);    //PID�����������
void chassis_mouse_keyboard(void);
void  press_shift_speed(void);
void mouse_rotate(void);
void remote_ros_switch(void);
#endif