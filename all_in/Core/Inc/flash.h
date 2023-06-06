#include<stdint.h>
#include<string.h>
#define slotTime 4

void Flash_Erase(uint32_t address);

extern void Flash_Write_Array(uint32_t address, uint8_t *arr);
extern void Flash_Read_Array(uint32_t address, uint8_t *arr);