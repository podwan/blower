/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Flash.c
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\Flash.h"

/**************************************************************************************************
*解锁
**************************************************************************************************/
static void Flash_unlock(void)
{
    FLASH -> KEYR = 0x45670123;
    FLASH -> KEYR = 0xcdef89ab;
}
/**************************************************************************************************
*上锁
**************************************************************************************************/
static void Flash_lock(void)
{
	FLASH -> CR |= 0x80000000;
}
/**************************************************************************************************
*页擦除
*FLASH_BASE = 0x0800 0000
*FLASH_PageNum 
*FLASH_PageSize = 2048
*FLASH_ADDR = FLASH_BASE + FLASH_PageNum * FLASH_PageSize
*such as  FLASH_PageNum = 63
*FLASH_ADDR = 0x0800 0000 + 63 * 2048 = 0x0801 F800
**************************************************************************************************/
void PageErase(void)
{
	unsigned int Temp;
    
    do
    {
        Temp = FLASH -> SR;
    }while(Temp & 0x00010000);//Wait BSY = 0
    
    Flash_unlock();//Unlock
    FLASH -> SR |= 0x00000378;//Clear All Programming Error Flag
    
    FLASH -> CR &= 0xfffffc07;//PNB = 0
    FLASH -> CR |= 0x00000002;//PER = 1
    FLASH -> CR |= 0x000001f8;//PNB = 3F
    FLASH -> CR |= 0x00010000;//START = 1
    
    do
    {
        Temp = FLASH -> SR;
    }while(Temp & 0x00010000);//Wait BSY = 0
    
    FLASH -> CR &= 0xfffffffd;//PER = 0
    Flash_lock();//lock
}
/**************************************************************************************************
*写双字
**************************************************************************************************/
void FLASH_write(unsigned int Addr,unsigned long long data)
{
	unsigned int Temp;
    
    do
    {
        Temp = FLASH -> SR;
    }while(Temp & 0x00010000); //Wait BSY = 0
    
    Flash_unlock(); //Unlock
    FLASH -> CR |= 0x00000001; //PG = 1
    *(unsigned int*)Addr = data;
    *(unsigned int*)(Addr + 4u) = (unsigned int)(data>>32);
    
    do
    {
        Temp = FLASH -> SR;
    }while(Temp & 0x00010000); //Wait BSY = 0
    
    FLASH -> CR &= 0xfffffffe; //PG = 0;
    Flash_lock(); //Lock
}
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
