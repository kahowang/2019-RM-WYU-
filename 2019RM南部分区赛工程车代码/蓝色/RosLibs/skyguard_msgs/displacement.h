#ifndef _ROS_skyguard_msgs_displacement_h
#define _ROS_skyguard_msgs_displacement_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace skyguard_msgs
{

  class displacement : public ros::Msg
  {
    public:
      typedef float _displacement_x_type;
      _displacement_x_type displacement_x;
      typedef float _displacement_y_type;
      _displacement_y_type displacement_y;
      typedef float _displacement_z_type;
      _displacement_z_type displacement_z;
      typedef int32_t _displacement_catch_type;
      _displacement_catch_type displacement_catch;
      typedef int32_t _displacement_stretch_type;
      _displacement_stretch_type displacement_stretch;

    displacement():
      displacement_x(0),
      displacement_y(0),
      displacement_z(0),
      displacement_catch(0),
      displacement_stretch(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_displacement_x;
      u_displacement_x.real = this->displacement_x;
      *(outbuffer + offset + 0) = (u_displacement_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_displacement_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_displacement_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_displacement_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->displacement_x);
      union {
        float real;
        uint32_t base;
      } u_displacement_y;
      u_displacement_y.real = this->displacement_y;
      *(outbuffer + offset + 0) = (u_displacement_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_displacement_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_displacement_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_displacement_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->displacement_y);
      union {
        float real;
        uint32_t base;
      } u_displacement_z;
      u_displacement_z.real = this->displacement_z;
      *(outbuffer + offset + 0) = (u_displacement_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_displacement_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_displacement_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_displacement_z.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->displacement_z);
      union {
        int32_t real;
        uint32_t base;
      } u_displacement_catch;
      u_displacement_catch.real = this->displacement_catch;
      *(outbuffer + offset + 0) = (u_displacement_catch.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_displacement_catch.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_displacement_catch.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_displacement_catch.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->displacement_catch);
      union {
        int32_t real;
        uint32_t base;
      } u_displacement_stretch;
      u_displacement_stretch.real = this->displacement_stretch;
      *(outbuffer + offset + 0) = (u_displacement_stretch.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_displacement_stretch.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_displacement_stretch.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_displacement_stretch.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->displacement_stretch);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_displacement_x;
      u_displacement_x.base = 0;
      u_displacement_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_displacement_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_displacement_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_displacement_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->displacement_x = u_displacement_x.real;
      offset += sizeof(this->displacement_x);
      union {
        float real;
        uint32_t base;
      } u_displacement_y;
      u_displacement_y.base = 0;
      u_displacement_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_displacement_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_displacement_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_displacement_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->displacement_y = u_displacement_y.real;
      offset += sizeof(this->displacement_y);
      union {
        float real;
        uint32_t base;
      } u_displacement_z;
      u_displacement_z.base = 0;
      u_displacement_z.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_displacement_z.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_displacement_z.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_displacement_z.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->displacement_z = u_displacement_z.real;
      offset += sizeof(this->displacement_z);
      union {
        int32_t real;
        uint32_t base;
      } u_displacement_catch;
      u_displacement_catch.base = 0;
      u_displacement_catch.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_displacement_catch.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_displacement_catch.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_displacement_catch.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->displacement_catch = u_displacement_catch.real;
      offset += sizeof(this->displacement_catch);
      union {
        int32_t real;
        uint32_t base;
      } u_displacement_stretch;
      u_displacement_stretch.base = 0;
      u_displacement_stretch.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_displacement_stretch.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_displacement_stretch.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_displacement_stretch.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->displacement_stretch = u_displacement_stretch.real;
      offset += sizeof(this->displacement_stretch);
     return offset;
    }

    const char * getType(){ return "skyguard_msgs/displacement"; };
    const char * getMD5(){ return "fb276e20172d2c69398be250ef798d78"; };

  };

}
#endif