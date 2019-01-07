#ifndef __PWM_CONTROL_H
#define __PWM_CONTROL_H
#include  "sys.h"
#include  "usart.h"

enum MotorDrection{
	MOTOR_REVOLUTION,
	MOTOR_CONNTER_REVOLUTION
};
	
typedef struct  Motor_Config{
	u8  Motor1Drection;
	u8  Motor2Drection;
	u16 Motor1Duty;
	u16 Motor2Duty;
}Motor_Config;


void Uart_Control(void);
void PPM_Control(void );
void over_protection(void);
#endif /*__PWM_CONTROL_H*/
