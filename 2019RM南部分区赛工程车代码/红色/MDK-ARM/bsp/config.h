#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PI      3.1415926
#define DEBUG   1
#define MAX_RPM         469 //�ת��
#define WHEEL_DIAMETER  0.1525 //����ֱ��

#define LR_WHEELS_DISTANCE 0.380   //��0.38��
#define FR_WHEELS_DISTANCE 0.480		//��0.48��
#define WHEELS_DISTANCE_K  0.430	//((LR_WHEELS_DISTANCE / 2) + (FR_WHEELS_DISTANCE / 2))

#define IMU_PUBLISH_RATE 50 //hz
#define BAT_PUBLISH_RATE 0.2 //hz
#define COMMAND_RATE 50 //hz
#define DEBUG_RATE 1
#define displacementxyz_k   328300.439    //157286.4/(2*PI)/WHEEL_RADIUS  ROSλ��XY���� = 8192*19.2/(2*PI)/WHEEL_RADIUS

#endif // _CONFIG_H_