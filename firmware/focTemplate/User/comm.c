
#include "comm.h"
#include "mt6701.h"
#include "pid.h"
#include "app.h"
// 串口采用DMA 空闲中断模式，参考keysking@bilibili
char txBuffer[USART_BUFFER_SIZE];
char rxBuffer[USART_BUFFER_SIZE];
bool toProcessData;
uint8_t aRxBuffer;
float comm1, comm2, comm3, comm4, comm5, comm6, comm7, comm8, comm9, comm10, comm11;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart == &huart3)
  {
    // HAL_UART_Transmit_DMA(&huart3, rxBuffer, Size);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, rxBuffer, sizeof(rxBuffer));
    toProcessData = 1;
  }
}

// DMA模式
void FOC_log(const char *format, ...)
{

  // uint32_t length;
  // va_list args;

  // va_start(args, format);
  // length = vsnprintf((char *)txBuffer, sizeof(txBuffer), (char *)format, args);
  // va_end(args);
  // HAL_UART_Transmit_DMA(&huart3, (const char *)txBuffer, length);

  va_list args;           // 定义参数列表变量
  va_start(args, format); // 从format位置开始接收参数表，放在arg里面

  char strBuf[256];               // 定义输出的字符串
  vsprintf(strBuf, format, args); // 使用vsprintf将格式化的数据写入缓冲区
  va_end(args);                   // 结束可变参数的使用

  // 等待上次的数据发送完成，避免新的数据覆盖正在传输的数据，导致混乱
  while (HAL_UART_GetState(&huart3) == HAL_UART_STATE_BUSY_TX)
  {
    // Wait for DMA transfer to complete
  }
  HAL_UART_Transmit(&huart3, (uint8_t *)strBuf, strlen(strBuf), 1000);
}
void t_log(const char *s)
{
  strcpy(txBuffer, s);

  HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
}

// void _dbg_printf(const char *format, ...)
// {
//   uint32_t length;
//   va_list args;

//   va_start(args, format);
//   length = vsnprintf((char *)txBuffer, sizeof(txBuffer), (char *)format, args);
//   va_end(args);
//   HAL_UART_Transmit_DMA(&huart3, (const char *)txBuffer, length);
// }

void printLog()
{

#if SHOW_WAVE == 0
  txDataProcess();
  HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
#endif
}

void commander_run(BldcMotor *motor)
{
  if (toProcessData == 1)
  {
    // memset(txBuffer, '\0', sizeof(txBuffer));

    switch (rxBuffer[0])
    {
    case 'H':
      // sprintf(sndBuff, "Hello World!\r\n");
      // HAL_UART_Transmit_DMA(&huart3, (uint8_t *)sndBuff, sizeof(sndBuff));
      sprintf(txBuffer, "Hello World!\r\n");
      HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
      break;
    case 'T': // T6.28

      motor->target = atof((const char *)(rxBuffer + 1));
      sprintf(txBuffer, "Target=%.2f\r\n", motor->target);
      HAL_UART_Transmit_DMA(&huart3, (uint8_t *)txBuffer, sizeof(txBuffer));
      // printf("%s", sndBuff);
      // HAL_UART_Transmit_DMA(&huart3, (uint8_t *)sndBuff, sizeof(sndBuff));
      break;
      // case 'P': // P0.5
      //   bldcMotor.pidVelocity.P = atof((const char *)( rxBuffer + 1));
      //   sprintf(sndBuff, "P=%.2f\r\n", bldcMotor.pidVelocity.P);
      //   printf("%s", sndBuff);
      //   break;
      // case 'I': // I0.2
      //   bldcMotor.pidVelocity.I = atof((const char *)( rxBuffer + 1));
      //   sprintf(sndBuff, "I=%.2f\r\n", bldcMotor.pidVelocity.I);
      //   printf("%s", sndBuff);
      //   break;
      // case 'V': // V
      //   sprintf(sndBuff, "Vel=%.2f\r\n", shaftVelocity);
      //   printf("%s", sndBuff);
      //   break;
      // case 'A': // A
      //   sprintf(sndBuff, "Ang=%.2f\r\n", shaftAngle);
      //   printf("%s", sndBuff);
      //   break;
    }
    toProcessData = 0;
  }
}
