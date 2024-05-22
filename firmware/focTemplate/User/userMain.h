#ifndef __USERMAIN_H
#define __USERMAIN_H

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "stm32g4xx_hal.h"
#include "tim.h"
#include "adc.h"
#include "usart.h"
#include "spi.h"

#define TOUCH_KEY 0
#define FEED_WATCH_DOG 0
#define TOUCH_KEY_SCAN 0

#define USE_UART 0
#define PRINT_LOG 0
#define SPEED_UP 0
#define DISPLAY_TEMP 0
#define WITHOUT_POWER_BOARD 0
#define POWER_ADJUST 0
#define USE_ZERO 0
#define DEBUG_HEAT 0
#define DEBUGGING 0
#define SHOW_PWMDUTY 0
#define DEBUG_MEMORY 0
#define SIMU 0
#define DEBUG_TEMP 0
#define DEBUG_DISPLAY 0
#define DEBUG_KEY 0
#define MAX_LEN 20
#define SHOW_WAVE 0



/*===========================================================================*/

/*===========================================================================*/


/*===========================================================================*/

/*===========================================================================*/

/*===========================================================================*/
typedef enum
{
    false,
    true,
} bool;

typedef enum
{
    STANDBY,
    WORK,
    TEST,
    FAULT,
    CLEAN,
    VERSION
} DevState;

typedef enum
{
    ONE_CUP,
    TWO_CUP,
    STEAM,
    HOT_WATER
} WorkMode;

typedef enum
{
    VALVE_ON,
    TEMP_HIGH,
    ZERO_ERR,
    NTC_ERR
} FaultType;

typedef enum
{
    NONE_KEY,
    USER1_SHORT,
    USER2_SHORT,
    USER3_SHORT,
} KeyState;

typedef union
{
    unsigned int bytes;
    struct
    {
        unsigned int b0 : 1;
        unsigned int b1 : 1;
        unsigned int b2 : 1;
        unsigned int b3 : 1;
        unsigned int b4 : 1;
        unsigned int b5 : 1;
        unsigned int b6 : 1;
        unsigned int b7 : 1;
        unsigned int b8 : 1;
        unsigned int b9 : 1;
        unsigned int b10 : 1;
        unsigned int b11 : 1;
        unsigned int b12 : 1;
        unsigned int b13 : 1;
        unsigned int b14 : 1;
        unsigned int b15 : 1;
    } bits;
} TwoBytes;

typedef union
{
    unsigned char byte;
    struct
    {
        unsigned char b0 : 1;
        unsigned char b1 : 1;
        unsigned char b2 : 1;
        unsigned char b3 : 1;
        unsigned char b4 : 1;
        unsigned char b5 : 1;
        unsigned char b6 : 1;
        unsigned char b7 : 1;
    } bits;
} Byte;

typedef enum
{
    STILL,
    CLOCKWISE,
    ANTI_CLOCKWISE,
} EncoderState;

typedef struct
{
    uint16_t index;
    char buf[MAX_LEN];
    uint16_t len;
    bool toProcessData;
} Uart;

typedef struct
{
    unsigned char firstByte;

    unsigned char lastByte;
} Memory;

#define LongToBin(n)         \
    (                        \
        ((n >> 21) & 0x80) | \
        ((n >> 18) & 0x40) | \
        ((n >> 15) & 0x20) | \
        ((n >> 12) & 0x10) | \
        ((n >> 9) & 0x08) |  \
        ((n >> 6) & 0x04) |  \
        ((n >> 3) & 0x02) |  \
        ((n) & 0x01))

#define Bin(n) LongToBin(0x##n##l) // write binary charactor set,exsample : Bin(11111111) = 0xff
#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

void userMain(void);
void setPowerLost();
bool getPowerLost();
float map(float x, float in_min, float in_max, float out_min, float out_max);
#endif
