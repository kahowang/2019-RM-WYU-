#include  "catch.h" 
int CATCH_ON_OFF = 0;   //是否夹取标志位
int32_t ref_angle0;//夹取机构
int32_t ref_angle1;//夹取机构  
int32_t jscope_ref_angle0;//夹取机构
int32_t jscope_ref_angle1;//夹取机构 

int32_t catching_time = 30;  //翻转记录时间，600ms为阈值
/*夹取S曲线*/
int32_t catch_angle = 83882; //夹取输入角度
int Sin_point_catch = 200;  //查表法为200个点
int Sin_control_time_catch_up = 1;  //S型曲线，每经过Sin_control_time  ms就跳到下一个插值
int Sin_control_time_catch_down = 3;  //S型曲线，每经过Sin_control_time  ms就跳到下一个插值
  
float Sin_up_table_catch[200+2] = {0,6.1684e-05,0.00024672,0.00055506,0.00098664,0.0015413,0.002219,0.0030195,0.0039426,0.0049882,0.0061558,0.0074453,0.0088564,0.010389,0.012042,0.013815,0.015708,0.017721,0.019853,0.022103,0.024472,0.026957,0.02956,0.032278,0.035112,0.03806,0.041123,0.044298,0.047586,0.050986,0.054497,0.058117,0.061847,0.065684,0.069629,0.07368,0.077836,0.082096,0.08646,0.090925,0.095492,0.10016,0.10492,0.10978,0.11474,0.1198,0.12494,0.13018,0.13552,0.14094,0.14645,0.15204,0.15773,0.16349,0.16934,0.17528,0.18129,0.18738,0.19355,0.19979,0.20611,0.2125,0.21896,0.22549,0.23209,0.23875,0.24548,0.25227,0.25912,0.26604,0.273,0.28003,0.28711,0.29424,0.30143,0.30866,0.31594,0.32326,0.33063,0.33804,0.34549,0.35298,0.3605,0.36806,0.37566,0.38328,0.39093,0.39861,0.40631,0.41404,0.42178,0.42955,0.43733,0.44513,0.45295,0.46077,0.4686,0.47645,0.48429,0.49215,0.5,0.50785,0.51571,0.52355,0.5314,0.53923,0.54705,0.55487,0.56267,0.57045,0.57822,0.58596,0.59369,0.60139,0.60907,0.61672,0.62434,0.63194,0.6395,0.64702,0.65451,0.66196,0.66937,0.67674,0.68406,0.69134,0.69857,0.70576,0.71289,0.71997,0.727,0.73396,0.74088,0.74773,0.75452,0.76125,0.76791,0.77451,0.78104,0.7875,0.79389,0.80021,0.80645,0.81262,0.81871,0.82472,0.83066,0.83651,0.84227,0.84796,0.85355,0.85906,0.86448,0.86982,0.87506,0.8802,0.88526,0.89022,0.89508,0.89984,0.90451,0.90907,0.91354,0.9179,0.92216,0.92632,0.93037,0.93432,0.93815,0.94188,0.9455,0.94901,0.95241,0.9557,0.95888,0.96194,0.96489,0.96772,0.97044,0.97304,0.97553,0.9779,0.98015,0.98228,0.98429,0.98618,0.98796,0.98961,0.99114,0.99255,0.99384,0.99501,0.99606,0.99698,0.99778,0.99846,0.99901,0.99944,0.99975,0.99994,1,1};
int32_t Sin_up_y1_catch;  
int32_t Sin_up_y0_catch;
int32_t Sin_up_x1_catch;
int32_t Sin_up_x0_catch;//每一段都清零
int32_t Sin_up_x_catch;   //每一段都清零
int32_t Sin_up_y_catch;
int Sin_up_count_catch;   //S型曲线上升计数 
/*******************Lifting_DOWN************************/	
float Sin_down_table_catch[200+2] = {1,0.99994,0.99975,0.99944,0.99901,0.99846,0.99778,0.99698,0.99606,0.99501,0.99384,0.99255,0.99114,0.98961,0.98796,0.98618,0.98429,0.98228,0.98015,0.9779,0.97553,0.97304,0.97044,0.96772,0.96489,0.96194,0.95888,0.9557,0.95241,0.94901,0.9455,0.94188,0.93815,0.93432,0.93037,0.92632,0.92216,0.9179,0.91354,0.90907,0.90451,0.89984,0.89508,0.89022,0.88526,0.8802,0.87506,0.86982,0.86448,0.85906,0.85355,0.84796,0.84227,0.83651,0.83066,0.82472,0.81871,0.81262,0.80645,0.80021,0.79389,0.7875,0.78104,0.77451,0.76791,0.76125,0.75452,0.74773,0.74088,0.73396,0.727,0.71997,0.71289,0.70576,0.69857,0.69134,0.68406,0.67674,0.66937,0.66196,0.65451,0.64702,0.6395,0.63194,0.62434,0.61672,0.60907,0.60139,0.59369,0.58596,0.57822,0.57045,0.56267,0.55487,0.54705,0.53923,0.5314,0.52355,0.51571,0.50785,0.5,0.49215,0.48429,0.47645,0.4686,0.46077,0.45295,0.44513,0.43733,0.42955,0.42178,0.41404,0.40631,0.39861,0.39093,0.38328,0.37566,0.36806,0.3605,0.35298,0.34549,0.33804,0.33063,0.32326,0.31594,0.30866,0.30143,0.29424,0.28711,0.28003,0.273,0.26604,0.25912,0.25227,0.24548,0.23875,0.23209,0.22549,0.21896,0.2125,0.20611,0.19979,0.19355,0.18738,0.18129,0.17528,0.16934,0.16349,0.15773,0.15204,0.14645,0.14094,0.13552,0.13018,0.12494,0.1198,0.11474,0.10978,0.10492,0.10016,0.095492,0.090925,0.08646,0.082096,0.077836,0.07368,0.069629,0.065684,0.061847,0.058117,0.054497,0.050986,0.047586,0.044298,0.041123,0.03806,0.035112,0.032278,0.02956,0.026957,0.024472,0.022103,0.019853,0.017721,0.015708,0.013815,0.012042,0.010389,0.0088564,0.0074453,0.0061558,0.0049882,0.0039426,0.0030195,0.002219,0.0015413,0.00098664,0.00055506,0.00024672,6.1684e-05,0,0};
int32_t Sin_down_y1_catch;
int32_t Sin_down_y0_catch;
int32_t Sin_down_x1_catch;
int32_t Sin_down_x0_catch; //每一段都清零
int32_t Sin_down_x_catch;  //每一段都清零
int32_t Sin_down_y_catch;
int Sin_down_count_catch;   //S型曲线下降计数
	
