#ifndef _ROS_skyguard_msgs_ROS_ON_OFF_h
#define _ROS_skyguard_msgs_ROS_ON_OFF_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace skyguard_msgs
{

  class ROS_ON_OFF : public ros::Msg
  {
    public:
      typedef int32_t _on_off_type;
      _on_off_type on_off;

    ROS_ON_OFF():
      on_off(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_on_off;
      u_on_off.real = this->on_off;
      *(outbuffer + offset + 0) = (u_on_off.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_on_off.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_on_off.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_on_off.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->on_off);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_on_off;
      u_on_off.base = 0;
      u_on_off.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_on_off.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_on_off.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_on_off.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->on_off = u_on_off.real;
      offset += sizeof(this->on_off);
     return offset;
    }

    const char * getType(){ return "skyguard_msgs/ROS_ON_OFF"; };
    const char * getMD5(){ return "f5869342823137cec27a54a6786fb6e6"; };

  };

}
#endif