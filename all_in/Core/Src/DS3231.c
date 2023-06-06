 /* USER CODE BEGIN x */
#include  "DS3231.h"

extern I2C_HandleTypeDef hi2c1;
extern 	TIME time;

 
int bcdToDec(uint8_t val)
{
	uint8_t bin;
	bin=((val & 0xf0)>>4)*10 +(val & 0x0f);
  return (bin);
  //return (int)( (val/16*10) + (val%16) );
}


uint8_t decToBcd(int val)
{
  uint8_t y;
	y = (val/10) <<4;
	y = y | (val % 10);
	return (y);	
	//return (uint8_t)( (val/10*16) + (val%10) );
}


void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(day);
	set_time[4] = decToBcd(date);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
	//(para1:which i2c,para2:target add,para3:internal mem add,para4:mem add size,para5:p data,para6:size data,para7:time out)
}

void Get_Time (uint8_t *Get_Sec , uint8_t *Get_min ,uint8_t *Get_hour,uint8_t *Get_day ,uint8_t *Get_date,uint8_t *Get_month ,uint8_t *Get_year)
{                      //struct use here//
	
  uint8_t get_time[7];
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);
	//(para1:which i2c,para2:target add,para3:internal mem add,para4:mem add size,para5:p data,para6:size data,para7:time out)
	*Get_Sec = bcdToDec(get_time[0]);
	*Get_min= bcdToDec(get_time[1]);
	*Get_hour= bcdToDec(get_time[2]);
	*Get_day= bcdToDec(get_time[3]);
	*Get_date= bcdToDec(get_time[4]);
	*Get_month= bcdToDec(get_time[5]);
	*Get_year= bcdToDec(get_time[6]);
	
}  

/* USER CODE END x */