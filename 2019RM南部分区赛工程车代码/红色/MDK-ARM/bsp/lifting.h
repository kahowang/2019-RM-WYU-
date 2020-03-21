#ifndef __LIFTING_H
#define __LIFTING_H
#include  "allheader.h"
#define  UP  1;
#define DOWN 2;
extern int16_t Z_count_time;
extern int16_t X_count_time;
extern int16_t C_count_time;

extern int32_t UP_OR_DOWN; //抬升或者下降
void pid_lifting_fcn(void);
void pid_lifting_setcurrent_fcn(void);
void Sin_up_y_calc(void);
void Sin_down_y_calc(void);
void keyboard_remote_control_lifting(void);
void Sin_Up_or_Down_switch(void);

extern int32_t lifting_embrace_giveballet_count_time;  //抬升计时
extern int32_t lifting_angle ; //抬升输入角度
extern int32_t lifting_angle_small;   //离地面高度为100
extern int32_t lifting_angle_difference;  //角度差值
extern int32_t lifting_angle_embrace ; //抱柱抬升角度
extern int32_t lifting_angle_catch ; //夹取抬升角度
extern int32_t lifting_angle_giveballet ; //供弹抬升角度
extern int32_t UP_OR_DOWN; //抬升或者下降
extern int32_t ref_angle2_lifting;//抬升支架
extern int32_t ref_angle3_lifting;//抬升支架
extern int32_t ref_angle_increase_lifting;
extern int32_t ref_angle2_press_lifting;//当前抬升支架
extern int32_t ref_angle3_press_lifting;//当前抬升支架
#endif