#include "timer.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "modechoice.h"
#include "pwm_input.h"
#include "led.h"

void PWM_Output_Init(u16 arr,u16 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOB , ENABLE); 
	/*����GPIO*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
 	/*����TIM*/
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	/*����PWM*/
	/*ͨ��1*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/*ͨ��2*/
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/*ͨ��3*/
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	/*ͨ��4*/
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); 
}
void PWM_Output_Start(void )
{
	TIM_Cmd(TIM3,ENABLE);
}
void PWM_Output_Stop(void )
{
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare4(TIM3,0);
	TIM_SetCompare2(TIM3,0);
	TIM_SetCompare3(TIM3,0);
	TIM_Cmd(TIM3,DISABLE);
}



void PWM_Input_Init(u16 arr,u16 psc)
{	 
  //��ʱ��4ͨ�����벶������
  TIM_ICInitTypeDef  TIM4_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6| GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);						 
	
	//��ʼ����ʱ��4 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
  
	//��ʼ��TIM5���벶�����
	 TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; 
   TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
   TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
   TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
   TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
   TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	 
	 TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2 ;
	 TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	 TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3 ;
	 TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	 TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;
	 TIM_ICInit(TIM4, &TIM4_ICInitStructure);
  
	 //�жϷ����ʼ��
	 NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	 NVIC_Init(&NVIC_InitStructure);
	 
	 ch1.ch=CH1;
	 ch1.tim=(u32)TIM4;
	 ch2.ch=CH2;
	 ch2.tim=(u32)TIM4;
	 ch3.ch=CH3;
	 ch3.tim=(u32)TIM4;
	 ch4.ch=CH4;
	 ch4.tim=(u32)TIM4;
	
	
}
void PWM_Input_Start()
{
	TIM_ITConfig(TIM4,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�	
  TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��5
}
void PWM_Input_Stop()
{
	TIM_ITConfig(TIM4,TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,DISABLE);//��������ж� ,����CC1IE�����ж�	
  TIM_Cmd(TIM4,DISABLE ); 	//ʹ�ܶ�ʱ��5
}

void TIM4_IRQHandler(void)
{ 
  
		if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1); 		
			get_pwm(&ch1);
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2); 		
			get_pwm(&ch2);
	  }
	
		if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3); 		
			get_pwm(&ch3);
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4); 		
			get_pwm(&ch4);
		}
	
}


//��ʱ��5ͨ��1���벶������

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
	
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	
}
void TIM5_Start(void )
{
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
}
void TIM5_Stop(void )
{
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,DISABLE);//��������ж� ,����CC1IE�����ж�	
	TIM_Cmd(TIM5,DISABLE ); 	//ʹ�ܶ�ʱ��5
}

u8  TIM5CH1_CAPTURE_STA=0;					
u16	TIM5CH1_CAPTURE_VAL=0;	
 
//��ʱ��5�жϷ������
extern bool MODECHOICE;
extern bool ChoiceUnlink;
void TIM5_IRQHandler(void)
{ 
	
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				TIM5CH1_CAPTURE_VAL++;
			if(TIM5CH1_CAPTURE_VAL==300)
			{
				MODECHOICE=TRUE;
			}
			if(TIM5CH1_CAPTURE_VAL>500)
			{
				printf("����5s\r\n");
//				 __set_FAULTMASK(1);//?????
//         NVIC_SystemReset();//?
			}
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			delay_us(10);
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  	
        TIM5CH1_CAPTURE_STA=0;
        TIM5CH1_CAPTURE_VAL=0;			
        ChoiceUnlink=TRUE;				
		   	TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���	
			}else if(!MODECHOICE)  								//��δ��ʼ,��һ�β���������
			{
				ChoiceUnlink=FALSE;
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   	TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			
	
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
 
}
void TIM6_Init(u16 arr,u16 psc)
{	 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	//ʹ��TIM5ʱ��
	
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

}
void TIM6_start(void)
{
	  TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE );
		TIM_Cmd(TIM6,ENABLE ); 	//ʹ�ܶ�ʱ��5
}
void TIM6_stop(void)
{
	  TIM_ITConfig(TIM6,TIM_IT_Update,DISABLE );
		TIM_Cmd(TIM6,DISABLE ); 	//ʹ�ܶ�ʱ��5
}
u32 waittime=0;
u8  ledtime=0;
extern u16  CurrMode;   //��ǰ����ģʽ
u8 adc=0;
u32 adc_time=0;
void TIM6_IRQHandler(void)
{
		
	if(MODECHOICE){
		waittime++;
		ledtime++;
		if(waittime==300)
		{
			printf("ģʽȷ��\r\n");
		}
		if(waittime==500)
		{
		  Flash_WriteData(CurrMode);
			MODECHOICE=FALSE;
			waittime=0;
			if(CurrMode==0) LED0=0;
			else  LED1=0;	
		}
		if(ledtime==20)
		{
			ledtime=0;
			if(CurrMode==0) LED0=~LED0;
			else  LED1=~LED1;			
		} 
	}
	if(CurrMode==PPM_OVERCURRENT||CurrMode==UART_OVERCURRENT)
	{
		adc_time++;
		if(adc_time==25)
		{
			adc_time=0;
			adc=1;
		}
		
	}
	
	 TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //����жϱ�־λ
}
