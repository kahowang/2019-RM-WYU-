#include "Kinematics.h"

#define constrain(amt,low,high) \
	((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

Kinematics::Kinematics(int motor_max_rpm, float wheel_diameter, float wheels_x_distance, float wheels_y_distance)
{
  wheel_diameter_ = wheel_diameter;
  wheel_circumference_ = PI * wheel_diameter_;     
  max_rpm_ = motor_max_rpm;
  wheels_x_distance_ = wheels_x_distance;
  wheels_y_distance_ = wheels_y_distance;
}

Kinematics::rpm Kinematics::calculateRPM(float linear_x, float linear_y, float angular_z)
{
    float linear_vel_x_mins;
    float linear_vel_y_mins;
    float angular_vel_z_mins;
    float tangential_vel;
    float x_rpm;
    float y_rpm;
    float tan_rpm;

    //convert m/s to m/min
    linear_vel_x_mins = linear_x * 60;
    linear_vel_y_mins = linear_y * 60;

    //convert rad/s to rad/min
    angular_vel_z_mins = angular_z * 60;

    tangential_vel = angular_vel_z_mins * ((wheels_x_distance_ / 2) + (wheels_y_distance_ / 2));

    x_rpm = linear_vel_x_mins / wheel_circumference_;
    y_rpm = linear_vel_y_mins / wheel_circumference_;
    tan_rpm = tangential_vel / wheel_circumference_;

    Kinematics::rpm rpm;

    //calculate for the target motor RPM and direction
    
		//front-right motor 右前
		rpm.motor0 = -(x_rpm + y_rpm + tan_rpm);
    rpm.motor0 = constrain(rpm.motor0, -max_rpm_, max_rpm_);


    //front-left motor  左前
		rpm.motor1 = x_rpm - y_rpm - tan_rpm;
    rpm.motor1 = constrain(rpm.motor1, -max_rpm_, max_rpm_);


    //rear-left motor   左后
		rpm.motor2 = x_rpm + y_rpm - tan_rpm;
    rpm.motor2 = constrain(rpm.motor2, -max_rpm_, max_rpm_);


    //rear-right motor	右后
		rpm.motor3 = -(x_rpm + y_rpm + tan_rpm);
    rpm.motor3 = constrain(rpm.motor3, -max_rpm_, max_rpm_);
    

    return rpm;
}


Kinematics::rpm Kinematics::getRPM(float linear_x, float linear_y, float angular_z)
{
    Kinematics::rpm rpm;

			rpm = calculateRPM(linear_x, linear_y , angular_z);
			return rpm;
}


Kinematics::velocities Kinematics::getVelocities(int rpm1, int rpm2, int rpm3, int rpm4)
{
    Kinematics::velocities vel;
    float average_rps_x;
    float average_rps_y;
    float average_rps_a;

    //convert average revolutions per minute to revolutions per second
    average_rps_x = ((float)(rpm1 + rpm2 + rpm3 + rpm4) / 4) / 60; // RPM
    vel.linear_x = average_rps_x * wheel_circumference_; // m/s

    //convert average revolutions per minute in y axis to revolutions per second
    average_rps_y = ((float)(rpm1 - rpm2 + rpm3 - rpm4) / 4) / 60; // RPM
		vel.linear_y = average_rps_y * wheel_circumference_; // m/s
    //vel.linear_y = 0;

    //convert average revolutions per minute to revolutions per second
    average_rps_a = ((float)(rpm1 - rpm2 - rpm3 + rpm4) / 4) / 60;
    vel.angular_z =  (average_rps_a * wheel_circumference_) / ((wheels_x_distance_ / 2) + (wheels_y_distance_ / 2)); //  rad/s

    return vel;
}

