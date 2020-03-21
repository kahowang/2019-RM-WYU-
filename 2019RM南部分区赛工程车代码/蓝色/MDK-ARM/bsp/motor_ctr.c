#include "motor_ctr.h" 

/************************�ײ�can1ͨ��****************************/
/*remote�µ�PID*/
pid_t pid_pos[8];       //����λ�û��ṹ��
pid_t pid_spd[8];				//�����ٶȻ��ṹ��
/*ROS�µĵ���PID����˫�ջ�*/
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

/************************�ϲ㣨upper��can2ͨ��*******************/
pid_t pid2_pos[8];       //����λ�û��ṹ��
pid_t pid2_spd[8];				//�����ٶȻ��ṹ��
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
						/*shiftб�³�ʼ��*/
						ramp_init(&set_spd_shift_ramp, RAMP_CONTROL_TIME * 0.001f, RAMP_MAX, RAMP_MIN);  
						/*����WASDб�³�ʼ��*/
						ramp_init(&set_spd_w_ramp, RAMP_W_D_CONTROL_TIME * 0.001f, RAMP_W_D_MAX, RAMP_W_D_MIN);
						ramp_init(&set_spd_d_ramp, RAMP_W_D_CONTROL_TIME * 0.001f, RAMP_W_D_MAX, RAMP_W_D_MIN);
						ramp_init(&set_spd_a_ramp, RAMP_A_S_CONTROL_TIME * 0.001f, RAMP_A_S_MAX, RAMP_A_S_MIN);
						ramp_init(&set_spd_s_ramp, RAMP_A_S_CONTROL_TIME * 0.001f, RAMP_A_S_MAX, RAMP_A_S_MIN);

				/****************************************can1*********************************************/
							/*motor0-motor3  ����*/ 
							PID_struct_init(&pid_spd[0], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);  
							PID_struct_init(&pid_spd[1], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);
							PID_struct_init(&pid_spd[2], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);
							PID_struct_init(&pid_spd[3], POSITION_PID, 5000, 400, 102.3026f, 0.0f, 10.54012f);
							/*motor6-motor5  ̧��*/
							PID_struct_init(&pid_pos[4], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f); 
							PID_struct_init(&pid_spd[4], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);
							PID_struct_init(&pid_pos[5], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f);  
							PID_struct_init(&pid_spd[5], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f); 
							/*motor6 ͼ���ӽ��л���2006��*/
							PID_struct_init(&pid_pos[6], POSITION_PID, 1000, 10, 20, 0.01f, 0);    // M2006
							PID_struct_init(&pid_spd[6], POSITION_PID, 8000, 0, 2, 0.1f, 0); 
			/****************************************can1*********************************************/
			/****************************************can2*********************************************/	
							/*motor0-motor1  ����*/
							PID_struct_init(&pid2_pos[0], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f);  
							PID_struct_init(&pid2_spd[0], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);    
							PID_struct_init(&pid2_pos[1], POSITION_PID,  1000, 100,  0.050f, 0.0f, 1.7f); 
							PID_struct_init(&pid2_spd[1], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);
							/*motor2��ȡ*/
							PID_struct_init(&pid2_pos[2], POSITION_PID,  1000, 100,  0.020f, 0.0f, 1.0f);  //λ�û�
							PID_struct_init(&pid2_spd[2], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);    //�ٶȻ�
	            /*motor3��ȡ*/
							PID_struct_init(&pid2_pos[3], POSITION_PID,  1000, 100,  0.020f, 0.0f, 1.0f);  //λ�û�
							PID_struct_init(&pid2_spd[3], POSITION_PID, 10000, 400, 102.3026f, 10.5401f, 0.0f);    //�ٶȻ�
							/*motor4   ����*/
							PID_struct_init(&pid2_pos[4], POSITION_PID, 1000, 10, 11, 0.01f, 0);    // M2006
							PID_struct_init(&pid2_spd[4], POSITION_PID, 8000, 0, 25, 0.1f, 0);
						/*motor5   ����*/
							PID_struct_init(&pid2_pos[5], POSITION_PID, 1000, 10, 11, 0.01f, 0);    // M2006
							PID_struct_init(&pid2_spd[5], POSITION_PID, 8000, 0, 25, 0.1f, 0);  							
			/*************************************************************************************/	
			/****************************************ROS�£��ĸ����ӵ�PID��˫�ջ�***********************/
							PID_struct_init(&pid_pos_ros[0], POSITION_PID,  1000, 10, 0.7, 0.0001, 0);  //λ�û�
							PID_struct_init(&pid_spd_ros[0], POSITION_PID, 20000, 0, 10.0f, 0, 0);    //�ٶȻ� 
							PID_struct_init(&pid_pos_ros[1], POSITION_PID,  1000, 10, 0.7, 0.0001, 0);  
							PID_struct_init(&pid_spd_ros[1], POSITION_PID, 20000, 0, 10.0f, 0, 0);    
							PID_struct_init(&pid_pos_ros[2], POSITION_PID,  1000, 10, 0.7, 0.0001, 0);  
							PID_struct_init(&pid_spd_ros[2], POSITION_PID, 20000, 0, 10.0f, 0, 0);    
							PID_struct_init(&pid_pos_ros[3], POSITION_PID,  1000, 10, 0.7, 0.0001, 0); 
							PID_struct_init(&pid_spd_ros[3], POSITION_PID, 20000, 0, 10.0f, 0, 0);   
}

/*****************************CAN2********************************************/
void remote_task(void)  //����ң�ؿ���
{
		/***********ROS�ͼ��̲ٿ��л�*************************/
		if(ROS_ON_OFF == OFF)   
		{
			 mouse_rotate();//��������ת
			 chassis_mouse_keyboard();	//���̼���ٿ�
		}else if(ROS_ON_OFF == ON){
			Kinematics_displacement_move_fcn();
		}
		/****************************************************/
		/*̧���������ʹ��S�����ߣ�,����Z������̧��������X���½�������C����ȡ̧��������R������һ��*/
		keyboard_remote_control_lifting();
		/*��ದ���Ƶ��к��±���Ħ����ת��*/
   // keyboard_remote_control_embrace();
      remote_control_embrace();    //  ��ದ���Ƶ��Ϻ��±���Ħ����ת��
	/*��ȡ������ Q������ E,������ȡ */ 
    keyboard_remote_control_catching();
		/*��V,�����������Ԯ*/
		keyboard_rescue();      
}

void pid_control_output(void)
{
			pid_lifting_setcurrent_fcn();    //̧������         ��˫�ջ����٣�
			pid_chassis_setcurrent_fcn();    //�����˶����������ֻ���ٶȻ���
      pid_embrace_catch_setcurrent_fcn();     //����,��ȡ
      pid_stretch_setcurrent_fcn();     //����	
}

void pid_calc_all_motor(void)   
{
		pid_lifting_fcn();     //̧�����2����3508�� can1
	  pid_perspective_fcn(); //�ӽ��л����1�� ��2006�� can1
		pid_chassis_fcn();     //���̵��4����3508�� can1
		pid_embrace_fcn();     //�������2����3508�� can2
		pid_catching_fcn();    //��ȡ���2����3508�� can2
	  pid_giveballet_fcn();  //�������1����2006�� can2
		pid_stretch_fcn();     //�������1����2006�� can2
}

/*4�����̵����can1��*/
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

/*2��̧�������can1��,1���ӽ��л����*/
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

/*��ȡ,���������can2��*/
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

/*������� m2006��can2��*/
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


