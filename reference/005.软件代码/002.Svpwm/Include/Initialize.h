/**************************************************************************************************
* �ŷ�ʵս����
* @project Svpwm
* @file    Initialize.h
* @author  �ŷ�ʵս�����Ŷ�
* @date    2024/03/28
* @version V100
* @Copyright  �������Ȩ�ŷ�ʵս��������
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\UserParams.h"

void Initialize(void);
static void delay(unsigned int time);

static void SysClockInit(void);
static void GpioInit(void);
static void PwmInit(void);
static void CompInit(void);
static void OpAmpInit(void);
static void AdcInit(void);
static void DacInit(void);
static void CORDICInit(void);
static void Timer1Init(void);
static void NvicInit(void);

/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *****END OF FILE****/
