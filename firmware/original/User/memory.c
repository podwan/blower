
#include "memory.h"
// Memory memory;

// bool memorize(Memory *memory)
// {
// 	MEMORY_ERASE(0);

// 	if (MEMORY_WRITE_BYTES(PAGE, START_ADDRESS + i, memory, sizeof memory) == 0)
// 		return 0;
// 	else
// 		return 1;
// }

void memorize(uint add, char *p, uchar length)
{
	unsigned char i;
	for (i = 0; i < length; i++)
	{
		//MEMORIZE_BYTE(add + i, *(p + i));
	}
}

// bool isRemembered()
// {
// 	// 如果需要判断掉电时间
// 	xdata unsigned char cnt = 0;
// 	xdata unsigned int max = 0, min = 0xFFFF, sum = 0;

// 	while (++cnt <= 10)
// 	{
// 		unsigned int value = 0;

// 		value = ADC_SAMPLE_START(MEMORY_ADC_CHN);

// 		if (cnt >= 5)
// 		{
// 			if (min > value)
// 				min = value;
// 			if (max < value)
// 				max = value;
// 			sum += value;
// 		}

// 		if (cnt == 10)
// 		{

// 			sum -= (max + min);

// 			value = sum >> 2;

// 			UNSET_ADC;

// #if DEBUG_MEMORY
// 			stuff = value;
// #endif

// 			if (value >= REMEMBER_THRESHOLD) // how long have been out of power
// 				return 1;
// 			else
// 				return 0;
// 		}
// 	}
// }

// 上电读取
void recall(Memory *memory)
{
	// 如果无需判断掉电时间则直接使用以下部分
	unsigned char i;
	char memoryBuf[sizeof(Memory)];

	for (i = 0; i < sizeof(Memory); i++)
	{
		//memoryBuf[i] = RECALL_BYTE(START_ADDRESS + i);
	}

	*memory = *(Memory *)memoryBuf;
}

// CMS 51core
/*
	write memory data from address
*/
// void memorize(unsigned int addr, char *p, unsigned char length)
// {
// 	unsigned char i;
// 	FLASH_UnLock();
// 	FLASH_Erase(FLASH_DATA, 0);
// 	for (i = 0; i < length; i++)
// 	{
// 		MEMORIZE_BYTE(addr + i, *(p + i));
// 	}
// 	FLASH_Lock();
// }

// /*
// function: read memory
// para1: memory address
// para2: memory pointer
// return void
// */
// void recall(unsigned int addr, char *p, unsigned char length)
// {

// 	unsigned char i;
// 	FLASH_UnLock();
// 	for (i = 0; i < length; i++)
// 	{
// 		*(p + i) = RECALL_BYTE(addr + i);
// 	}
// 	FLASH_Lock();
// }
