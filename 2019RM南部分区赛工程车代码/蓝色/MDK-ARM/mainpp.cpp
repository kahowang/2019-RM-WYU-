#include <mainpp.h>   
#include <ros.h>
#include <std_msgs/String.h>
#include <skyguard_msgs/gimbal.h>  
#include <geometry_msgs/Twist.h>
#include <skyguard_msgs/Velocities.h>
#include <skyguard_msgs/displacement.h>   
#include <skyguard_msgs/ROS_ON_OFF.h>
#include <skyguard_msgs/perspective_change.h>
#include "Kinematics.h"
extern "C"
{

}	

/*�ӽ��л�*/
extern int32_t  perspective;
int perspective_embrace_publish_flag=1;     //��ȡ���� ������־λ��ȷ��ÿ�ΰ���ֻ��һ��
extern float wheels_x_distance_;
extern float wheels_y_distance_;
/*ROS���ض��ı���*/
int ros_connected;    //���ڼ��ROS�Ƿ����ϵı���
extern int32_t ROS_ON_OFF;
/*kinmaticsλ����Ҫ�ĽǶ�*/
/*ramp��־λ��ֻ�ܽ���һ��*ram_init()*/
int ramp_flag;
/*б�º�������*/
/*motor0-3 �ڵ���б�º���ʱ�����ֵ����Сֵ*/
int32_t RAMP_MAX_MOTOR0;
int32_t RAMP_MAX_MOTOR1;
int32_t RAMP_MAX_MOTOR2;
int32_t RAMP_MAX_MOTOR3;
int32_t RAMP_MIN_MOTOR0;
int32_t RAMP_MIN_MOTOR1;
int32_t RAMP_MIN_MOTOR2;
int32_t RAMP_MIN_MOTOR3;
int ROS_MOTOR_RAMP_CONTROL_TIME = 1;
/*�ĸ����̵��б�º����ṹ��*/
ramp_function_source_t  motor0_ramp;
ramp_function_source_t  motor1_ramp;
ramp_function_source_t  motor2_ramp;
ramp_function_source_t  motor3_ramp;
/*ͨ��kimaticsʵ������ĽǶȣ�б������*/
int32_t motor0_angle_displacement;
int32_t motor1_angle_displacement;
int32_t motor2_angle_displacement;
int32_t motor3_angle_displacement;
/*б�����*/
int32_t motor0_angle_ramp;
int32_t motor1_angle_ramp;
int32_t motor2_angle_ramp;
int32_t motor3_angle_ramp;
/*��־λ*/
extern int Kinematics_displacement_move_flag;
/*�����Ƕ�*/
int32_t motor0_offset_angle;
int32_t motor1_offset_angle;
int32_t motor2_offset_angle;
int32_t motor3_offset_angle;

double required_linear_x_vel = 0;
double required_linear_y_vel = 0;
double required_angular_vel  = 0;

float dodge_angular_vel= 2;
/*kimaticsλ��xy*/
float displacementx;
float displacementy;
float displacementz;
int32_t displacementcatch;
int32_t displacementstretch;

float jscope_displacementx;
float jscope_displacementy;
int32_t jscope_displacementcatch;

void displacement_callback ( const skyguard_msgs::displacement& displacement_msg);  //����λ�ƻص�����
Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER, FR_WHEELS_DISTANCE, LR_WHEELS_DISTANCE);  //��Ĺ��캯��


ros::NodeHandle nh;     //��ʼ�����
skyguard_msgs::ROS_ON_OFF ros_on_off_msg;  //����ROS_ON_OFF�Ӿ�����׽ȡ��Ϣ����
skyguard_msgs::perspective_change perspective_change_msg;  //�����л��ӽ���Ϣ����

