#include "pwm_input.h"

pwm_input ch1;
pwm_input ch2;
pwm_input ch3;
pwm_input ch4;

static u32 getcapture(u32 TIM,u8 ch)
{
	if(ch==CH1)
    return TIM_GetCapture1((TIM_TypeDef *)TIM);
	if(ch==CH2)
		return TIM_GetCapture2((TIM_TypeDef *)TIM);
	if(ch==CH3)
		return TIM_GetCapture3((TIM_TypeDef *)TIM);
	if(ch==CH4)
		return TIM_GetCapture4((TIM_TypeDef *)TIM);
	return 0;
}
static void polarityConfig(u32 TIM,u8 ch,uint16_t sta)
{
	if(ch==CH1)
    TIM_OC1PolarityConfig((TIM_TypeDef *)TIM,sta);
	if(ch==CH2)
		TIM_OC2PolarityConfig((TIM_TypeDef *)TIM,sta);
	if(ch==CH3)
		TIM_OC3PolarityConfig((TIM_TypeDef *)TIM,sta);
	if(ch==CH4)
		TIM_OC4PolarityConfig((TIM_TypeDef *)TIM,sta);
}
void get_pwm(pwm_input *in)
{
	if (in->data.sta& 0X40)		
			{
				in->data.second_value = getcapture(in->tim,in->ch);   
				if (in->data.second_value < in->data.fisrt_value) in->data.timer_value = 65535;
				else in->data.timer_value = 0;
				
				in->data.high_value = in->data.second_value - in->data.fisrt_value
						+ in->data.timer_value;		//得到总的高电平的时间
				in->data.sta = 0;		//捕获标志位清零
				in->data.sta |=0x20;
				
				polarityConfig(in->tim,in->ch,TIM_ICPolarity_Rising); //设置为上升沿捕获		  
			}else if(in->data.sta & 0X20){
			     in->data.thrid_value = getcapture(in->tim,in->ch);//记录下此时的定时器计数值
				if (in->data.thrid_value < in->data.second_value)
				{
					in->data.timer_value = 65535;
				}
				else
					in->data.timer_value = 0;
				in->data.low_value = in->data.thrid_value - in->data.second_value
						+ in->data.timer_value;		
				in->data.sta = 0;		//捕获标志位清零
				in->data.sta |=0x80;
			}
			else 
			{
				in->data.fisrt_value = getcapture(in->tim,in->ch);	
				in->data.sta |= 0X40;		
				polarityConfig(in->tim,in->ch, TIM_ICPolarity_Falling);
			}
}

