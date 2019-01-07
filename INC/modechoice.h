#ifndef __MODECHOICE_H__
#define __MODECHOICE_H__
#include "sys.h"
typedef enum{FALSE=0,TRUE=!FALSE} bool;

#define MODE_SAVE_ADDRESS 0x0807F800

enum MODE{
	PPM_N_OVERCURRENT,
	PPM_OVERCURRENT,
	UART_N_OVERCURRENT,
	UART_OVERCURRENT	
};

#ifdef DEBUG
extern char MODEPrint[][30];
#endif

void enternModeChoice(void );
uint16_t Flash_ReadData(void );
void Flash_WriteData(uint16_t CurrMode );

#endif  /*MODECHOICE_H*/

