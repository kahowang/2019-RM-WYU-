#include "chassis.h"  
/*******************ROS Kinmatics参数********************/
int32_t motor0_angle;
int32_t motor1_angle;
int32_t motor2_angle;
int32_t motor3_angle;
/*kimatics位移xy*/
extern float displacementx;
extern float displacementy;
extern float displacementz;
extern int ramp_flag;
int32_t ROS_ON_OFF; 
int ROS_ON_FLAG=1;
int ROS_OFF_FLAG=1;  //只执行一次的ROS_ON_OFF标志位
int moto_offset_flag;

/*标志位*/
int Kinematics_displacement_move_flag;

/*在切换模式时，需要复位的 斜坡函数 标志位*/
/*外部调用的斜坡结构体*/  
extern ramp_function_source_t  motor0_ramp;  
extern ramp_function_source_t  motor1_ramp;
extern ramp_function_source_t  motor2_ramp;
extern ramp_function_source_t  motor3_ramp;
/*清零斜坡输入*/
extern int32_t motor0_angle_displacement;
extern int32_t motor1_angle_displacement;
extern int32_t motor2_angle_displacement;
extern int32_t motor3_angle_displacement;
/*清零斜坡输出*/
extern int32_t motor0_angle_ramp;
extern int32_t motor1_angle_ramp;
extern int32_t motor2_angle_ramp;
extern int32_t motor3_angle_ramp;
/******************底盘速度**************************/
ramp_function_source_t  set_spd_shift_ramp;
/*按键 W A S D 斜坡*/
ramp_function_source_t  set_spd_w_ramp; 
ramp_function_source_t  set_spd_a_ramp; 
ramp_function_source_t  set_spd_s_ramp; 
ramp_function_source_t  set_spd_d_ramp; 
int set_spd_w; //按键输出的速度（经过斜坡处理）
int set_spd_a;
int set_spd_s;
int set_spd_d;
int set_spd_default=400;  //底盘默认速度为400rpm
float set_spd_shift=2.0;          //按shift补偿速度系数
int set_spd_rotate;         //鼠标控制旋转
int mouse_control_fb;       //鼠标控制的 Front-Back
int mouse_control_lr;       //鼠标控制的 Left-Right
/*Jscope速度调试*/
int32_t Jscope_chassis0_speed;
int32_t Jscope_chassis1_speed;
int32_t Jscope_chassis2_speed;
int32_t Jscope_chassis3_speed;
/******************************底盘**************************************/
void pid_chassis_fcn(void)    //PID控制计算
{
			Jscope_chassis0_speed =  moto_chassis[0].speed_rpm/19.2;
			Jscope_chassis1_speed =  moto_chassis[1].speed_rpm/19.2;
			Jscope_chassis2_speed =  moto_chassis[2].speed_rpm/19.2;
			Jscope_chassis3_speed =  moto_chassis[3].speed_rpm/19.2;
	/*右侧拨杆在上，没有开启ROS*/
	if(ROS_ON_OFF == OFF)  
	{
				pid_calc(&pid_spd[0],moto_chassis[0].speed_rpm/19.2,set_spd0); 
				pid_calc(&pid_spd[1],moto_chassis[1].speed_rpm/19.2,set_spd1);
				pid_calc(&pid_spd[2],moto_chassis[2].speed_rpm/19.2,set_spd2); 
				pid_calc(&pid_spd[3],moto_chassis[3].speed_rpm/19.2,set_spd3);
	}else if (ROS_ON_OFF == ON)
	{
				pid_calc(&pid_pos_ros[0],moto_chassis[0].total_angle, motor0_angle);
				pid_calc(&pid_spd_ros[0],moto_chassis[0].speed_rpm,pid_pos_ros[0].pos_out);
	
				pid_calc(&pid_pos_ros[1], moto_chassis[1].total_angle, motor1_angle);
				pid_calc(&pid_spd_ros[1],moto_chassis[1].speed_rpm,pid_pos_ros[1].pos_out);
	
				pid_calc(&pid_pos_ros[2], moto_chassis[2].total_angle, motor2_angle);
				pid_calc(&pid_spd_ros[2],moto_chassis[2].speed_rpm,pid_pos_ros[2].pos_out);
	
				pid_calc(&pid_pos_ros[3], moto_chassis[3].total_angle, motor3_angle);
				pid_calc(&pid_spd_ros[3],moto_chassis[3].speed_rpm,pid_pos_ros[3].pos_out);			
	}
}
void pid_chassis_setcurrent_fcn(void)    //PID控制最终输出
{
		if(ROS_ON_OFF == OFF)
		{
			set_moto_current(&hcan1, pid_spd[0].pos_out, 
			pid_spd[1].pos_out,
			pid_spd[2].pos_out,
			pid_spd[3].pos_out);  //电机输出，速度环->电流环
		}else if (ROS_ON_OFF == ON){
			set_moto_current(&hcan1, pid_spd_ros[0].pos_out, pid_spd_ros[1].pos_out,pid_spd_ros[2].pos_out,pid_spd_ros[3].pos_out);
		}
}
/**********************************************************************************/
void chassis_mouse_keyboard(void)
{
					if(KEY_W)    //向前
			{
					ramp_calc(&set_spd_w_ramp, set_spd_default);   //加速
			}else{
					ramp_calc(&set_spd_w_ramp, -set_spd_default);  //减速
			}
					if(KEY_D)    //向右
			{
					ramp_calc(&set_spd_d_ramp, set_spd_default);   //加速
			}else{
					ramp_calc(&set_spd_d_ramp, -set_spd_default);  //减速
			}
					if(KEY_S)    //退后
			{
					ramp_calc(&set_spd_s_ramp, -set_spd_default);   //加速
			}else{
					ramp_calc(&set_spd_s_ramp, set_spd_default);  //减速
			}
					if(KEY_A)    //向左
			{
					ramp_calc(&set_spd_a_ramp, -set_spd_default);   //加速
			}else{
					ramp_calc(&set_spd_a_ramp, set_spd_default);  //减速
			}
			press_shift_speed();  //按shift 加速 ，加速系数为1-2
			set_spd_w =  set_spd_w_ramp.out;
			set_spd_d =  set_spd_d_ramp.out;
			set_spd_s =  set_spd_s_ramp.out;
			set_spd_a =  set_spd_a_ramp.out;
			mouse_control_fb = set_spd_w + set_spd_s;
			mouse_control_lr = set_spd_d + set_spd_a;
		//车轮1（右上）
		set_spd0 = -mouse_control_fb/set_spd_shift + mouse_control_lr/set_spd_shift + set_spd_rotate; 
	
		//车轮2（左上）
		set_spd1 =  mouse_control_fb/set_spd_shift + mouse_control_lr/set_spd_shift + set_spd_rotate;

		//车轮3（左下）
		set_spd2 =  mouse_control_fb/set_spd_shift - mouse_control_lr/set_spd_shift + set_spd_rotate;

		//车轮4（右下）
		set_spd3 = -mouse_control_fb/set_spd_shift - mouse_control_lr/set_spd_shift + set_spd_rotate; 
}

