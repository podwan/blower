#ifndef __KEY_H
#define __KEY_H

#include "userMain.h"

#define SW_PORT GPIOC

#define SW1_PIN GPIO_PIN_10
#define SW2_PIN GPIO_PIN_11
#define SW3_PIN GPIO_PIN_13

#define KEY0_LONG_CNT 180
#define KEY1_LONG_CNT 300
#define KEY2_LONG_CNT 300
#define KEY3_LONG_CNT 1
#define KEY4_LONG_CNT 850

#define CONTINUOUS_INTEVAL 40

#define CONTINUOUS_TRIG_CNT 100

#define KEY_NUM 4

#define K(i) (uint)(1 << (i - 1))

typedef enum
{
    NO_TRIG,
    TRIG_SHORT,
    TRIG_LONG,
} TrigType;

typedef enum
{
    SHORT,
    LONG_WITH_SHORT,
    CONTINUOUS,
    LONG
} KeyType;

typedef struct
{
    KeyType keyType;
    uint trigCnt;
    TrigType trigType;
    TrigType preKeyValue;
} KeyStruct;
void getKeyState(KeyState *keyState);
void keyScan();
#endif
