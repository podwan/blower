#ifndef __LED_H
#define __LED_H

#include "userMain.h"

#define LED1_ON (HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET))
#define LED1_OFF (HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET))

#define LED2_ON (HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET))
#define LED2_OFF (HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET))

extern bool led1On, led2On;

void LED_drive(void);

#endif