void Sin_up_y_calc_catch(void)
{
	/*公式
		     (y1-y0)(x-x0)         (y1-y0)=(Sin_up_table[Sin_up_count+1]-Sin_up_table[Sin_up_count])   (x-x0)=(Sin_up_x-Sin_up_x0)=Sin_up_x   
		y = ---------------	+ y0   y0=Sin_up_table[Sin_up_count]     
					 (x1-x0)             (x1-x0)= Sin_control_time  
	*/
			Sin_up_y_catch = catch_angle*( ((Sin_up_table_catch[Sin_up_count_catch+1]-Sin_up_table_catch[Sin_up_count_catch])*(Sin_up_x_catch))/Sin_control_time_catch_up + Sin_up_table_catch[Sin_up_count_catch] );
			Sin_up_x_catch++;
			if(Sin_up_x_catch >Sin_control_time_catch_up)
			{
				 Sin_up_x_catch = 0;
				 Sin_up_count_catch++;
			}
			if(Sin_up_count_catch>Sin_point_catch)
			{
					Sin_up_count_catch = Sin_point_catch;
			}
			ref_angle0 =  Sin_up_y_catch;
			ref_angle1 =  -Sin_up_y_catch;
			Sin_down_count_catch = 0;
			Sin_down_x_catch = 0;
}

