#ifndef __KEY_H
#define __KEY_H

#include "userMain.h"

#define KEY0_LONG_CNT 1
#define KEY1_LONG_CNT 300
#define KEY2_LONG_CNT 300
#define KEY3_LONG_CNT 1
#define KEY4_LONG_CNT 0
#define KEY5_LONG_CNT 1
#define KEY6_LONG_CNT 0
#define KEY7_LONG_CNT 0
#define KEY8_LONG_CNT 1
#define KEY9_LONG_CNT 0
#define KEY10_LONG_CNT 0
#define KEY11_LONG_CNT 1
#define KEY12_LONG_CNT 0

#define FILTER_CNT 12

#define CONTINUOUS_INTEVAL 40

#define CONTINUOUS_TRIG_CNT 100

#define K(i) (KEY_FLAG_BYTES)(1 << i)

#define TK1 1    // 3
#define TK2 2    // 3
#define TK3 4    // 3
#define TK4 1   // 3
#define TK5 2   // 3
#define TK6 32  // 3
#define TK7 4   // 3


#define KEY_NUM 7 //

#define TOUCH_KEY_FLAGS 

typedef enum
{
    NO_TRIG,
    TRIG_SHORT,
    TRIG_LONG,
} TrigType;

typedef enum
{
    SHORT,           //
    LONG,            //
    LONG_WITH_SHORT, //
    CONTINUOUS,      //
} KeyType;

typedef struct
{
    KeyType keyType;
    uint trigCnt;
    TrigType trigType;
    TrigType preKeyValue;
} KeyStruct;

void keyScan();
void getKeyState(KeyState *keyState);
bool getSwitchClosed();

#endif
