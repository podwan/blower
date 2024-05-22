

#include "userMain.h"
#include "userTimer.h"
#include "bldcMotor.h"
#include "math_utils.h"
#include "bldcMotor.h"
#include "voltage.h"
#include "comm.h"
#include "app.h"
#include "key.h"

#define PHASE_SHIFT_ANGLE (float)(120.0f / 360.0f * 2.0f * PI)

extern DMA_HandleTypeDef hdma_usart3_tx;

uint16_t DAC_temp = 0;

float Vbus, Ia, Ib, Ic;
uint8_t Motor_state = 0;
uint16_t IA_Offset, IB_Offset, IC_Offset;
uint16_t adc1_in1, adc1_in2, adc1_in3, Vpoten, adc_vbus;
uint8_t ADC_offset = 0;

uint8_t RxData[8] = {NULL};
uint8_t TxData[8] = {NULL};

float HallTemp = 0;
float HallThetaAdd = 0;
float HallTheta = 0;
float HallSpeed = 0;
uint8_t HallReadTemp = 0;
//static bool powerLost;
void userMain(void)
{

	if (get5MsFlag())
	{
		keyScan();
	}

	if (get100MsFlag())
	{
		appRunning();
	}
#if SHOW_WAVE == 0 //&& COMMAMNDER == 0
	// if (get500MsFlag())
	if (getOneSecFlag())
	{
		printLog();
	}
#endif
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int fputc(int ch, FILE *f)
{
	while ((USART3->ISR & 0X40) == 0)
		;
	USART3->TDR = (uint8_t)ch;
	return ch;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	/* Prevent unused argument(s) compilation warning */
	// UNUSED(htim);
	// if (htim == &htim4)
	// {
	// 	HallTemp = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
	// 	;
	// 	HallThetaAdd = (PI / 3) / (HallTemp / 1000000) / 10000;
	// 	HallSpeed = (PI / 3) / (HallTemp / 1000000) * 30 / PI;
	// 	HallReadTemp = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
	// 	HallReadTemp |= HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7) << 1;
	// 	HallReadTemp |= HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) << 2;
	// 	if (HallReadTemp == 0x05)
	// 	{
	// 		HallTheta = 0.0f + PHASE_SHIFT_ANGLE;
	// 	}
	// 	else if (HallReadTemp == 0x04)
	// 	{
	// 		HallTheta = (PI / 3.0f) + PHASE_SHIFT_ANGLE;
	// 	}
	// 	else if (HallReadTemp == 0x06)
	// 	{
	// 		HallTheta = (PI * 2.0f / 3.0f) + PHASE_SHIFT_ANGLE;
	// 	}
	// 	else if (HallReadTemp == 0x02)
	// 	{
	// 		HallTheta = PI + PHASE_SHIFT_ANGLE;
	// 	}
	// 	else if (HallReadTemp == 0x03)
	// 	{
	// 		HallTheta = (PI * 4.0f / 3.0f) + PHASE_SHIFT_ANGLE;
	// 	}
	// 	else if (HallReadTemp == 0x01)
	// 	{
	// 		HallTheta = (PI * 5.0f / 3.0f) + PHASE_SHIFT_ANGLE;
	// 	}
	// 	if (HallTheta < 0.0f)
	// 	{
	// 		HallTheta += 2.0f * PI;
	// 	}
	// 	else if (HallTheta > (2.0f * PI))
	// 	{
	// 		HallTheta -= 2.0f * PI;
	// 	}
	// }

	/* NOTE : This function should not be modified, when the callback is needed,
			  the HAL_TIM_IC_CaptureCallback could be implemented in the user file
	 */
}
