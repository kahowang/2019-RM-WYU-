#include "lifting.h"
int16_t Z_count_time = 11;  //"Z" 按键的消抖时间为10*100ms
int16_t X_count_time = 11;  //"X" 按键的消抖时间为10*100ms
int16_t C_count_time = 11;  //"C" 按键的消抖时间为10*100ms
int32_t UP_OR_DOWN; //抬升或者下降
int32_t ref_angle2_lifting;//抬升支架
int32_t ref_angle3_lifting;//抬升支架
int32_t ref_angle2_press_lifting;//当前抬升支架
int32_t ref_angle3_press_lifting;//当前抬升支架
int32_t ref_angle_increase_lifting = -100000;  //夹取增加的抬升角度 
int32_t lifting_embrace_giveballet_count_time = 91;  //抬升计时
/*************************Sin函数插值*********************************/
float Sin_up_table[200+2] = {0,6.1684e-05,0.00024672,0.00055506,0.00098664,0.0015413,0.002219,0.0030195,0.0039426,0.0049882,0.0061558,0.0074453,0.0088564,0.010389,0.012042,0.013815,0.015708,0.017721,0.019853,0.022103,0.024472,0.026957,0.02956,0.032278,0.035112,0.03806,0.041123,0.044298,0.047586,0.050986,0.054497,0.058117,0.061847,0.065684,0.069629,0.07368,0.077836,0.082096,0.08646,0.090925,0.095492,0.10016,0.10492,0.10978,0.11474,0.1198,0.12494,0.13018,0.13552,0.14094,0.14645,0.15204,0.15773,0.16349,0.16934,0.17528,0.18129,0.18738,0.19355,0.19979,0.20611,0.2125,0.21896,0.22549,0.23209,0.23875,0.24548,0.25227,0.25912,0.26604,0.273,0.28003,0.28711,0.29424,0.30143,0.30866,0.31594,0.32326,0.33063,0.33804,0.34549,0.35298,0.3605,0.36806,0.37566,0.38328,0.39093,0.39861,0.40631,0.41404,0.42178,0.42955,0.43733,0.44513,0.45295,0.46077,0.4686,0.47645,0.48429,0.49215,0.5,0.50785,0.51571,0.52355,0.5314,0.53923,0.54705,0.55487,0.56267,0.57045,0.57822,0.58596,0.59369,0.60139,0.60907,0.61672,0.62434,0.63194,0.6395,0.64702,0.65451,0.66196,0.66937,0.67674,0.68406,0.69134,0.69857,0.70576,0.71289,0.71997,0.727,0.73396,0.74088,0.74773,0.75452,0.76125,0.76791,0.77451,0.78104,0.7875,0.79389,0.80021,0.80645,0.81262,0.81871,0.82472,0.83066,0.83651,0.84227,0.84796,0.85355,0.85906,0.86448,0.86982,0.87506,0.8802,0.88526,0.89022,0.89508,0.89984,0.90451,0.90907,0.91354,0.9179,0.92216,0.92632,0.93037,0.93432,0.93815,0.94188,0.9455,0.94901,0.95241,0.9557,0.95888,0.96194,0.96489,0.96772,0.97044,0.97304,0.97553,0.9779,0.98015,0.98228,0.98429,0.98618,0.98796,0.98961,0.99114,0.99255,0.99384,0.99501,0.99606,0.99698,0.99778,0.99846,0.99901,0.99944,0.99975,0.99994,1,1};
int32_t Sin_up_y1;  
int32_t Sin_up_y0;
int32_t Sin_up_x1; 
int32_t Sin_up_x0;//每一段都清零
int32_t Sin_up_x;   //每一段都清零
int32_t Sin_up_y;
int Sin_up_count;   //S型曲线上升计数 
/*******************Lifting_DOWN************************/	
float Sin_down_table[200+2] = {1,0.99994,0.99975,0.99944,0.99901,0.99846,0.99778,0.99698,0.99606,0.99501,0.99384,0.99255,0.99114,0.98961,0.98796,0.98618,0.98429,0.98228,0.98015,0.9779,0.97553,0.97304,0.97044,0.96772,0.96489,0.96194,0.95888,0.9557,0.95241,0.94901,0.9455,0.94188,0.93815,0.93432,0.93037,0.92632,0.92216,0.9179,0.91354,0.90907,0.90451,0.89984,0.89508,0.89022,0.88526,0.8802,0.87506,0.86982,0.86448,0.85906,0.85355,0.84796,0.84227,0.83651,0.83066,0.82472,0.81871,0.81262,0.80645,0.80021,0.79389,0.7875,0.78104,0.77451,0.76791,0.76125,0.75452,0.74773,0.74088,0.73396,0.727,0.71997,0.71289,0.70576,0.69857,0.69134,0.68406,0.67674,0.66937,0.66196,0.65451,0.64702,0.6395,0.63194,0.62434,0.61672,0.60907,0.60139,0.59369,0.58596,0.57822,0.57045,0.56267,0.55487,0.54705,0.53923,0.5314,0.52355,0.51571,0.50785,0.5,0.49215,0.48429,0.47645,0.4686,0.46077,0.45295,0.44513,0.43733,0.42955,0.42178,0.41404,0.40631,0.39861,0.39093,0.38328,0.37566,0.36806,0.3605,0.35298,0.34549,0.33804,0.33063,0.32326,0.31594,0.30866,0.30143,0.29424,0.28711,0.28003,0.273,0.26604,0.25912,0.25227,0.24548,0.23875,0.23209,0.22549,0.21896,0.2125,0.20611,0.19979,0.19355,0.18738,0.18129,0.17528,0.16934,0.16349,0.15773,0.15204,0.14645,0.14094,0.13552,0.13018,0.12494,0.1198,0.11474,0.10978,0.10492,0.10016,0.095492,0.090925,0.08646,0.082096,0.077836,0.07368,0.069629,0.065684,0.061847,0.058117,0.054497,0.050986,0.047586,0.044298,0.041123,0.03806,0.035112,0.032278,0.02956,0.026957,0.024472,0.022103,0.019853,0.017721,0.015708,0.013815,0.012042,0.010389,0.0088564,0.0074453,0.0061558,0.0049882,0.0039426,0.0030195,0.002219,0.0015413,0.00098664,0.00055506,0.00024672,6.1684e-05,0,0};
int32_t Sin_down_x1;
int32_t Sin_down_x0; //每一段都清零
int32_t Sin_down_x;  //每一段都清零
int32_t Sin_down_y;
int Sin_down_count;   //S型曲线下降计数
/*********************************************************************/	
int32_t lifting_angle ; //抬升输入角度
int32_t lifting_angle_small = -100;   //离地面高度为100
int32_t lifting_angle_difference;  //角度差值
int32_t lifting_angle_embrace = -888675; //抱柱抬升角度
int32_t lifting_angle_catch = -462433; //夹取抬升角度
int32_t lifting_angle_giveballet = -400000; //供弹抬升角度
/*抬升*/
int Sin_point = 200;  //查表法为200个点
int Sin_control_time_up = 4;  //S型曲线，每经过Sin_control_time  ms就跳到下一个插值
int Sin_control_time_down = 8;  //S型曲线，每经过Sin_control_time  ms就跳到下一个插值
/********************Lifting_UP***********************/

