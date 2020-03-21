#ifndef __LIFTING_H
#define __LIFTING_H
#include  "allheader.h"
#define  UP  1;
#define DOWN 2;
extern int16_t Z_count_time;
extern int16_t X_count_time;
extern int16_t C_count_time;

extern int32_t UP_OR_DOWN; //̧�������½�
void pid_lifting_fcn(void);
void pid_lifting_setcurrent_fcn(void);
void Sin_up_y_calc(void);
void Sin_down_y_calc(void);
void keyboard_remote_control_lifting(void);
void Sin_Up_or_Down_switch(void);

extern int32_t lifting_embrace_giveballet_count_time;  //̧����ʱ
extern int32_t lifting_angle ; //̧������Ƕ�
extern int32_t lifting_angle_small;   //�����߶�Ϊ100
extern int32_t lifting_angle_difference;  //�ǶȲ�ֵ
extern int32_t lifting_angle_embrace ; //����̧���Ƕ�
extern int32_t lifting_angle_catch ; //��ȡ̧���Ƕ�
extern int32_t lifting_angle_giveballet ; //����̧���Ƕ�
extern int32_t UP_OR_DOWN; //̧�������½�
extern int32_t ref_angle2_lifting;//̧��֧��
extern int32_t ref_angle3_lifting;//̧��֧��
extern int32_t ref_angle_increase_lifting;
extern int32_t ref_angle2_press_lifting;//��ǰ̧��֧��
extern int32_t ref_angle3_press_lifting;//��ǰ̧��֧��
#endif