#ifndef MAINPP_H_
#define MAINPP_H_

#ifdef __cplusplus
 extern "C" {
#include "allheader.h"
#endif	
#define Connected 1;
#define Disconnected 0;
void ROS_ON(void);
void ROS_OFF(void);
void ROS_perspective_embrace(void);
void ROS_perspective_catch(void);
void Kinematics_displacement_move_fcn(void); 
void setup(void);
void ros_control_loop(void);	 
void ros_chassis_ramp(void);
void RAMP_MAX_MIN_SELECT(void);
void displacement_to_last_displacement(void);
extern int perspective_embrace_publish_flag;
extern int32_t displacementcatch;
extern int32_t displacementstretch;
extern int ros_connected;    //用于检测ROS是否连上的变量
#ifdef __cplusplus
}  

#endif
#endif /* MAINPP_H_ */
