#ifndef _EMBRACE_H_
#define _EMBRACE_H_
#include  "allheader.h"
void pid_embrace_fcn(void);
void pid_embrace_catch_setcurrent_fcn(void);
void Sin_up_y_calc_embrace(void);
void Sin_down_y_calc_embrace(void);
void keyboard_remote_control_embrace(void);
void remote_control_embrace(void);
void detection_embrace_ps(void);
extern int32_t Jscope_angle4;
extern int32_t Jscope_angle5;
extern int32_t ref_embrace_angle4;  //±§Öù½Ç¶È
extern int32_t ref_embrace_angle5;  //±§Öù½Ç¶È 
#endif