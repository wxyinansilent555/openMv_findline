#ifndef __MOTOR_H
#define __MOTOR_H
extern int start_time;
void Motor_Init(void);
void Motor_SetSpeed(float Speed_L,float Speed_R);
void Motor_control_1(void);
void Motor_control_2(void);
void Motor_control_3(void);
void Motor_control_4(void);
float Position_PID(float error);

static float Kp = 0.51;
static float Ki = 0;
static float Kd = 0.008;

#endif
