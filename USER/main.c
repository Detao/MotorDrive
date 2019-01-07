#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "modechoice.h"
#include "pwm_input.h"
#include "adc.h"
#include "pwm_control.h"

extern bool MODECHOICE;
extern u16  CurrMode;   //��ǰ����ģʽ
int main(void)
{		
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init(); 
	
	PWM_Output_Init(2000-1,360-1); 		
  PWM_Input_Init(0xFFFF-1,360-1);
 	TIM5_Cap_Init(100-1,7200-1);	
  TIM6_Init(100-1,7200-1);
  TIM5_Start();	
	TIM6_start();
	Adc_Init();
	CurrMode=Flash_ReadData();
#ifdef DEBUG
	printf("currmode:%s\r\n",MODEPrint[CurrMode]);
#endif
  while(1)
	{	
		if(MODECHOICE) 
		{
			enternModeChoice();
#ifdef DEBUG
	    printf("currmode:%s\r\n",MODEPrint[CurrMode]);
#endif
		}
		
		switch(CurrMode)
		{
			case PPM_N_OVERCURRENT:
				PPM_Control();
				break;
			case PPM_OVERCURRENT:
				over_protection();
				PPM_Control();
				break;
			case UART_N_OVERCURRENT:
				Uart_Control();
				break;
			case UART_OVERCURRENT:
				over_protection();
				Uart_Control();
				break;
			default:
				break;
		}
		
 }/*while(1)*/
}