ros::Subscriber<skyguard_msgs::displacement> displacement_move("displacement_move", displacement_callback);    //���Ļ��⡰displacement_move��
ros::Publisher ros_on_off_pub("ROS_ON_OFF", &ros_on_off_msg);  //�������⡰ROS_ON_OFF��
ros::Publisher perspective_change_pub("perspective_change", &perspective_change_msg);  //�������⡰perspective_change��


void displacement_callback( const skyguard_msgs::displacement& displacement_msg)
{
		displacementx = displacement_msg.displacement_x;
		displacementy = displacement_msg.displacement_y;
		displacementz = displacement_msg.displacement_z;
		displacementcatch = displacement_msg.displacement_catch;
	  displacementstretch = displacement_msg.displacement_stretch;
	 /*Jscope ����*/
//	  jscope_displacementx =  displacementx*100;
//		jscope_displacementy =  displacementy*100;
//	  jscope_displacementcatch =  displacementcatch;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  nh.getHardware()->reset_rbuf();
}

void setup(void)
{
  nh.initNode();
	nh.subscribe(displacement_move);   //���� ��displacement_move������  
	nh.advertise(ros_on_off_pub);  		//���� "ROS_ON_OFF"������Ϣ
	nh.advertise(perspective_change_pub);  		//���� "perspective_change"������Ϣ,�ӽ��л�
}

void ros_control_loop(void)
{
  	if(!nh.connected())  //���û����
	{
			LED_OFF(LED2);  //ROS�Ͽ����ƹر�
		  ros_connected = Disconnected	;  
	}else{
			LED_ON(LED2);  //�������ˣ��������� 
      ros_connected = Connected	;
	}	
	nh.spinOnce();
}

void Kinematics_displacement_move_fcn(void)    //��kinmatics�Ƴ���λ���˶�ѧת����ʽ,157286.4=8192*19.2
{
		if(Kinematics_displacement_move_flag == 0)
		{
			motor0_offset_angle = moto_chassis[0].total_angle;
			motor1_offset_angle = moto_chassis[1].total_angle;
			motor2_offset_angle = moto_chassis[2].total_angle;
			motor3_offset_angle = moto_chassis[3].total_angle;
			Kinematics_displacement_move_flag = 1;
		}
		/*����kimatics�㷨������ĸ�����ʵ��ֵ*/
		motor0_angle_displacement =  -((displacementx + displacementy - WHEELS_DISTANCE_K*displacementz)*displacementxyz_k) ;
		motor1_angle_displacement =  (displacementx - displacementy + WHEELS_DISTANCE_K*displacementz)*displacementxyz_k    ;
		motor2_angle_displacement =  (displacementx + displacementy + WHEELS_DISTANCE_K*displacementz)*displacementxyz_k    ;
		motor3_angle_displacement =  -((displacementx - displacementy- WHEELS_DISTANCE_K*displacementz)*displacementxyz_k)  ;
		/*����б�º����ԽǶ�ֵ�����˲�����*/
		//ros_chassis_ramp();
		/*б�´���ĽǶȼ���ԭ�еĽǶ��ۼ�*/
		motor0_angle = motor0_angle_displacement + motor0_offset_angle;//motor0_angle_ramp + motor0_offset_angle;
		motor1_angle = motor1_angle_displacement + motor1_offset_angle;//motor1_angle_ramp + motor1_offset_angle;
		motor2_angle = motor2_angle_displacement + motor2_offset_angle;//motor2_angle_ramp + motor2_offset_angle;
		motor3_angle = motor3_angle_displacement + motor3_offset_angle;//motor3_angle_ramp + motor3_offset_angle;
}

