/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Initialize.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
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

extern void LedInitialize(void);
extern void KeyInitialize(void);
extern void SwitchInitialize(void);
extern void MotorInitialize(void);
extern void HeatInitialize(void);
extern void ProtectInitialize(void);
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *****END OF FILE****/