void  press_shift_speed(void)
{
		if(KEY_SHIFT)  //按shift加速
	{
		ramp_calc(&set_spd_shift_ramp, -set_spd_shift);
		set_spd_shift = set_spd_shift_ramp.out;	
		}else{
		ramp_calc(&set_spd_shift_ramp, set_spd_shift);
		set_spd_shift = set_spd_shift_ramp.out;
	}
}

void mouse_rotate(void)
{
		set_spd_rotate = remote_control.mouse.x*6;
}

void remote_ros_switch(void)
{
		if(remote_control.switch_right == Switch_Up)  //拨杆在上，键盘控制底盘模式
		{
			/*关于ROS的标志位清零*/	
				ROS_ON_OFF = OFF;  // 关闭ROS
				Kinematics_displacement_move_flag = 0;  //控制补偿值，拨钮拨一次，只读取一次补偿角度
				/*切换ROS时，将minipc传来的位移信息清零*/
				displacementx = 0.0;
				displacementy = 0.0;
				displacementz = 0.0;
				/*保证斜坡初始化ramp_init()只调用一次*/
				ramp_flag = 1; 
				/*切换模式时清空斜坡函数的输入值，也就是输入的目标角度*/
				motor0_angle_displacement = motor1_angle_displacement = motor2_angle_displacement= motor3_angle_displacement = 0;
				/*清空斜坡的输出值*/
			  motor0_angle_ramp = motor1_angle_ramp = motor2_angle_ramp = motor3_angle_ramp = 0;
				motor0_ramp.out = motor1_ramp.out =motor2_ramp.out = motor3_ramp.out = 0;
			/*ROS_OFF_FLAG作用保证每次拨档只发送一次ROS_ON_OFF*/
				if(ROS_OFF_FLAG == 1)
				{
					ROS_OFF();
					ROS_OFF_FLAG = 0;
				}
				ROS_ON_FLAG = 1;
		}else if(remote_control.switch_right == Switch_Middle)
		{
				ROS_ON_OFF = ON;
				if(ROS_ON_FLAG == 1)
				{
					ROS_ON();
					ROS_ON_FLAG = 0;
				}
				ROS_OFF_FLAG = 1;
		}
}