/******************************抬升*******************************************/
void pid_lifting_fcn(void)    //双闭环调速
{	
				/*电机4，5为抬升支架机构电机*/
				pid_calc(&pid_pos[4], moto_chassis[4].total_angle, ref_angle2_lifting);
				pid_calc(&pid_spd[4],moto_chassis[4].speed_rpm/19.2,pid_pos[4].pos_out);
	
				pid_calc(&pid_pos[5], moto_chassis[5].total_angle, ref_angle3_lifting);
				pid_calc(&pid_spd[5],moto_chassis[5].speed_rpm/19.2,pid_pos[5].pos_out);
}  

void pid_lifting_setcurrent_fcn(void)
{
	set_lift_moto_current(&hcan1,pid_spd[4].pos_out, pid_spd[5].pos_out, pid_spd[6].pos_out,0);  //can1 motor4-5 -抬升电机  motor6 切换图传视角电机 
}

void Sin_up_y_calc(void)
{
	/*公式
		     (y1-y0)(x-x0)         (y1-y0)=(Sin_up_table[Sin_up_count+1]-Sin_up_table[Sin_up_count])   (x-x0)=(Sin_up_x-Sin_up_x0)=Sin_up_x   
		y = ---------------	+ y0   y0=Sin_up_table[Sin_up_count]     
					 (x1-x0)             (x1-x0)= Sin_control_time  
	*/
      lifting_angle_difference =  lifting_angle - lifting_angle_small;
			Sin_up_y = lifting_angle_difference*( ((Sin_up_table[Sin_up_count+1]-Sin_up_table[Sin_up_count])*(Sin_up_x))/Sin_control_time_up + Sin_up_table[Sin_up_count] );
			Sin_up_x++;
			if(Sin_up_x >Sin_control_time_up)
			{
				 Sin_up_x = 0;
				 Sin_up_count++;
			}
			if(Sin_up_count>Sin_point)
			{
					Sin_up_count = Sin_point;
			}
			ref_angle2_lifting =  Sin_up_y + lifting_angle_small;
			ref_angle3_lifting =  Sin_up_y + lifting_angle_small;
			Sin_down_count = 0;
			Sin_down_x = 0;
}

