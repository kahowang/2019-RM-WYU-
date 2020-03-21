#include "chassis.h"  
/*******************ROS Kinmatics����********************/
int32_t motor0_angle;
int32_t motor1_angle;
int32_t motor2_angle;
int32_t motor3_angle;
/*kimaticsλ��xy*/
extern float displacementx;
extern float displacementy;
extern float displacementz;
extern int ramp_flag;
int32_t ROS_ON_OFF; 
int ROS_ON_FLAG=1;
int ROS_OFF_FLAG=1;  //ִֻ��һ�ε�ROS_ON_OFF��־λ
int moto_offset_flag;

/*��־λ*/
int Kinematics_displacement_move_flag;

/*���л�ģʽʱ����Ҫ��λ�� б�º��� ��־λ*/
/*�ⲿ���õ�б�½ṹ��*/  
extern ramp_function_source_t  motor0_ramp;  
extern ramp_function_source_t  motor1_ramp;
extern ramp_function_source_t  motor2_ramp;
extern ramp_function_source_t  motor3_ramp;
/*����б������*/
extern int32_t motor0_angle_displacement;
extern int32_t motor1_angle_displacement;
extern int32_t motor2_angle_displacement;
extern int32_t motor3_angle_displacement;
/*����б�����*/
extern int32_t motor0_angle_ramp;
extern int32_t motor1_angle_ramp;
extern int32_t motor2_angle_ramp;
extern int32_t motor3_angle_ramp;
/******************�����ٶ�**************************/
ramp_function_source_t  set_spd_shift_ramp;
/*���� W A S D б��*/
ramp_function_source_t  set_spd_w_ramp; 
ramp_function_source_t  set_spd_a_ramp; 
ramp_function_source_t  set_spd_s_ramp; 
ramp_function_source_t  set_spd_d_ramp; 
int set_spd_w; //����������ٶȣ�����б�´���
int set_spd_a;
int set_spd_s;
int set_spd_d;
int set_spd_default=400;  //����Ĭ���ٶ�Ϊ400rpm
float set_spd_shift=2.0;          //��shift�����ٶ�ϵ��
int set_spd_rotate;         //��������ת
int mouse_control_fb;       //�����Ƶ� Front-Back
int mouse_control_lr;       //�����Ƶ� Left-Right
/*Jscope�ٶȵ���*/
int32_t Jscope_chassis0_speed;
int32_t Jscope_chassis1_speed;
int32_t Jscope_chassis2_speed;
int32_t Jscope_chassis3_speed;
/******************************����**************************************/
void pid_chassis_fcn(void)    //PID���Ƽ���
{
			Jscope_chassis0_speed =  moto_chassis[0].speed_rpm/19.2;
			Jscope_chassis1_speed =  moto_chassis[1].speed_rpm/19.2;
			Jscope_chassis2_speed =  moto_chassis[2].speed_rpm/19.2;
			Jscope_chassis3_speed =  moto_chassis[3].speed_rpm/19.2;
	/*�Ҳದ�����ϣ�û�п���ROS*/
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
void pid_chassis_setcurrent_fcn(void)    //PID�����������
{
		if(ROS_ON_OFF == OFF)
		{
			set_moto_current(&hcan1, pid_spd[0].pos_out, 
			pid_spd[1].pos_out,
			pid_spd[2].pos_out,
			pid_spd[3].pos_out);  //���������ٶȻ�->������
		}else if (ROS_ON_OFF == ON){
			set_moto_current(&hcan1, pid_spd_ros[0].pos_out, pid_spd_ros[1].pos_out,pid_spd_ros[2].pos_out,pid_spd_ros[3].pos_out);
		}
}
/**********************************************************************************/
void chassis_mouse_keyboard(void)
{
					if(KEY_W)    //��ǰ
			{
					ramp_calc(&set_spd_w_ramp, set_spd_default);   //����
			}else{
					ramp_calc(&set_spd_w_ramp, -set_spd_default);  //����
			}
					if(KEY_D)    //����
			{
					ramp_calc(&set_spd_d_ramp, set_spd_default);   //����
			}else{
					ramp_calc(&set_spd_d_ramp, -set_spd_default);  //����
			}
					if(KEY_S)    //�˺�
			{
					ramp_calc(&set_spd_s_ramp, -set_spd_default);   //����
			}else{
					ramp_calc(&set_spd_s_ramp, set_spd_default);  //����
			}
					if(KEY_A)    //����
			{
					ramp_calc(&set_spd_a_ramp, -set_spd_default);   //����
			}else{
					ramp_calc(&set_spd_a_ramp, set_spd_default);  //����
			}
			press_shift_speed();  //��shift ���� ������ϵ��Ϊ1-2
			set_spd_w =  set_spd_w_ramp.out;
			set_spd_d =  set_spd_d_ramp.out;
			set_spd_s =  set_spd_s_ramp.out;
			set_spd_a =  set_spd_a_ramp.out;
			mouse_control_fb = set_spd_w + set_spd_s;
			mouse_control_lr = set_spd_d + set_spd_a;
		//����1�����ϣ�
		set_spd0 = -mouse_control_fb/set_spd_shift + mouse_control_lr/set_spd_shift + set_spd_rotate; 
	
		//����2�����ϣ�
		set_spd1 =  mouse_control_fb/set_spd_shift + mouse_control_lr/set_spd_shift + set_spd_rotate;

		//����3�����£�
		set_spd2 =  mouse_control_fb/set_spd_shift - mouse_control_lr/set_spd_shift + set_spd_rotate;

		//����4�����£�
		set_spd3 = -mouse_control_fb/set_spd_shift - mouse_control_lr/set_spd_shift + set_spd_rotate; 
}

void  press_shift_speed(void)
{
		if(KEY_SHIFT)  //��shift����
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
		if(remote_control.switch_right == Switch_Up)  //�������ϣ����̿��Ƶ���ģʽ
		{
			/*����ROS�ı�־λ����*/	
				ROS_ON_OFF = OFF;  // �ر�ROS
				Kinematics_displacement_move_flag = 0;  //���Ʋ���ֵ����ť��һ�Σ�ֻ��ȡһ�β����Ƕ�
				/*�л�ROSʱ����minipc������λ����Ϣ����*/
				displacementx = 0.0;
				displacementy = 0.0;
				displacementz = 0.0;
				/*��֤б�³�ʼ��ramp_init()ֻ����һ��*/
				ramp_flag = 1; 
				/*�л�ģʽʱ���б�º���������ֵ��Ҳ���������Ŀ��Ƕ�*/
				motor0_angle_displacement = motor1_angle_displacement = motor2_angle_displacement= motor3_angle_displacement = 0;
				/*���б�µ����ֵ*/
			  motor0_angle_ramp = motor1_angle_ramp = motor2_angle_ramp = motor3_angle_ramp = 0;
				motor0_ramp.out = motor1_ramp.out =motor2_ramp.out = motor3_ramp.out = 0;
			/*ROS_OFF_FLAG���ñ�֤ÿ�β���ֻ����һ��ROS_ON_OFF*/
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