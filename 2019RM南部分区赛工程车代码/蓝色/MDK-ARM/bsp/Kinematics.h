#ifndef KINEMATICS_H
#define KINEMATICS_H
#include "config.h"

class Kinematics
{
  public:
    struct rpm {
      int motor0;
      int motor1;
      int motor2;
      int motor3;
    };
    struct velocities {
      float linear_x;
      float linear_y;
      float angular_z;
    };
    Kinematics(int motor_max_rpm, float wheel_diameter, float wheels_x_distance, float wheels_y_distance);
    velocities getVelocities(int rpm1, int rpm2, int rpm3, int rpm4);
		velocities getVelocities(float steering_angle, int rpm1, int rpm2);
    rpm getRPM(float linear_x, float linear_y, float angular_z);

  private:
	rpm calculateRPM(float linear_x, float linear_y, float angular_z);
  int max_rpm_;
	float wheel_diameter_;
	float wheels_x_distance_;
	float wheels_y_distance_;
	float wheel_circumference_;
};

#endif
