#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PI      3.1415926
#define DEBUG   1
#define MAX_RPM         469 //额定转速
#define WHEEL_DIAMETER  0.1525 //麦轮直径

#define LR_WHEELS_DISTANCE 0.380   //宽0.38米
#define FR_WHEELS_DISTANCE 0.480		//长0.48米
#define WHEELS_DISTANCE_K  0.430	//((LR_WHEELS_DISTANCE / 2) + (FR_WHEELS_DISTANCE / 2))

#define IMU_PUBLISH_RATE 50 //hz
#define BAT_PUBLISH_RATE 0.2 //hz
#define COMMAND_RATE 50 //hz
#define DEBUG_RATE 1
#define displacementxyz_k   328300.439    //157286.4/(2*PI)/WHEEL_RADIUS  ROS位移XY常数 = 8192*19.2/(2*PI)/WHEEL_RADIUS

#endif // _CONFIG_H_