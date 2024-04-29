#ifndef __USERMAIN_H
#define __USERMAIN_H

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

#include <stdio.h>
#include <string.h>
#include "stm32g4xx_hal.h"
#include "tim.h"

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

typedef struct
{
    signed short int X;
    signed short int Y;
    signed short int Z;
    unsigned short int sector;
    unsigned short int percentMax;
    unsigned short int percent;
    signed short int eAngle;
    unsigned short int TaOut;
    unsigned short int TbOut;
    unsigned short int TcOut;
    unsigned short int CCR1;
    unsigned short int CCR2;
    unsigned short int CCR3;
    void (*setPwm)(unsigned short int, unsigned short int, unsigned short int);
} SvPwm;

typedef enum
{
    false,
    true,
} bool;

typedef enum
{
    POWER_ON,
    POWER_OFF,
    STANDBY,
    PREHEAT,
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
    ONnOFF_SHORT,
    ONnOFF_LONG,
    ONE_CUP_SHORT,
    TWO_CUP_SHORT,
    ONE_CUP_LONG,
    TWO_CUP_LONG,
    STEAM_LONG,
    STEAM_SHORT,
    RESET_WORKED_TIMES_KEY,
    RESET_COFFEE_TIME_KEY,
    MENU_SHORT,
    TEST_KEY,
    RESET_KEY,
    VERSION_KEY
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
    unsigned char index;
    unsigned char buf[MAX_LEN];
    unsigned char len;
    unsigned char toProcessData;
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
void delay(uint t);
#endif
