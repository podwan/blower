
#include "userTimer.h"
#include "app.h"

#if NEED_POWER_OFF_MEMORY
#include "memory.h"
#endif

static void poweringOn();
static void standingby();
static void setting();
static void working();
static void testing();
static void faulting();
static DevState devState;
static bool _1s;
// static WorkMode workMode;
uint showStuff;
#if KEY_ENABLE
#include "key.h"
static KeyState keyState;
#endif

#if DISPLAY_ENABLE
#include "display.h"
static void displayDataUpdate();
static Byte displayDataBuf[NUM_OF_COM];
#endif

#if NEED_COMMUNICATION
#include "comm.h"
static uchar commErrCnt;
static void uartRxProcess();
static void uartTxProcess();
#endif
#if WITH_NTC
#include "sensor.h"
static uint ntcTemp;
static uchar ntcErr, errNo;
#endif
/*
deal per 100ms
*/
void appInit()
{
}

void appRunning()
{

#if NEED_POWER_OFF_MEMORY
    if (devState != POWER_ON)
    {
        memory.firstByte = 'K';
        memory.lastByte = 'X';
    }
#endif
#if KEY_ENABLE
    getKeyState(&keyState);
#endif

#if NEED_COMMUNICATION
    uartRxProcess();
#endif

#if DISPLAY_ENABLE
    memset(displayDataBuf, 0, NUM_OF_COM * sizeof(Byte));
#endif

#if WITH_NTC
    ntcErr = getTemp(&ntcTemp);
    if (devState != FAULT && devState != POWER_ON)
    {
        if (ntcErr != 0)
        {
            FAULT_INIT;
            errNo = ntcErr;
        }
    }
#endif

    _1s = getOneSecFlag();

    switch (devState)
    {
    case POWER_ON:
        poweringOn();
        break;

    case STANDBY:
        standingby();
        break;

    case SET:
        setting();
        break;

    case WORK:
        working();
        break;

    case TEST:
        testing();
        break;

    case FAULT:
        faulting();
        break;
    }
#if DISPLAY_ENABLE
    displayDataUpdate();
#endif

#if NEED_COMMUNICATION
    uartTxProcess();
#endif
    if (_1s)
    {

#if NEED_COMMUNICATION && WITHOUT_POWER_BOARD == 0
        if (commErrCnt < 10)
            ++commErrCnt;
        else if (errNo == 0)
        {
            errNo = 3;
            FAULT_INIT;
        }
#endif
        // beepOnce();
        _1s = 0;
    }
}

#if NEED_COMMUNICATION

static void uartRxProcess()
{
    if (rxUart.toProcessData)
    {

        if (rxUart.buf[0] == 'X' && rxUart.buf[rxUart.len - 1] == 'K')
        {
            commErrCnt = 0;
        }

        rxUart.len = 0;
        rxUart.toProcessData = 0;
    }
}
static void uartTxProcess()
{
    sprintf(sendStuff, "K%d%dX\n", (int)devState, (int)workMode);
}
#endif

#if DISPLAY_ENABLE
static void displayDataUpdate()
{
#if NEED_SEG_REMAP
    char i;
    for (i = 0; i < NUM_OF_COM; i++)
    {
        if (i == 0) // 数字部分
        {
            char seg = 0;

            if (displayDataBuf[i].bits.b0)
                SEG_REMAP(5); //
            if (displayDataBuf[i].bits.b1)
                SEG_REMAP(6); //
            if (displayDataBuf[i].bits.b2)
                SEG_REMAP(3); //
            if (displayDataBuf[i].bits.b3)
                SEG_REMAP(1); //
            if (displayDataBuf[i].bits.b4)
                SEG_REMAP(0); //
            if (displayDataBuf[i].bits.b5)
                SEG_REMAP(7);
            if (displayDataBuf[i].bits.b6)
                SEG_REMAP(4); //
            if (displayDataBuf[i].bits.b7)
                SEG_REMAP(2); //

            displayDataBuf[i].byte = seg;
        }
    }
#endif
    memcpy(displayData, displayDataBuf, NUM_OF_COM * sizeof(Byte));
}
#endif
#if DEBUG_DISPLAY
uchar i;
#endif
static void poweringOn()
{

#if DEBUG_DISPLAY
    if (_1s)
    {
#if DEBUG_COM
        if (++i == NUM_OF_COM)
        {
            i = 0;
        }
#elif DEBUG_SEG
        if (++i == 8)
        {
            i = 0;
        }

#endif
    }
#if DEBUG_SEG
    displayDataBuf[0].byte = 1 << i;
#elif DEBUG_COM
    displayDataBuf[i].byte = 0xFF;
#endif
    // D1 = DIGITS[i];
#elif DEBUG_KEY
    // D1 = DIGITS[keys_flag / 10000000];
    // D2 = DIGITS[keys_flag % 10000000 / 1000000];
    // D3 = DIGITS[keys_flag % 1000000 / 100000];
    // D4 = DIGITS[keys_flag % 100000 / 10000];
    D1 = DIGITS[KeyFlag % 10000 / 1000];
    D2 = DIGITS[KeyFlag % 1000 / 100];
    D3 = DIGITS[KeyFlag % 100 / 10];
    D4 = DIGITS[KeyFlag % 10];
#elif DEBUG_TEMP || DEBUG_MEMORY
    D1 = DIGITS[showStuff % 10000 / 1000];
    D2 = DIGITS[showStuff % 1000 / 100];
    D3 = DIGITS[showStuff % 100 / 10];
    D4 = DIGITS[showStuff % 10];
#else

    static unsigned char cnt;
    // static uchar i;
    // for (i = 0; i < NUM_OF_COM; i++)
    // {
    //     displayDataBuf[i].byte = 0xFF;
    // }

    if (++cnt >= 10)
    {
#if NEED_POWER_OFF_MEMORY
        recall();

        if (memory.firstByte == 'K' && memory.lastByte == 'X')
        {
            if (memory.devState == WORK)
            {
                // devState = memory.devState;
                // workMode = memory.workMode;
                // workTime = memory.workTime;
                // workTemp = memory.workTemp;
            }
            else
                STANDBY_INIT;
        }
        else
            STANDBY_INIT;
#else
        STANDBY_INIT;
#endif
    }

#endif
}

static void standingby()
{
}
static void setting()
{
}
static void working()
{
}

static void testing()
{
}

static void faulting()
{
}
