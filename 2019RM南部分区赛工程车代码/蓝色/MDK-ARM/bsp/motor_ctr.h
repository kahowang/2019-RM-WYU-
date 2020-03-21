#ifndef _MOTOR_CTR_H_
#define _MOTOR_CTR_H_ 

#include "allheader.h"

/*shift����б������*/
#define   RAMP_CONTROL_TIME         0.5
#define   RAMP_MAX                  2.0
#define   RAMP_MIN									1.0
/*W A S D ����б������*/
#define   RAMP_W_D_CONTROL_TIME          3  //W D�Ŀ�������
#define   RAMP_W_D_MAX                  400
#define   RAMP_W_D_MIN									0

#define   RAMP_A_S_CONTROL_TIME          3   //A S�Ŀ�������
#define   RAMP_A_S_MAX                  0
#define   RAMP_A_S_MIN									-400

void moto_param_init(void);
void remote_ros_switch(void);


void pid_calc_all_motor(void);            //����PID���㺯�������ڶ�ʱ��TIM5��

void set_moto_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4);
void set_lift_moto_current (CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4);
void set_embrace_catch_moto_current (CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4);
void set_stretch_moto_current(CAN_HandleTypeDef* hcan, s16 iq1, s16 iq2, s16 iq3, s16 iq4);

void remote_task(void);

void pid_control_output(void);

extern pid_t pid2_pos[8];       //����λ�û��ṹ��
extern pid_t pid2_spd[8];				//�����ٶȻ��ṹ��
extern pid_t pid_pos[8];       //����λ�û��ṹ��
extern pid_t pid_spd[8];				//�����ٶȻ��ṹ��
/*ROS�µĵ���PID����˫�ջ�*/
extern pid_t pid_pos_ros[4];    
extern pid_t pid_spd_ros[4];

extern int32_t set_spd0 ;
extern int32_t set_spd1 ;
extern int32_t set_spd2 ;
extern int32_t set_spd3 ;
extern int32_t set_spd4 ;
extern int32_t set_spd5 ;
extern int32_t set_spd6 ;
extern int32_t set_spd7 ;

extern int32_t set2_spd0;
extern int32_t set2_spd1;
extern int32_t set2_spd2;
extern int32_t set2_spd3;
extern int32_t set2_spd4;
extern int32_t set2_spd5;
extern int32_t set2_spd6;
extern int32_t set2_spd7;
#endif  //__MOTOR_CTR_H  