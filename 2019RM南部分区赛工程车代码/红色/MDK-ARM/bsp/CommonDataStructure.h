#ifndef __COMMONDATASTRUCTURE_H
#define __COMMONDATASTRUCTURE_H

/******************************************************
���ļ�Ϊ�������ݽṹ
******************************************************/

#include  "allheader.h"  


//��ʽת��������
typedef union
{
    uint8_t U[4];
    float F;
    int I;
}FloatTrans;

typedef union
{
    uint8_t  u[4];
    uint16_t U;
    int I;
}Uint16Trans;


#endif
