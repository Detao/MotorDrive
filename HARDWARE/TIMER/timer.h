#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

/*PWMÊä³ö*/
#define OCPWM_TIM         TIM3
#define OCPWM_TIM_RCC     RCC_APB1Periph_TIM3
#define OCPWM_TIM_IRQ     TIM3_IRQn

#define OCPWM_CH1_PIN         GPIO_Pin_6
#define OCPWM_CH1_GPIO_PORT   GPIOA
#define OCPWM_CH1_RCC         RCC_APB2Periph_GPIOA

#define OCPWM_CH2_PIN         GPIO_Pin_7
#define OCPWM_CH2_GPIO_PORT   GPIOA
#define OCPWM_CH2_RCC         RCC_APB2Periph_GPIOA

#define OCPWM_CH3_PIN         GPIO_Pin_0
#define OCPWM_CH3_GPIO_PORT   GPIOB
#define OCPWM_CH3_RCC         RCC_APB2Periph_GPIOB

#define OCPWM_CH4_PIN         GPIO_Pin_1
#define OCPWM_CH4_GPIO_PORT   GPIOB
#define OCPWM_CH4_RCC         RCC_APB2Periph_GPIOB

/*PWM²¶»ñ*/

#define ICPWM_TIM         TIM4
#define ICPWM_TIM_RCC     RCC_APB1Periph_TIM4
#define ICPWM_TIM_IRQ     TIM4_IRQn

#define ICPWM_CH1_PIN         GPIO_Pin_6
#define ICPWM_CH1_GPIO_PORT   GPIOB
#define ICPWM_CH1_RCC         RCC_APB2Periph_GPIOB

#define ICPWM_CH2_PIN         GPIO_Pin_7
#define ICPWM_CH2_GPIO_PORT   GPIOB
#define ICPWM_CH2_RCC         RCC_APB2Periph_GPIOB

#define ICPWM_CH3_PIN         GPIO_Pin_8
#define ICPWM_CH3_GPIO_PORT   GPIOB
#define ICPWM_CH3_RCC         RCC_APB2Periph_GPIOB

#define ICPWM_CH4_PIN         GPIO_Pin_9
#define ICPWM_CH4_GPIO_PORT   GPIOB
#define ICPWM_CH4_RCC         RCC_APB2Periph_GPIOB

#define ICPWM_TIM         TIM4

void PWM_Output_Init(u16 arr,u16 psc);
void PWM_Output_Start(void );
void PWM_Output_Stop(void );


void PWM_Input_Init(u16 arr, u16 psc);
void PWM_Input_Start(void );
void PWM_Input_Stop(void );

void TIM5_Cap_Init(u16 arr,u16 psc);


void TIM5_Start(void );
void TIM5_Stop(void );



void TIM6_Init(u16 arr,u16 psc);
void TIM6_start(void );
void TIM6_stop(void );


#endif
