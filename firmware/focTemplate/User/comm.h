#ifndef __COMM_H
#define __COMM_H

#include "userMain.h"
#include "bldcMotor.h"
#define UART_SEND_BYTE(STUFF) UART0_Send_Byte(STUFF)

#define USART_BUFFER_SIZE 100

void printLog(void);
void uartRcv(const char buf);
void commander_run(BldcMotor *motor);
void communicationLoop(void *argument);
void FOC_log(const char *format, ...);
void log_DMA_TX(const char *format, ...);
void t_log(const char *s);
void _dbg_printf(const char *format, ...);
extern float comm1, comm2, comm3, comm4, comm5, comm6, comm7, comm8, comm9, comm10, comm11;
extern char txBuffer[USART_BUFFER_SIZE];

extern uint8_t aRxBuffer;
extern char rxBuffer[USART_BUFFER_SIZE];
extern bool toProcessData;
#endif
