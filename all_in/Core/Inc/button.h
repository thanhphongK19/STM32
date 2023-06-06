#include "stdio.h"
#include "stm32f1xx.h"
#include "lcd.h"
#include "flash.h"

extern void Press_UP (uint32_t address);
extern void Press_DOWN(uint32_t address);
       void showLCD(uint8_t *arr);