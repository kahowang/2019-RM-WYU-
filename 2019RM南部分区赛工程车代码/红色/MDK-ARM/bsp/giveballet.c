#include "giveballet.h"      
int ref_giveballet_angle;
int ref_giveballet_angle_open = 900;  //2006���սǶ�Ϊ900
int ref_giveballet_angle_close = 0;  //2006�ز�
int jscope_ref_giveballet_angle;

void giveballet(void)  //��������
{
			if(lifting_embrace_giveballet_count_time < 11)
			{
			 UP_OR_DOWN = UP;	 //̧������
			}
			if((lifting_embrace_giveballet_count_time>10)&&(lifting_embrace_giveballet_count_time<61)){
				ref_giveballet_angle =   ref_giveballet_angle_open;  //����   
			}
		  if ((lifting_embrace_giveballet_count_time>61)&&(lifting_embrace_giveballet_count_time<90)){
						ref_giveballet_angle	= ref_giveballet_angle_close;  // �ز�  
					  UP_OR_DOWN = DOWN;          //�½�	
				}   
}  
/*���6Ϊ�������*/
void pid_giveballet_fcn(void)
{
			pid_calc(&pid2_pos[5], moto_upper[5].total_angle/100, ref_giveballet_angle);
			pid_calc(&pid2_spd[5],moto_upper[5].speed_rpm,pid2_pos[5].pos_out);
			jscope_ref_giveballet_angle = moto_upper[5].total_angle/100;
}