#include "giveballet.h"      
int ref_giveballet_angle;
int ref_giveballet_angle_open = 900;  //2006开舱角度为900
int ref_giveballet_angle_close = 0;  //2006关舱
int jscope_ref_giveballet_angle;

void giveballet(void)  //供弹动作
{
			if(lifting_embrace_giveballet_count_time < 11)
			{
			 UP_OR_DOWN = UP;	 //抬升供弹
			}
			if((lifting_embrace_giveballet_count_time>10)&&(lifting_embrace_giveballet_count_time<61)){
				ref_giveballet_angle =   ref_giveballet_angle_open;  //开舱   
			}
		  if ((lifting_embrace_giveballet_count_time>61)&&(lifting_embrace_giveballet_count_time<90)){
						ref_giveballet_angle	= ref_giveballet_angle_close;  // 关舱  
					  UP_OR_DOWN = DOWN;          //下降	
				}   
}  
/*电机6为供弹电机*/
void pid_giveballet_fcn(void)
{
			pid_calc(&pid2_pos[5], moto_upper[5].total_angle/100, ref_giveballet_angle);
			pid_calc(&pid2_spd[5],moto_upper[5].speed_rpm,pid2_pos[5].pos_out);
			jscope_ref_giveballet_angle = moto_upper[5].total_angle/100;
}