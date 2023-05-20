#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Motor.h"
#include "Delay.h"
#include "sensor.h"
#include "oled.h"

int start_time;
extern int circle;
void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;//AIN1 AIN2 BIN1 BIN2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	PWM_Init();
}

void Motor_SetSpeed(float Speed_L,float Speed_R)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_13);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	PWM_SetCompare1(Speed_L);

	GPIO_SetBits(GPIOB, GPIO_Pin_15);
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	PWM_SetCompare4(Speed_R);
}

float speed;
float Integral_bias, last_error;

//位置式PID
float Position_PID(float error)
{
	float pwm;
	Integral_bias += error;	
	pwm = Kp * error + Ki * Integral_bias + Kd * (error - last_error);
	last_error = error;
	
    if(pwm > 20 )  pwm =  20;
	if(pwm < -20)  pwm = -20;
	
    return pwm;
}

void Motor_control_1(void)
{
	Motor_SetSpeed(80,80);
	Delay_ms(500);
	Motor_SetSpeed(30,80);
	Delay_ms(700);
	Motor_SetSpeed(80,80);
	Delay_ms(1000);
	Motor_SetSpeed(0,0);
	OLED_ShowString(3,1,"Stoping...");
	OLED_Clear();
	Delay_ms(4000);
	Motor_SetSpeed(80,80);
	Delay_ms(1400);
	Motor_SetSpeed(30,80);
	Delay_ms(700);
	Motor_SetSpeed(0,0);
	Delay_ms(3000);
}

void Motor_control_2(void)
{
	Motor_SetSpeed(80,80);
	Delay_ms(500);
	Motor_SetSpeed(30,80);
	Delay_ms(650);
	Motor_SetSpeed(80,80);
	Delay_ms(1000);
	Motor_SetSpeed(80,80);
	Delay_ms(1350);
	Motor_SetSpeed(30,80);
	Delay_ms(500);
	Motor_SetSpeed(80,80);
	Delay_ms(500);
	Motor_SetSpeed(0,0);
	OLED_ShowString(3,1,"Stoping...");
	OLED_Clear();
	Delay_ms(4000);
}

void Motor_control_3(void)
{
	if( circle == 1)
	{
		Motor_SetSpeed(80,80);
	    Delay_ms(500);
	    Motor_SetSpeed(30,80);
	    Delay_ms(1300);
		Motor_SetSpeed(80,30);
		Delay_ms(650);
		Motor_SetSpeed(50,50);
		Delay_ms(1200);
		Motor_SetSpeed(80,30);
		Delay_ms(650);
		Motor_SetSpeed(30,80);
		Delay_ms(650);
		Motor_SetSpeed(50,50);
		Delay_ms(500);
	    Motor_SetSpeed(30,80);
	    Delay_ms(700);
	    Motor_SetSpeed(80,80);
	    Delay_ms(500);
		Motor_SetSpeed(0,0);
	    OLED_ShowString(3,1,"Stoping...");
		OLED_Clear();
		Delay_ms(4000);
	}
	else if(circle == 2)
	{
		Motor_SetSpeed(80,80);
	    Delay_ms(500);
	    Motor_SetSpeed(30,80);
	    Delay_ms(700);
	    Motor_SetSpeed(80,80);
	    Delay_ms(1000);
	    Motor_SetSpeed(0,0);
	    OLED_ShowString(3,1,"Stoping...");
		OLED_Clear();
	    Delay_ms(4000);
	    Motor_SetSpeed(80,80);
	    Delay_ms(1400);
	    Motor_SetSpeed(30,80);
	    Delay_ms(700);
	    Motor_SetSpeed(80,80);
	    Delay_ms(1500);
	}
}

void Motor_control_4(void)
{
	if( circle == 1)
	{
		Motor_SetSpeed(80,80);
	    Delay_ms(500);
	    Motor_SetSpeed(30,80);
	    Delay_ms(1300);
		Motor_SetSpeed(50,50);
	    Delay_ms(400);
		Motor_SetSpeed(80,30);
		Delay_ms(650);
		Motor_SetSpeed(50,50);
		Delay_ms(1200);
		Motor_SetSpeed(80,30);
		Delay_ms(650);
		Motor_SetSpeed(30,80);
		Delay_ms(650);
		Motor_SetSpeed(50,50);
		Delay_ms(500);
	    Motor_SetSpeed(30,80);
	    Delay_ms(700);
	    Motor_SetSpeed(80,80);
	    Delay_ms(500);
		Motor_SetSpeed(80,80);
	    Delay_ms(500);

	}
	else if(circle == 2)
	{
        		
	    Motor_SetSpeed(30,80);
	    Delay_ms(700);
	    Motor_SetSpeed(80,80);
	    Delay_ms(1000);
	    Motor_SetSpeed(0,0);
	    Delay_ms(4000);
	    OLED_ShowString(3,1,"Stoping...");
		OLED_Clear();
	    Motor_SetSpeed(80,80);
	    Delay_ms(1400);
	    Motor_SetSpeed(30,80);
	    Delay_ms(700);
	    Motor_SetSpeed(80,80);
	    Delay_ms(1500);
	}
}