void Sin_down_y_calc_catch(void)
{
			Sin_down_y_catch = catch_angle*( ((Sin_down_table_catch[Sin_down_count_catch+1]-Sin_down_table_catch[Sin_down_count_catch])*(Sin_down_x_catch))/Sin_control_time_catch_down + Sin_down_table_catch[Sin_down_count_catch] );  
			Sin_down_x_catch++;
			if(Sin_down_x_catch >Sin_control_time_catch_down)
			{
				 Sin_down_x_catch = 0;
				 Sin_down_count_catch++;
			}
			if(Sin_down_count_catch>Sin_point_catch)
			{
					Sin_down_count_catch = Sin_point_catch;
			}
			ref_angle0 =  Sin_down_y_catch;
			ref_angle1 =  -Sin_down_y_catch;
			Sin_up_count_catch = 0;
			Sin_up_x_catch = 0;
}	

void Step_up_y_calc_catch(void)    //夹取角度的阶跃输入
{
		  ref_angle0 =  catch_angle;	 //	翻转给定角度方式为阶跃输入				
			ref_angle1 =  -catch_angle;   // 翻转给定角度方式为阶跃输入
			Sin_down_count_catch = 0;
			Sin_down_x_catch = 0;
}
	
/*夹取*/
void pid_catching_fcn(void)  //双闭环调速
{
			/*电机2，3为夹取机构电机*/
			pid_calc(&pid2_pos[2], moto_upper[2].total_angle, ref_angle0);
			pid_calc(&pid2_spd[2],moto_upper[2].speed_rpm/19.2,pid2_pos[2].pos_out);
	   	pid_calc(&pid2_pos[3], moto_upper[3].total_angle, ref_angle1);
			pid_calc(&pid2_spd[3],moto_upper[3].speed_rpm/19.2,pid2_pos[3].pos_out);
	    jscope_ref_angle0 =  moto_upper[2].total_angle;
	    jscope_ref_angle1 =  moto_upper[3].total_angle;
}

void keyboard_remote_control_catching(void)  //按"Q"或MiniPc发送displacementcatch==1进行夹取翻转动作，按"E"伸缩后夹取
{
    catch_action();   //夹取动作函数
	  stretch();        //伸缩动作
}

/*夹取动作函数*/
void catch_action(void)
{
	if((KEY_Q) || ((displacementcatch==1)&&(ROS_ON_OFF == ON)) )   //按“Q” 或者 拨杆在中间触发 夹取  
	{   
		  CATCH_ON_OFF = ON;
		  UP_OR_DOWN = 3; //夹取时需要上升的小角度
		  ref_angle2_press_lifting =  ref_angle2_lifting  ; //获取按键时抬升角度
			ref_angle3_press_lifting =  ref_angle3_lifting  ; //获取按键时抬升角度	  
		  displacementcatch = 0;   //displacementcatch 置零，有下次信息才开启
		  catching_time =  0;  //开始计时，500ms翻转
	}
					if ( (catching_time < 5)&&(CATCH_ON_OFF == ON) )
					{
							Sin_up_y_calc_catch();     //	翻转给定角度方式为阶跃型输入	
					}else if ( (5<catching_time)&&(catching_time<10)&&(CATCH_ON_OFF == ON) ){  //500ms-1000ms 时间进行夹取的增加抬升
							ref_angle2_lifting =  ref_angle2_press_lifting +  ref_angle_increase_lifting;  //按下时抬升的角度 + 额外增加角度
							ref_angle3_lifting =  ref_angle3_press_lifting +  ref_angle_increase_lifting;
					}else if ( (10<catching_time)&&(catching_time<24)&&(CATCH_ON_OFF == ON) ){ //1000ms-2400ms 时间进行翻转
							Sin_down_y_calc_catch();
					}else if ( (24<catching_time)&&(catching_time<29)&&(CATCH_ON_OFF == ON) ){ //2400ms-2900ms 下降到原来的夹取抬升角度
							ref_angle2_lifting = ref_angle2_press_lifting;
							ref_angle3_lifting = ref_angle3_press_lifting;
					}
					if(catching_time > 29)
					{
						CATCH_ON_OFF = 	OFF;
					}

}