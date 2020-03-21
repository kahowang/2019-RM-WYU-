#include "stretch.h"  
int ref_stretch_angle;
int32_t stretch_time;
int stretch_acc_time;  //收缩额外增加时间
int stretch_catch = 1;    //开启伸缩夹取
int jscope_ref_stretch_angle;

void stretch(void)
{
	  /*按键按“B”触发伸缩*/
	  if((KEY_B)&&(stretch_time>15))  //1500ms 的伸缩按键消抖  
		{
			stretch_catch =  -stretch_catch;
			stretch_time = 0; //消抖复位
		}
		/*或者ROS发displacementstretch = 1，触发伸缩*/
		if(ROS_ON_OFF == ON){
		if(displacementstretch ==1)
		{
				stretch_catch = -1;   //displacementstretch=1，伸
			  displacementstretch = 0;
		}
	}
		/*********************************************/
		if(stretch_catch == -1)
		{
			 ref_stretch_angle = -5677;  //伸出
		}else if(stretch_catch == 1){
		   ref_stretch_angle = 0;  //收缩
		}
}

void pid_stretch_fcn(void)  
{
			pid_calc(&pid2_pos[4], moto_upper[4].total_angle/100, ref_stretch_angle);
			pid_calc(&pid2_spd[4],moto_upper[4].speed_rpm/6,pid2_pos[4].pos_out);
			jscope_ref_stretch_angle =  moto_upper[4].total_angle/100;
}

void pid_stretch_setcurrent_fcn(void)
{
			set_stretch_moto_current(&hcan2, pid2_spd[4].pos_out,pid2_spd[5].pos_out,0,0);  //电机输出，速度环->电流环 
}