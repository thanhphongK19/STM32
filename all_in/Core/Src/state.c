#include "state.h"

extern uint32_t timer;
uint8_t  sec,min,hour,day,date,month,year;
char buffer[15];
char buffer_UART[1000];
uint8_t count=0;
int oie = 1;
uint8_t arr_w[7] = {0};
uint32_t address = 0x0800FC00;
uint32_t address1 = 0;
UART_HandleTypeDef huart1;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)  // sensor detect
{
	    oie = 0;
}

void stateMachineUpdate(void)
{
	TASK_Clock(); // show clock
	
	 if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==GPIO_PIN_RESET)   // nut nhan PA3
	 {
		 do{
         HAL_Delay(5);
		   }
     while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==GPIO_PIN_RESET);
			timer = 10000;
      lcd_clear();
		  sprintf (buffer, "Wait button...");
	    lcd_put_cur(0,0);
	    lcd_send_string(buffer);
			TASK_Handle();
	 }
	 
	 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET && oie == 0)
	 {
		  Task_Storage();
	 }
	
}


void TASK_Clock(void)  // hien thi dong ho 
{     
			Get_Time(&sec,&min,&hour,&day,&date,&month,&year);
		  sprintf (buffer, "%02d-%02d-%02d-20%02d",day,date,month,year);
	    lcd_put_cur(0,0);
	    lcd_send_string(buffer);
		
	    sprintf (buffer, "%02d:%02d:%02d Sum=%02d",hour,min,sec,count);
	    lcd_put_cur (1,0);
	    lcd_send_string(buffer);
}	
void Task_Storage()  // luu du lieu vao bo nho flash
{
      oie = 1;
		  Get_Time(&sec,&min,&hour,&day,&date,&month,&year);
		  arr_w[0]= sec;
		  arr_w[1]= min;
		  arr_w[2]= hour;
		  arr_w[3]= day;
		  arr_w[4]= date;
		  arr_w[5]= month;
		  arr_w[6]= year;
	    sprintf(buffer_UART,"%02d:%02d:%02d %02d/%02d/%02d/20%02d \n",hour,min,sec,day,date,month,year);
	    HAL_UART_Transmit(&huart1,(uint8_t*)buffer_UART,sizeof(buffer_UART),1000);
		  Flash_Write_Array(address,arr_w);
		  count = count + 1;
		  address = address + 8;
		  address1= address;
		  HAL_Delay(1000); 
}

void TASK_Handle(void)
{
 while(1)
 {
			if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET)
	    {
		    do{
          HAL_Delay(5);
		      }
        while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_RESET);
				timer = 20000;
			  if(address1==0x0800FC00)
			  {
			 	  address1 = address-8;
					Press_UP(address1);
			  }
			  else
			  { 
				  address1 = address1 - 8;
				  Press_UP(address1);
			  }
			}
			
			else if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_RESET)
	    {
		   do{
         HAL_Delay(5);
		     }
       while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_RESET);
				 timer = 20000;
				 if(address1 == address)
				 {
					  lcd_clear();
					  sprintf (buffer, "No new value");
	          lcd_put_cur(0,0);
	          lcd_send_string(buffer);
				 }	 
         else
         {
					 address1 = address1 + 8;
					 Press_DOWN(address1);
         }
			}
	 if(timer == 0)
	 { 
		 break; 
	 }
	 
	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0)==GPIO_PIN_RESET && oie == 0)
	 {
		 Task_Storage();
	 }
	 
 }
}