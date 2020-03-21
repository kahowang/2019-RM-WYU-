#include "motor_ctr.h" 

/************************底层can1通信****************************/
/*remote下的PID*/
pid_t pid_pos[8];       //定义位置环结构体
pid_t pid_spd[8];				//定义速度环结构体
/*ROS下的底盘PID，有双闭环*/
pid_t pid_pos_ros[4];    
pid_t pid_spd_ros[4];
/********************************************************************/
int32_t set_spd0 = 0;
int32_t set_spd1 = 0;
int32_t set_spd2 = 0;
int32_t set_spd3 = 0;
int32_t set_spd4 = 0;
int32_t set_spd5 = 0;
int32_t set_spd6 = 0;
int32_t set_spd7 = 0;

/************************上层（upper）can2通信*******************/
pid_t pid2_pos[8];       //定义位置环结构体
pid_t pid2_spd[8];				//定义速度环结构体
int32_t set2_spd0 = 0;
int32_t set2_spd1 = 0;
int32_t set2_spd2 = 0;
int32_t set2_spd3 = 0;
int32_t set2_spd4 = 0;
int32_t set2_spd5 = 0;
int32_t set2_spd6 = 0;  
int32_t set2_spd7 = 0;

void moto_param_init(void)
{
						/*shift斜坡初始化*/
						ramp_init(&set_spd_shift_ramp, RAMP_CONTROL_TIME * 0.001f, RAMP_MAX, RAMP_MIN);  
						/*按键WASD斜坡初始化*/
						ramp_init(&set_spd_w_ramp, RAMP_W_D_CONTROL_TIME * 0.001f, RAMP_W_D_MAX, RAMP_W_D_MIN);
						ramp_init(&set_spd_d_ramp, RAMP_W_D_CONTROL_TIME * 0.001f, RAMP_W_D_MAX, RAMP_W_D_MIN);
						ramp_init(&set_spd_a_ramp, RAMP_A_S_CONTROL_TIME * 0.001f, RAMP_A_S_MAX, RAMP_A_S_MIN);
						ramp_init(&set_spd_s_ramp, RAMP_A_S_CONTROL_TIME * 0.001f, RAMP_A_S_MAX, RAMP_A_S_MIN);

				/****************************************can1*********************************************/
							/*motor0-motor3  底盘*/ 
							PID_struct_init(&pid_spd[0], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);  
							PID_struct_init(&pid_spd[1], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);
							PID_struct_init(&pid_spd[2], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);
							PID_struct_init(&pid_spd[3], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);
							/*motor6-motor5  抬升*/
							PID_struct_init(&pid_pos[4], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f); 
							PID_struct_init(&pid_spd[4], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);
							PID_struct_init(&pid_pos[5], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f);  
							PID_struct_init(&pid_spd[5], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f); 
							/*motor6 图传视角切换（2006）*/
							PID_struct_init(&pid_pos[6], POSITION_PID, 1000, 10, 20, 0.01f, 0);    // M2006
							PID_struct_init(&pid_spd[6], POSITION_PID, 8000, 0, 2, 0.1f, 0); 
			/****************************************can1*********************************************/
			/****************************************can2*********************************************/	
							/*motor0-motor1  抱柱*/
							PID_struct_init(&pid2_pos[0], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f);  
							PID_struct_init(&pid2_spd[0], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);    
							PID_struct_init(&pid2_pos[1], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f); 
							PID_struct_init(&pid2_spd[1], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);
							/*motor2夹取*/
							PID_struct_init(&pid2_pos[2], POSITION_PID,  1000, 100,  0.020f, 0.0f, 1.0f);  //位置环
							PID_struct_init(&pid2_spd[2], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);    //速度环
	            /*motor3夹取*/
							PID_struct_init(&pid2_pos[3], POSITION_PID,  1000, 100,  0.020f, 0.0f, 1.0f);  //位置环
							PID_struct_init(&pid2_spd[3], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);    //速度环
							/*motor4   伸缩*/
							PID_struct_init(&pid2_pos[4], POSITION_PID, 1000, 10, 11, 0.01f, 0);    // M2006
							PID_struct_init(&pid2_spd[4], POSITION_PID, 8000, 0, 25, 0.1f, 0);
						/*motor5   供弹*/
							PID_struct_init(&pid2_pos[5], POSITION_PID, 1000, 10, 11, 0.01f, 0);    // M2006
							PID_struct_init(&pid2_spd[5], POSITION_PID, 8000, 0, 25, 0.1f, 0);  							
			/*************************************************************************************/	
			/****************************************ROS下，四个轮子的PID，双闭环***********************/
							PID_struct_init(&pid_pos_ros[0], POSITION_PID,  1000, 10, 0.7, 0.0001, 0);  //位置环
							PID_struct_init(&pid_spd_ros[0], POSITION_PID, 20000, 0, 10.0f, 0, 0);    //速度环 
							PID_struct_init(&pid_pos_ros[1], POSITION_PID,  1000, 10, 0.7, 0.0001, 0);  
							PID_struct_init(&pid_spd_ros[1], POSITION_PID, 20000, 0, 10.0f, 0, 0);    
							PID_struct_init(&pid_pos_ros[2], POSITION_PID,  1000, 10, 0.7, 0.0001, 0);  
							PID_struct_init(&pid_spd_ros[2], POSITION_PID, 20000, 0, 10.0f, 0, 0);    
							PID_struct_init(&pid_pos_ros[3], POSITION_PID,  1000, 10, 0.7, 0.0001, 0); 
							PID_struct_init(&pid_spd_ros[3], POSITION_PID, 20000, 0, 10.0f, 0, 0);   
}