void Sin_down_y_calc(void)
{
	    lifting_angle_difference =  lifting_angle - lifting_angle_small;
			Sin_down_y = lifting_angle_difference*( ((Sin_down_table[Sin_down_count+1]-Sin_down_table[Sin_down_count])*(Sin_down_x))/Sin_control_time_down + Sin_down_table[Sin_down_count] );  
			Sin_down_x++;
			if(Sin_down_x >Sin_control_time_down)
			{
				 Sin_down_x = 0;
				 Sin_down_count++;
			}
			if(Sin_down_count>Sin_point)
			{
					Sin_down_count = Sin_point;
			}
			ref_angle2_lifting =  Sin_down_y + lifting_angle_small;
			ref_angle3_lifting =  Sin_down_y + lifting_angle_small;
			Sin_up_count = 0;
			Sin_up_x = 0;
}

void keyboard_remote_control_lifting(void)
{
	  /******************抬升抱柱角度**********************/
		 if((KEY_Z)&&(Z_count_time>10))  //抱柱 抬升,Z_count_time>10  防止1s误按多次
		 {
        ref_perspective_angle = ref_perspective_angle_back;  //视角切换为后	
				ROS_perspective_embrace();         //发布抱柱消息  
			  if( ((lifting_angle != lifting_angle_catch)&&(lifting_angle != lifting_angle_giveballet)) ||(UP_OR_DOWN == 2) ) //防止误触，"C","R","Z不可连按"
				{
					lifting_angle =  lifting_angle_embrace;
				}
				UP_OR_DOWN = UP;
        Z_count_time = 0;  // "Z" 防误触复位
		 }
		 /*********************下降*********************/
		 if((KEY_X)&&(X_count_time>10))    //X_count_time>10  防止1s误按多次
		 {
			     ref_perspective_angle = ref_perspective_angle_front;  //视角切换为前
					 perspective_embrace_publish_flag = 1;    //抱柱夹取ROS标志位复位
				   UP_OR_DOWN = DOWN;  //下降
			     X_count_time = 0;  // "X" 防误触复位
		 }
		 /*********************抬升夹取角度********************/
		 if((KEY_C)&&(C_count_time>10))
		 {
			  ref_perspective_angle = ref_perspective_angle_back;  //视角切换为后
				ROS_perspective_catch();             //发布夹取消息			 
			 if( ((lifting_angle != lifting_angle_embrace)&&(lifting_angle != lifting_angle_giveballet))||(UP_OR_DOWN == 2) ) 
			{
			  lifting_angle = lifting_angle_catch;   
			}	
			 UP_OR_DOWN = UP;
       C_count_time = 0;  // "C" 防误触复位			
		 }
		 /********************供弹抬升开舱一套动作**************************/
		 if(KEY_R)
		 {
			  ref_perspective_angle = ref_perspective_angle_front;  //视角切换为前 
			 if( ((lifting_angle != lifting_angle_catch)&&(lifting_angle != lifting_angle_embrace)) ||(UP_OR_DOWN == 2) ) 
			{
				lifting_embrace_giveballet_count_time = 0; //将供弹动作计时归零
			  lifting_angle = lifting_angle_giveballet;   
			}
		 }
		 	giveballet();
		 /*******************************************************************/
      Sin_Up_or_Down_switch();	
}

void Sin_Up_or_Down_switch(void)   //抬升下降选择函数
{
    if(UP_OR_DOWN == 1)
		{
				Sin_up_y_calc();
		}else if (UP_OR_DOWN == 2)  
		{
				Sin_down_y_calc();
		}else if (UP_OR_DOWN == 3)   //夹取时需要上升的小角度
		{

		}		
}