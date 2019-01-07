#include "modechoice.h"
#include "key.h"
#include "stdio.h"
#include "delay.h"
#include  "timer.h"
bool MODECHOICE=FALSE;
u16  CurrMode=0;   //当前所处模式
bool ChoiceUnlink=FALSE;
extern u32 waittime;
extern u8  TIM5CH1_CAPTURE_STA;		

#ifdef DEBUG
char MODEPrint[][30]={"PPM_N_OVERCURRENT_MODE","PPM_OVERCURRENT","UART_N_OVERCURRENT_MODE","UART_OVERCURRENT_MODE"};
#endif

void enternModeChoice()
{
#ifdef DEBUG
	printf("当前所处模式为：%s\r\n",MODEPrint[CurrMode]);
#endif
	PWM_Output_Stop();
	PWM_Input_Stop();
	if(ChoiceUnlink){
		//TIM5_Stop();
		
	  while(MODECHOICE)
	 {
		 if(KEY_Scan(0)==WKUP_PRES)	
		{
			waittime=0;
			CurrMode++;
			if(CurrMode>=4)
			{
				CurrMode=0;
			}
			switch(CurrMode)
		  {
			  case PPM_N_OVERCURRENT:
					PWM_Output_Start();
	        PWM_Input_Start();
				  printf("MODE1\r\n");
				  break;
			  case PPM_OVERCURRENT:
					PWM_Output_Start();
	        PWM_Input_Start();
				  printf("MODE2\r\n");
				  break;
			  case UART_N_OVERCURRENT:
					PWM_Output_Start();
				  printf("MODE3\r\n");
				  break;
			  case UART_OVERCURRENT:
					PWM_Output_Start();
				  printf("MODE4\r\n");
				  break;
			  default:
				  break;
		  }
		}
  }
	 TIM5CH1_CAPTURE_STA=0;
 }
}

void Flash_WriteData(uint16_t CurrMode)
{
	FLASH_Unlock();
	FLASH_ErasePage(MODE_SAVE_ADDRESS);//擦除这个扇区
  FLASH_ProgramHalfWord(MODE_SAVE_ADDRESS,CurrMode);
	FLASH_Lock();
}
uint16_t Flash_ReadData()
{
	return *(__IO uint16_t*)MODE_SAVE_ADDRESS; 
}