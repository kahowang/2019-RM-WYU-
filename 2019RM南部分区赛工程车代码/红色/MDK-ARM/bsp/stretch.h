#ifndef _STRETCH_H_
#define _STRETCH_H_
#include "allheader.h"

void stretch(void);
void pid_stretch_fcn(void);
void pid_stretch_setcurrent_fcn(void);
extern int32_t stretch_time;
extern int stretch_catch;    //¿ªÆôÉìËõ¼ĞÈ¡
extern int stretch_acc_time;
#endif