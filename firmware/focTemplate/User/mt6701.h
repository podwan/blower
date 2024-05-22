
#ifndef MT6701_H
#define MT6701_H

#include "userMain.h"

#define MT6701_CS_Enable GPIOA->BSRR = (uint32_t)GPIO_PIN_4 << 16U

#define MT6701_CS_Disable GPIOA->BSRR = GPIO_PIN_4

uint16_t MT6701_GetRawData(void);
float MT6701_GetRawAngle(void);

#endif