/*ros����б�º���*/
void ros_chassis_ramp(void)
{
			RAMP_MAX_MIN_SELECT();
		/*��ramp_flag == 1��minipc ��������ʱ�Żᴥ��*/
		if( (ramp_flag == 1)&&(displacementx|| displacementy ||displacementz) ) 
		{
			ramp_init_int32(&motor0_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR0, RAMP_MIN_MOTOR0);
			ramp_init_int32(&motor1_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR1, RAMP_MIN_MOTOR1);
			ramp_init_int32(&motor2_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR2, RAMP_MIN_MOTOR2);
			ramp_init_int32(&motor3_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR3, RAMP_MIN_MOTOR3);
			ramp_flag = 0;  //��֤�����ťһֱ�����е�����ʼ��Ҳֻ����һ��
		}
			/*б������*/
			ramp_calc_int32(&motor0_ramp, motor0_angle_displacement); 
			ramp_calc_int32(&motor1_ramp, motor1_angle_displacement);
			ramp_calc_int32(&motor2_ramp, motor2_angle_displacement);
			ramp_calc_int32(&motor3_ramp, motor3_angle_displacement);	
			/*б�����*/
			motor0_angle_ramp = motor0_ramp.out;   //б�����  
			motor1_angle_ramp = motor1_ramp.out;   //б�����  
			motor2_angle_ramp = motor2_ramp.out;   //б�����  
			motor3_angle_ramp = motor3_ramp.out;   //б�����  
 }

void RAMP_MAX_MIN_SELECT(void)
{
			 //�Ƕȵ� ���ֵ ��Сֵ�оݣ���� angle>0 , RAMP_MAX = angle,RAMP_MIN = 0;��� angle<0 , RAMP_MAX = 0 ;RAMP_MIN = angle;
			/****************motor0*******************/
			if(motor0_angle_displacement>0)
		{
			RAMP_MAX_MOTOR0 = motor0_angle_displacement;
			RAMP_MIN_MOTOR0 = 0;
		}else if(motor0_angle_displacement<0)
		{
			RAMP_MAX_MOTOR0 = 0;
			RAMP_MIN_MOTOR0 = motor0_angle_displacement;
		}
			/****************motor1*******************/
				if(motor1_angle_displacement>0)
		{
			RAMP_MAX_MOTOR1 = motor1_angle_displacement;
			RAMP_MIN_MOTOR1 = 0;
		}else if(motor1_angle_displacement<0)
		{
			RAMP_MAX_MOTOR1 = 0;
			RAMP_MIN_MOTOR1 = motor1_angle_displacement;
		}
		/****************motor2*******************/
				if(motor2_angle_displacement>0)
		{
			RAMP_MAX_MOTOR2 = motor2_angle_displacement;
			RAMP_MIN_MOTOR2 = 0;
		}else if(motor2_angle_displacement<0)
		{
			RAMP_MAX_MOTOR2 = 0;
			RAMP_MIN_MOTOR2 = motor2_angle_displacement;
		}
		/****************motor3*******************/
				if(motor3_angle_displacement>0)
		{
			RAMP_MAX_MOTOR3 = motor3_angle_displacement;
			RAMP_MIN_MOTOR3 = 0;
		}else if(motor3_angle_displacement<0)
		{
			RAMP_MAX_MOTOR3 = 0;
			RAMP_MIN_MOTOR3 = motor3_angle_displacement;
		}
}
void ROS_ON(void)
{  
		ros_on_off_msg.on_off= ROS_ON_OFF; 
		ros_on_off_pub.publish(&ros_on_off_msg);
}

void ROS_OFF(void)
{
		ros_on_off_msg.on_off= ROS_ON_OFF; 
		ros_on_off_pub.publish(&ros_on_off_msg);
}  

void ROS_perspective_catch(void)
{
	if( perspective_embrace_publish_flag == 1)
	{
		 perspective_change_msg.perspective =  perspective_catch; 
		 perspective_change_pub.publish(&perspective_change_msg);
		 perspective_embrace_publish_flag = 0; //��־λ��0
	}
}
void ROS_perspective_embrace(void)
{
		if( perspective_embrace_publish_flag == 1)
	{
		 perspective_change_msg.perspective =  perspective_embrace; 
		 perspective_change_pub.publish(&perspective_change_msg);
	   perspective_embrace_publish_flag = 0; //��־λ��0
	}
}

