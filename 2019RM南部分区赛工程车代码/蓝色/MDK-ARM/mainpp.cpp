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

/*视角切换*/
extern int32_t  perspective;
int perspective_embrace_publish_flag=1;     //夹取抱柱 发布标志位，确保每次按键只发一次
extern float wheels_x_distance_;
extern float wheels_y_distance_;
/*ROS开关订阅变量*/
int ros_connected;    //用于检测ROS是否连上的变量
extern int32_t ROS_ON_OFF;
/*kinmatics位移需要的角度*/
/*ramp标志位，只能进入一次*ram_init()*/
int ramp_flag;
/*斜坡函数参数*/
/*motor0-3 在调用斜坡函数时的最大值和最小值*/
int32_t RAMP_MAX_MOTOR0;
int32_t RAMP_MAX_MOTOR1;
int32_t RAMP_MAX_MOTOR2;
int32_t RAMP_MAX_MOTOR3;
int32_t RAMP_MIN_MOTOR0;
int32_t RAMP_MIN_MOTOR1;
int32_t RAMP_MIN_MOTOR2;
int32_t RAMP_MIN_MOTOR3;
int ROS_MOTOR_RAMP_CONTROL_TIME = 1;
/*四个底盘电机斜坡函数结构体*/
ramp_function_source_t  motor0_ramp;
ramp_function_source_t  motor1_ramp;
ramp_function_source_t  motor2_ramp;
ramp_function_source_t  motor3_ramp;
/*通过kimatics实际算出的角度，斜坡输入*/
int32_t motor0_angle_displacement;
int32_t motor1_angle_displacement;
int32_t motor2_angle_displacement;
int32_t motor3_angle_displacement;
/*斜坡输出*/
int32_t motor0_angle_ramp;
int32_t motor1_angle_ramp;
int32_t motor2_angle_ramp;
int32_t motor3_angle_ramp;
/*标志位*/
extern int Kinematics_displacement_move_flag;
/*补偿角度*/
int32_t motor0_offset_angle;
int32_t motor1_offset_angle;
int32_t motor2_offset_angle;
int32_t motor3_offset_angle;

double required_linear_x_vel = 0;
double required_linear_y_vel = 0;
double required_angular_vel  = 0;

float dodge_angular_vel= 2;
/*kimatics位移xy*/
float displacementx;
float displacementy;
float displacementz;
int32_t displacementcatch;
int32_t displacementstretch;

float jscope_displacementx;
float jscope_displacementy;
int32_t jscope_displacementcatch;

void displacement_callback ( const skyguard_msgs::displacement& displacement_msg);  //底盘位移回调函数
Kinematics kinematics(MAX_RPM, WHEEL_DIAMETER, FR_WHEELS_DISTANCE, LR_WHEELS_DISTANCE);  //类的构造函数


ros::NodeHandle nh;     //初始化句柄
skyguard_msgs::ROS_ON_OFF ros_on_off_msg;  //发布ROS_ON_OFF视觉开启捉取消息类型
skyguard_msgs::perspective_change perspective_change_msg;  //发布切换视角消息类型

ros::Subscriber<skyguard_msgs::displacement> displacement_move("displacement_move", displacement_callback);    //订阅话题“displacement_move”
ros::Publisher ros_on_off_pub("ROS_ON_OFF", &ros_on_off_msg);  //发布话题“ROS_ON_OFF”
ros::Publisher perspective_change_pub("perspective_change", &perspective_change_msg);  //发布话题“perspective_change”


void displacement_callback( const skyguard_msgs::displacement& displacement_msg)
{
		displacementx = displacement_msg.displacement_x;
		displacementy = displacement_msg.displacement_y;
		displacementz = displacement_msg.displacement_z;
		displacementcatch = displacement_msg.displacement_catch;
	  displacementstretch = displacement_msg.displacement_stretch;
	 /*Jscope 调试*/
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
	nh.subscribe(displacement_move);   //订阅 “displacement_move”话题  
	nh.advertise(ros_on_off_pub);  		//发布 "ROS_ON_OFF"话题信息
	nh.advertise(perspective_change_pub);  		//发布 "perspective_change"话题信息,视角切换
}

