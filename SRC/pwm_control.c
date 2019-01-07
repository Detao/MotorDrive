#include "pwm_control.h"
#include "pwm_input.h"
#include "adc.h"
/* 7e    00 07         00 00 00            00 00 00                   ee*/
/*帧头  数据长度   电机1的方向占空比  电机2的方向和占空比       帧尾   */
/*00正向   01 反向  占空比不超过2000*/
u8 UART_Packet_Pase(Motor_Config* conf)
{
	u16 packet_data_len=0;
	 if(USART_RX_BUF[0]!=0x7e)
	 {
		 USART_RX_STA=0;
		 return 1;
	 }
	 packet_data_len=(USART_RX_BUF[1]<<8)|USART_RX_BUF[2];
	 if(USART_RX_BUF[packet_data_len+2]!=0xee)
	 {
		 USART_RX_STA=0;
		 return 1;
	 }
	 conf->Motor1Drection=USART_RX_BUF[3];
	 conf->Motor2Drection=USART_RX_BUF[6];
	 if(((USART_RX_BUF[4]<<8)|USART_RX_BUF[5])<=2000&&((USART_RX_BUF[7]<<8)|USART_RX_BUF[8])<=2000)
	 {
		 conf->Motor1Duty=((USART_RX_BUF[4]<<8)|USART_RX_BUF[5]);
		 conf->Motor2Duty=((USART_RX_BUF[7]<<8)|USART_RX_BUF[8]);
		 USART_RX_STA=0;
		 return 0;
	 }
	 USART_RX_STA=0;
	 return 1;
}
void motor_set(Motor_Config* conf)
{
  printf("motor1_drection:%d motor2_drection:%d motor1_pwm:%d motor2_pwm:%d \r\n",conf->Motor1Drection,conf->Motor2Drection,conf->Motor1Duty,conf->Motor2Duty);
	if(conf->Motor1Drection)
	{
	  TIM_SetCompare1(TIM3,conf->Motor1Duty);
		TIM_SetCompare3(TIM3,0);
	}else
	{
		TIM_SetCompare1(TIM3,0);
		TIM_SetCompare3(TIM3,conf->Motor1Duty);
	}
	if(conf->Motor2Drection)
	{
		TIM_SetCompare2(TIM3,0);
		TIM_SetCompare4(TIM3,conf->Motor2Duty);
	}else
	{
		TIM_SetCompare2(TIM3,conf->Motor2Duty);
		TIM_SetCompare4(TIM3,0);
	}
}
u32 ppm_get_pwm(pwm_input_data in)
{
	return ((float)in.high_value/(float)(in.high_value+in.low_value))*2000;
}
void PPM_Control()
{
	Motor_Config motor_config={0};
	if(ch1.data.sta&0X80)   // 通道1完成捕获 电机1正转 
		{
			motor_config.Motor1Drection=MOTOR_REVOLUTION;
			motor_config.Motor1Duty=ppm_get_pwm(ch1.data);
			ch1.data.sta=0;//开启下一次捕获
		}
		if(ch2.data.sta&0X80)//通道2完成捕获 电机2正转
		{
			motor_config.Motor2Drection=MOTOR_REVOLUTION;
			motor_config.Motor2Duty=ppm_get_pwm(ch2.data);
			ch2.data.sta=0;//开启下一次捕获
		}
		if(ch3.data.sta&0X80)//通道3完成捕获 电机1反转
		{
			motor_config.Motor1Drection=MOTOR_CONNTER_REVOLUTION;
			motor_config.Motor1Duty=ppm_get_pwm(ch3.data);
			ch3.data.sta=0;//开启下一次捕获
		}
		if(ch4.data.sta&0X80)//通道4完成捕获 电机2反转
		{
			motor_config.Motor2Drection=MOTOR_CONNTER_REVOLUTION;
			motor_config.Motor2Duty=ppm_get_pwm(ch4.data);
			ch4.data.sta=0;//开启下一次捕获
		}
		motor_set(&motor_config);
}

void Uart_Control()
{
	Motor_Config motor_config;
	if(USART_RX_STA&0x8000)
	 {					   
			if(!UART_Packet_Pase(&motor_config))
				{
					 motor_set(&motor_config);
				}
		}
}
extern u8 adc;
void over_protection()
{
	u32 adcx1=0,adcx2=0;
	float temp1,temp2;
	Motor_Config motor_config;
	if(adc)
	{
		adc=0;
		adcx1=Get_Adc_Average(ADC_Channel_1,10);
		adcx2=Get_Adc_Average(ADC_Channel_2,10);
		temp1=(float)adcx1*(3.3/4096);
		temp2=(float)adcx2*(3.3/4096);
	}
	if(temp1>(3.3-0.02))
	{
		motor_config.Motor1Duty=0;
		motor_set(&motor_config);
    printf("motor1 over\r\n");
	}
	if(temp2>(3.3-0.02))
	{
		motor_config.Motor2Duty=0;
		motor_set(&motor_config);
	}
}
