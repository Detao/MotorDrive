#ifndef __PWM_INPUT_H_
#define __PWM_INPUT_H_
#include "sys.h"

enum ch{
	CH1,
	CH2,
	CH3,
	CH4
};
typedef struct pwm_input_data
{
	 u8 sta;
	u32 fisrt_value;
	u32 second_value;
	u32 thrid_value;
	u32 timer_value;
	u32 high_value;
	u32 low_value;
}pwm_input_data;
typedef struct pwm_input
{
	          u32  tim;
           	u32  ch;
	pwm_input_data data;
}pwm_input;

extern pwm_input ch1;
extern pwm_input ch2;
extern pwm_input ch3;
extern pwm_input ch4;

void get_pwm(pwm_input* in);


#endif/*__PWM_INPUT_H_*/
