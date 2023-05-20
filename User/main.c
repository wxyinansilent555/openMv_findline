#include "stm32f10x.h"                  // Device header
#include "stm32f10x_flash.h"
#include "Delay.h"
#include "OLED.h"
#include "Time_interrupt.h"
#include "Motor.h"
#include "Key.h"
#include "PWM.h"                                    
#include "RPM.h"
#include "openMv.h"
#include "Encoder.h"
#include "LED.h"
#include "Serial.h"
#include "Sensor.h"

int  target_speed = 30;    //cm/s  小车整体预期速度
float target_L,target_R;   //      小车预期速度的脉冲数 30cm/s ==> 334.9
#define  track    17.7     //cm    后轮中轴距离
#define  wheel_R  3.248    //cm    轮子的半径
#define R        110       //cm    转向半径
int angle,last_angle, ENABLE_flag = 0;
extern uint8_t Serial_RxData;
u8 key_flag=0;

void go_line(void);

int main(void)
{
	LED_Init();
	OLED_Init();	
	
	sensor_Init();
	Key_Init();
	Motor_Init(); 
	Encoder_Init();	

	USART2_Init(57600);    //V831串口打开
	USART1_Init(57600);    //334透传模块打开
	TIM2_Init();	       //初始化定时器2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE); //立即失能定时器，直到V831初始化完成

	while (1)
	{	
		int key;
		key = Key_Scan(0);
        if(key == KEY_start_res && key_flag == 0)
		{
			key_flag = 1;
			ENABLE_flag = 1 ;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		}
	}
}

int circle = 1;
int test_flag = 0;//题目顺序
/*主控函数 0.05s触发一次*/
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{	
		if(start_time < 45) 
		{
			angle=0;		
			flag_time=0;
			sensor_flag=0;
		}
		else 
		{
		    flag_time++;
		}
		if(test_flag == 1) //任务1 正常走一圈
		{
			if(sensor_flag <= 2)
			{
                go_line();
			}	
			else
			{
				Motor_control_1();
				sensor_flag = 0;
			}		
		}
		else if(test_flag == 2) //任务2超车
		{
			if(sensor_flag < 2)
			{
                go_line();
			}
			else
			{
				Motor_control_2();
				sensor_flag = 0;
			}
		}
		else if(test_flag == 3) //任务3超车两次
		{
			if(sensor_flag > 2)
			{
				Motor_control_3();
				sensor_flag = 0;
				circle = circle + 1;
				if(circle >= 2) circle = 1;
			}
			else
			{
				go_line();
			}
		}
		else if(test_flag == 4) //任务3超车两次
		{
			if(sensor_flag > 2)
			{
				Motor_control_4();
				sensor_flag = 0;
				circle = circle + 1;
				if(circle > 2) circle = 1;
			}
			else
			{
				go_line();
			}
		}				
        
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);		
	}
	
}

void go_line(void)
{
	flag_time++;
    Encoder_Left_Count=Encoder_Left_Get();
	Encoder_Right_Count=Encoder_Right_Get();
	
    speed_L = 45 + Position_PID(angle);  //位置PID
	speed_R = 45 - Position_PID(angle);
		
	if(speed_L < 0)speed_L = 0;               //占空比限幅
	if(speed_R  <0)speed_R = 0;

	Motor_SetSpeed(LPID_realize(speed_L,Encoder_Left_Count),RPID_realize(speed_R,Encoder_Right_Count)); //速度PID
}
