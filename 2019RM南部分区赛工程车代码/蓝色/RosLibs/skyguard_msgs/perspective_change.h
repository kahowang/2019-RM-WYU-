#ifndef _ROS_skyguard_msgs_perspective_change_h
#define _ROS_skyguard_msgs_perspective_change_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace skyguard_msgs
{

  class perspective_change : public ros::Msg
  {
    public:
      typedef int32_t _perspective_type;
      _perspective_type perspective;

    perspective_change():
      perspective(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_perspective;
      u_perspective.real = this->perspective;
      *(outbuffer + offset + 0) = (u_perspective.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_perspective.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_perspective.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_perspective.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->perspective);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_perspective;
      u_perspective.base = 0;
      u_perspective.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_perspective.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_perspective.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_perspective.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->perspective = u_perspective.real;
      offset += sizeof(this->perspective);
     return offset;
    }

    const char * getType(){ return "skyguard_msgs/perspective_change"; };
    const char * getMD5(){ return "c39f0cdd5ee31742b5901cec1e548399"; };

  };

}
#endif