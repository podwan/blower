#include "mt6701.h"
#include "math_utils.h"
#include "time_utils.h"
// static unsigned int rotationCount, rotationCount_Last;

uint16_t MT6701_GetRawData(void)
{
    uint16_t rawData;
    uint16_t txData = 0xFFFF;
    uint16_t timeOut = 200;

    while (HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY)
    {
        if (timeOut-- == 0)
        {
            //   FOC_log("SPI state error!\r\n");
            return 0; // 在超时时直接返回，避免继续执行后续代码
        }
    }

    MT6701_CS_Enable;

    HAL_StatusTypeDef spiStatus = HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)&txData, (uint8_t *)&rawData, 1, HAL_MAX_DELAY);
    if (spiStatus != HAL_OK)
    {
        MT6701_CS_Disable;
        //  FOC_log("MT6701 read data error!\r\n");
        return 0; // 在SPI传输错误时直接返回，避免继续执行后续代码
    }

    MT6701_CS_Disable;

    return rawData >> 2; // 取高14位的角度数据
}

// 将传感器原始数据转化为弧度
float MT6701_GetRawAngle(void)
{
    uint16_t rawData = MT6701_GetRawData();
    return (float)rawData / 16384.0f * _2PI;
}
