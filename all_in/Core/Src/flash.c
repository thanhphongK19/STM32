#include "flash.h"
#include "stm32f1xx.h"

void Flash_Erase(uint32_t address)  //xoa bo nho flash
{
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.Banks = 1;
	EraseInitStruct.NbPages =1;
	EraseInitStruct.PageAddress = address;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;	
	uint32_t pageerr;
	
	HAL_FLASHEx_Erase( &EraseInitStruct, &pageerr);
	HAL_FLASH_Lock();
	
}

void Flash_Write_Array(uint32_t address, uint8_t *arr) //luu gia tri flash
{
	
	HAL_FLASH_Unlock();
	uint16_t *pt = (uint16_t*)arr;  
	for(uint16_t i=0; i< slotTime ;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, address+2*i,*pt);
		pt++;
	}
	HAL_FLASH_Lock();
}
void Flash_Read_Array(uint32_t address, uint8_t *arr)  //doc gia tri tu flash
{
	uint16_t *pt = (uint16_t*)arr;
	for(uint16_t i=0; i<slotTime;i++)
	{	
		*pt = *(__IO uint16_t*) (address+2*i);
		pt++;
	};
}