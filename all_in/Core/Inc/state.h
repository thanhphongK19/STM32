#ifndef STATE_H_
#define STATE_H_
#include "stm32f1xx.h"
#include "lcd.h"
#include "flash.h"
#include "DS3231.h"
#include "stdio.h"
#include "button.h"
#include "main.h"


extern void stateMachineUpdate(void);
void TASK_Clock(void);
void TASK_Handle(void);
extern void Task_Storage (void);
extern void Sendbuffer (uint8_t *buffer_Send);

#endif /* STATE_H_ */