/*****************************CAN2********************************************/
void remote_task(void)  //底盘遥控控制
{
		/***********ROS和键盘操控切换*************************/
		if(ROS_ON_OFF == OFF)   
		{
			 mouse_rotate();//鼠标控制旋转
			 chassis_mouse_keyboard();	//底盘键鼠操控
		}else if(ROS_ON_OFF == ON){
			Kinematics_displacement_move_fcn();
		}
		/****************************************************/
		/*抬升电机（有使用S型曲线）,按“Z”抱柱抬升，按“X”下降，按“C”夹取抬升，按“R”供弹一套*/
		keyboard_remote_control_lifting();
		/*左侧拨杆推到中和下抱柱摩擦轮转动*/
   // keyboard_remote_control_embrace();
      remote_control_embrace();    //  左侧拨杆推到上和下抱柱摩擦轮转动
	/*夹取，按键 Q，按键 E,伸缩夹取 */ 
    keyboard_remote_control_catching();
		/*按V,启动电磁铁救援*/
		keyboard_rescue();      
}

void pid_control_output(void)
{
			pid_lifting_setcurrent_fcn();    //抬升机构         （双闭环调速）
			pid_chassis_setcurrent_fcn();    //底盘运动输出函数（只有速度环）
      pid_embrace_catch_setcurrent_fcn();     //抱柱,夹取
      pid_stretch_setcurrent_fcn();     //伸缩	
}

void pid_calc_all_motor(void)   
{
		pid_lifting_fcn();     //抬升电机2个（3508） can1
	  pid_perspective_fcn(); //视角切换电机1个 （2006） can1
		pid_chassis_fcn();     //底盘电机4个（3508） can1
		pid_embrace_fcn();     //抱柱电机2个（3508） can2
		pid_catching_fcn();    //夹取电机2个（3508） can2
	  pid_giveballet_fcn();  //供弹电机1个（2006） can2
		pid_stretch_fcn();     //伸缩电机1个（2006） can2
}

/*4个底盘电机（can1）*/
void set_moto_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4){

	hcan->pTxMsg->StdId = 0x200;
	hcan->pTxMsg->IDE = CAN_ID_STD;
	hcan->pTxMsg->RTR = CAN_RTR_DATA;
	hcan->pTxMsg->DLC = 0x08;
	hcan->pTxMsg->Data[0] = iq1 >> 8;
	hcan->pTxMsg->Data[1] = iq1;
	hcan->pTxMsg->Data[2] = iq2 >> 8;
	hcan->pTxMsg->Data[3] = iq2;
	hcan->pTxMsg->Data[4] = iq3 >> 8;
	hcan->pTxMsg->Data[5] = iq3;
	hcan->pTxMsg->Data[6] = iq4 >> 8;
	hcan->pTxMsg->Data[7] = iq4;
	HAL_CAN_Transmit(hcan, 1000);
}	

/*2个抬升电机（can1）,1个视角切换电机*/
void set_lift_moto_current (CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4){

	hcan->pTxMsg->StdId = 0x1FF;
	hcan->pTxMsg->IDE = CAN_ID_STD;
	hcan->pTxMsg->RTR = CAN_RTR_DATA;
	hcan->pTxMsg->DLC = 0x08;
	hcan->pTxMsg->Data[0] = iq1 >> 8;
	hcan->pTxMsg->Data[1] = iq1;
	hcan->pTxMsg->Data[2] = iq2 >> 8;
	hcan->pTxMsg->Data[3] = iq2;
	hcan->pTxMsg->Data[4] = iq3 >> 8;
	hcan->pTxMsg->Data[5] = iq3;
	hcan->pTxMsg->Data[6] = iq4 >> 8;
	hcan->pTxMsg->Data[7] = iq4;
	HAL_CAN_Transmit(hcan, 1000);
}	

/*夹取,抱柱电机（can2）*/
void set_embrace_catch_moto_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4){

	hcan->pTxMsg->StdId = 0x200;
	hcan->pTxMsg->IDE = CAN_ID_STD;
	hcan->pTxMsg->RTR = CAN_RTR_DATA;
	hcan->pTxMsg->DLC = 0x08;
	hcan->pTxMsg->Data[0] = iq1 >> 8;
	hcan->pTxMsg->Data[1] = iq1;
	hcan->pTxMsg->Data[2] = iq2 >> 8;
	hcan->pTxMsg->Data[3] = iq2;
	hcan->pTxMsg->Data[4] = iq3 >> 8;
	hcan->pTxMsg->Data[5] = iq3;
	hcan->pTxMsg->Data[6] = iq4 >> 8;
	hcan->pTxMsg->Data[7] = iq4;
	HAL_CAN_Transmit(hcan, 1000);
}

/*伸缩电机 m2006（can2）*/
void set_stretch_moto_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4){

	hcan->pTxMsg->StdId = 0x1FF;
	hcan->pTxMsg->IDE = CAN_ID_STD;
	hcan->pTxMsg->RTR = CAN_RTR_DATA;
	hcan->pTxMsg->DLC = 0x08;
	hcan->pTxMsg->Data[0] = iq1 >> 8;
	hcan->pTxMsg->Data[1] = iq1;
	hcan->pTxMsg->Data[2] = iq2 >> 8;
	hcan->pTxMsg->Data[3] = iq2;
	hcan->pTxMsg->Data[4] = iq3 >> 8;
	hcan->pTxMsg->Data[5] = iq3;
	hcan->pTxMsg->Data[6] = iq4 >> 8;
	hcan->pTxMsg->Data[7] = iq4;
	HAL_CAN_Transmit(hcan, 1000);
}


