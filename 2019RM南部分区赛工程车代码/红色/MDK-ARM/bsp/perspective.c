#include "perspective.h"
#include "mainpp.h"
int32_t  ref_perspective_angle;
int32_t  ref_perspective_angle_jscope;
int32_t  ref_perspective_angle_back = 1475;   //后视角度 180
int32_t  ref_perspective_angle_front = 0;   //前视角度 0 

void pid_perspective_fcn(void)
{
			pid_calc(&pid_pos[6], moto_chassis[6].total_angle/100, ref_perspective_angle);
			pid_calc(&pid_spd[6],moto_chassis[6].speed_rpm,pid_pos[6].pos_out);
	    ref_perspective_angle_jscope =  moto_chassis[6].total_angle/100;
}