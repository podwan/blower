/**************************************************************************************************
* 张飞实战电子
* @project PLL_FOC
* @file    Main.h
* @author  张飞实战电子团队
* @date    2024/03/28
* @version V100
* @Copyright  软件著作权张飞实战电子所有
**************************************************************************************************/
#include "..\Include\stm32g431.h"
#include "..\Include\Define.h"

int Main(void);
void ADC1_2_IRQHandler(void);

static void SysTimeCount(void);

extern void Initialize(void);

extern void LedApp(void);
extern void KeyApp(void);
extern void SwitchApp(void);
extern void MotorApp(void);
extern void HeatApp(void);
extern void ProtectApp(void);

extern void CoreMachine(void);

extern void ScanfHeatTrigger(void);

extern void AdcSample(void);

extern void AdcFilter(void);

System_TypeDef tSystem;

extern Led_TypeDef tLed;
extern Switch_TypeDef tSwitch;
extern Key_TypeDef tKey;
extern Heat_TypeDef tHeat;
extern Motor_TypeDef tMotor;
extern Protect_TypeDef tProtect;
/************************ (C) COPYRIGHT Zhang Fei Shi Zhan Dian Zi *******************************/