void ros_control_loop(void)
{
  	if(!nh.connected())  //如果没连上
	{
			LED_OFF(LED2);  //ROS断开，灯关闭
		  ros_connected = Disconnected	;  
	}else{
			LED_ON(LED2);  //连接上了，亮灯提醒 
      ros_connected = Connected	;
	}	
	nh.spinOnce();
}

void Kinematics_displacement_move_fcn(void)    //由kinmatics推出的位移运动学转换公式,157286.4=8192*19.2
{
		if(Kinematics_displacement_move_flag == 0)
		{
			motor0_offset_angle = moto_chassis[0].total_angle;
			motor1_offset_angle = moto_chassis[1].total_angle;
			motor2_offset_angle = moto_chassis[2].total_angle;
			motor3_offset_angle = moto_chassis[3].total_angle;
			Kinematics_displacement_move_flag = 1;
		}
		/*储存kimatics算法算出的四个轮子实际值*/
		motor0_angle_displacement =  -((displacementx + displacementy - WHEELS_DISTANCE_K*displacementz)*displacementxyz_k) ;
		motor1_angle_displacement =  (displacementx - displacementy + WHEELS_DISTANCE_K*displacementz)*displacementxyz_k    ;
		motor2_angle_displacement =  (displacementx + displacementy + WHEELS_DISTANCE_K*displacementz)*displacementxyz_k    ;
		motor3_angle_displacement =  -((displacementx - displacementy- WHEELS_DISTANCE_K*displacementz)*displacementxyz_k)  ;
		/*调用斜坡函数对角度值进行滤波处理*/
		//ros_chassis_ramp();
		/*斜坡处理的角度加上原有的角度累加*/
		motor0_angle = motor0_angle_displacement + motor0_offset_angle;//motor0_angle_ramp + motor0_offset_angle;
		motor1_angle = motor1_angle_displacement + motor1_offset_angle;//motor1_angle_ramp + motor1_offset_angle;
		motor2_angle = motor2_angle_displacement + motor2_offset_angle;//motor2_angle_ramp + motor2_offset_angle;
		motor3_angle = motor3_angle_displacement + motor3_offset_angle;//motor3_angle_ramp + motor3_offset_angle;
}

/*ros底盘斜坡函数*/
void ros_chassis_ramp(void)
{
			RAMP_MAX_MIN_SELECT();
		/*当ramp_flag == 1且minipc 有数据来时才会触发*/
		if( (ramp_flag == 1)&&(displacementx|| displacementy ||displacementz) ) 
		{
			ramp_init_int32(&motor0_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR0, RAMP_MIN_MOTOR0);
			ramp_init_int32(&motor1_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR1, RAMP_MIN_MOTOR1);
			ramp_init_int32(&motor2_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR2, RAMP_MIN_MOTOR2);
			ramp_init_int32(&motor3_ramp, ROS_MOTOR_RAMP_CONTROL_TIME * 0.005f, RAMP_MAX_MOTOR3, RAMP_MIN_MOTOR3);
			ramp_flag = 0;  //保证如果拨钮一直处在中档，初始化也只进入一次
		}
			/*斜坡运算*/
			ramp_calc_int32(&motor0_ramp, motor0_angle_displacement); 
			ramp_calc_int32(&motor1_ramp, motor1_angle_displacement);
			ramp_calc_int32(&motor2_ramp, motor2_angle_displacement);
			ramp_calc_int32(&motor3_ramp, motor3_angle_displacement);	
			/*斜坡输出*/
			motor0_angle_ramp = motor0_ramp.out;   //斜坡输出  
			motor1_angle_ramp = motor1_ramp.out;   //斜坡输出  
			motor2_angle_ramp = motor2_ramp.out;   //斜坡输出  
			motor3_angle_ramp = motor3_ramp.out;   //斜坡输出  
 }

void RAMP_MAX_MIN_SELECT(void)
{
			 //角度的 最大值 最小值判据，如果 angle>0 , RAMP_MAX = angle,RAMP_MIN = 0;如果 angle<0 , RAMP_MAX = 0 ;RAMP_MIN = angle;
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
		 perspective_embrace_publish_flag = 0; //标志位置0
	}
}
void ROS_perspective_embrace(void)
{
		if( perspective_embrace_publish_flag == 1)
	{
		 perspective_change_msg.perspective =  perspective_embrace; 
		 perspective_change_pub.publish(&perspective_change_msg);
	   perspective_embrace_publish_flag = 0; //标志位置0
	}
}

