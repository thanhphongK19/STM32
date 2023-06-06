
#include "button.h"

uint8_t arr[7] = {0};
char buffer1[15];

 void Press_UP (uint32_t address)
 {
	 Flash_Read_Array(address,arr);
	 showLCD(arr);
 }
 void Press_DOWN(uint32_t address)
 {
	 Flash_Read_Array(address,arr);
	 showLCD(arr);
 }
  void showLCD(uint8_t *arr)
	{
		lcd_clear();
		
		sprintf (buffer1, "%02d-%02d-%02d-20%02d",arr[3],arr[4],arr[5],arr[6]);
	  lcd_put_cur(0,0);
	  lcd_send_string(buffer1);
		
	  sprintf (buffer1, "%02d:%02d:%02d",arr[2],arr[1],arr[0]);
	  lcd_put_cur (1,0);
	  lcd_send_string(buffer1);
	}
