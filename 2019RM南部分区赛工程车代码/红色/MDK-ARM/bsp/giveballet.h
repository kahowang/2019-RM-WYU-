#ifndef GIVEBALLET_H
#define GIVEBALLET_H
#include "allheader.h"
void giveballet(void);
extern int32_t giveballet_control_time;
extern int ref_giveballet_angle_open ;  //2006���սǶ�Ϊ900
extern int ref_giveballet_angle_close ;  //2006�ز�
void keyboard_remote_control_giveballet();
void pid_giveballet_fcn(void);
extern int ref_giveballet_angle;
#endif