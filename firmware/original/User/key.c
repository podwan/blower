
#include "key.h"


static bool switchClosed;
bool beepFlag; // long press first beep flag
static KeyStruct keyStruct[KEY_NUM];

// call per 5ms
void keyScan()
{

    // static TrigType preKeyValue;

    static bool keyInited;
    uint keyFlags;

    if (keyInited == 0)
    {
        uchar i;
        keyInited = 1;
        keyStruct[0].keyType = LONG;
        keyStruct[1].keyType = SHORT;
        for (i = 0; i < KEY_NUM; i++)
        {
            keyStruct[i].trigCnt = 0;
            keyStruct[i].preKeyValue = NO_TRIG;
        }
    }
    //keyFlags = TOUCH_KEY_FLAGS;

    if (keyFlags == 0)
    {
        uchar i;
        for (i = 0; i < KEY_NUM; i++)
        {
            if (keyStruct[i].keyType == LONG_WITH_SHORT && keyStruct[i].trigCnt > 0)
            {
                keyStruct[i].trigType = TRIG_SHORT;
            }
            keyStruct[i].trigCnt = 0;
            keyStruct[i].preKeyValue = NO_TRIG;
        }
    }

    if (keyStruct[0].preKeyValue == NO_TRIG)
    {
        if (keyFlags == (TK1 | TK3))
        {
            if (keyStruct[0].preKeyValue == NO_TRIG)
            {
                if (keyStruct[0].keyType == SHORT || keyStruct[0].keyType == CONTINUOUS)
                {
                    keyStruct[0].trigType = TRIG_SHORT;
                    keyStruct[0].preKeyValue = TRIG_SHORT;
                }
                else if (keyStruct[0].keyType == LONG_WITH_SHORT || keyStruct[0].keyType == LONG)
                {
                    if (++keyStruct[0].trigCnt >= KEY0_LONG_CNT)
                    {
                        keyStruct[0].trigCnt = 0;
                        keyStruct[0].trigType = TRIG_LONG;
                        keyStruct[0].preKeyValue = TRIG_LONG;
                    }
                }
            }
        }
    }
    else if (keyStruct[0].keyType == CONTINUOUS)
    {
        if (keyStruct[0].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[0].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[0].trigCnt = 0;
                keyStruct[0].trigType = TRIG_LONG; // long
                keyStruct[0].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[0].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[0].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[0].trigCnt = 0;
                keyStruct[0].trigType = keyStruct[1].preKeyValue;
            }
        }
    }

    if (keyStruct[1].preKeyValue == NO_TRIG)
    {
        if (keyFlags == TK1)
        {
            if (keyStruct[1].preKeyValue == NO_TRIG)
            {
                if (keyStruct[1].keyType == SHORT || keyStruct[1].keyType == CONTINUOUS)
                {
                    keyStruct[1].trigType = TRIG_SHORT;
                    keyStruct[1].preKeyValue = TRIG_SHORT;
                }
                else if (keyStruct[1].keyType == LONG_WITH_SHORT || keyStruct[1].keyType == LONG)
                {
                    if (++keyStruct[1].trigCnt >= KEY1_LONG_CNT)
                    {
                        keyStruct[1].trigCnt = 0;
                        keyStruct[1].trigType = TRIG_LONG;
                        keyStruct[1].preKeyValue = TRIG_LONG;
                    }
                }
            }
        }
    }
    else if (keyStruct[1].keyType == CONTINUOUS)
    {
        if (keyStruct[1].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[1].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[1].trigCnt = 0;
                keyStruct[1].trigType = TRIG_LONG; // long
                keyStruct[1].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[1].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[1].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[1].trigCnt = 0;
                keyStruct[1].trigType = keyStruct[1].preKeyValue;
            }
        }
    }

    if (keyStruct[2].preKeyValue == NO_TRIG)
    {
        if (keyFlags == TK2)
        {

            if (keyStruct[2].keyType == SHORT || keyStruct[2].keyType == CONTINUOUS)
            {
                keyStruct[2].trigType = TRIG_SHORT;
                keyStruct[2].preKeyValue = TRIG_SHORT;
            }
            else if (keyStruct[2].keyType == LONG_WITH_SHORT || keyStruct[2].keyType == LONG)
            {
                if (++keyStruct[2].trigCnt >= KEY2_LONG_CNT)
                {
                    keyStruct[2].trigCnt = 0;
                    keyStruct[2].trigType = TRIG_LONG;
                    keyStruct[2].preKeyValue = TRIG_LONG;
                }
            }
        }
    }
    else if (keyStruct[2].keyType == CONTINUOUS)
    {
        if (keyStruct[2].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[2].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[2].trigCnt = 0;
                keyStruct[2].trigType = TRIG_LONG; // long
                keyStruct[2].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[2].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[2].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[2].trigCnt = 0;
                keyStruct[2].trigType = keyStruct[2].preKeyValue;
            }
        }
    }

    if (keyStruct[3].preKeyValue == NO_TRIG)
    {
        if (keyFlags == TK3)
        {
            // beepOnce();
            if (keyStruct[3].keyType == SHORT || keyStruct[3].keyType == CONTINUOUS)
            {
                keyStruct[3].trigType = TRIG_SHORT;
                keyStruct[3].preKeyValue = TRIG_SHORT;
            }
            else if (keyStruct[3].keyType == LONG_WITH_SHORT || keyStruct[3].keyType == LONG)
            {
                if (++keyStruct[3].trigCnt >= KEY3_LONG_CNT)
                {
                    keyStruct[3].trigCnt = 0;
                    keyStruct[3].trigType = TRIG_LONG;
                    keyStruct[3].preKeyValue = TRIG_LONG;
                }
            }
        }
    }
    else if (keyStruct[3].keyType == CONTINUOUS)
    {
        if (keyStruct[3].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[3].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[3].trigCnt = 0;
                keyStruct[3].trigType = TRIG_LONG; // long
                keyStruct[3].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[3].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[3].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[3].trigCnt = 0;
                keyStruct[3].trigType = keyStruct[3].preKeyValue;
            }
        }
    }

    if (keyStruct[4].preKeyValue == NO_TRIG)
    {
        if (keyFlags == TK4)
        {

            if (keyStruct[4].keyType == SHORT || keyStruct[4].keyType == CONTINUOUS)
            {
                keyStruct[4].trigType = TRIG_SHORT;
                keyStruct[4].preKeyValue = TRIG_SHORT;
            }
            else if (keyStruct[4].keyType == LONG_WITH_SHORT || keyStruct[4].keyType == LONG)
            {
                if (++keyStruct[4].trigCnt >= KEY4_LONG_CNT)
                {
                    keyStruct[4].trigCnt = 0;
                    keyStruct[4].trigType = TRIG_LONG;
                    keyStruct[4].preKeyValue = TRIG_LONG;
                }
            }
        }
    }
    else if (keyStruct[4].keyType == CONTINUOUS)
    {
        if (keyStruct[4].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[4].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[4].trigCnt = 0;
                keyStruct[4].trigType = TRIG_LONG; // long
                keyStruct[4].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[4].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[4].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[4].trigCnt = 0;
                keyStruct[4].trigType = keyStruct[4].preKeyValue;
            }
        }
    }

    if (keyStruct[5].preKeyValue == NO_TRIG)
    {
        if (keyFlags == TK5)
        {
            // beepOnce();
            if (keyStruct[5].keyType == SHORT || keyStruct[5].keyType == CONTINUOUS)
            {
                keyStruct[5].trigType = TRIG_SHORT;
                keyStruct[5].preKeyValue = TRIG_SHORT;
            }
            else if (keyStruct[5].keyType == LONG_WITH_SHORT || keyStruct[5].keyType == LONG)
            {
                if (++keyStruct[5].trigCnt >= KEY5_LONG_CNT)
                {
                    keyStruct[5].trigCnt = 0;
                    keyStruct[5].trigType = TRIG_LONG;
                    keyStruct[5].preKeyValue = TRIG_LONG;
                }
            }
        }
    }
    else if (keyStruct[5].keyType == CONTINUOUS)
    {
        if (keyStruct[5].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[5].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[5].trigCnt = 0;
                keyStruct[5].trigType = TRIG_LONG; // long
                keyStruct[5].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[5].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[5].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[5].trigCnt = 0;
                keyStruct[5].trigType = keyStruct[5].preKeyValue;
            }
        }
    }

    if (keyStruct[6].preKeyValue == NO_TRIG)
    {
        if (keyFlags == TK6)
        {

            if (keyStruct[6].keyType == SHORT || keyStruct[6].keyType == CONTINUOUS)
            {
                keyStruct[6].trigType = TRIG_SHORT;
                keyStruct[6].preKeyValue = TRIG_SHORT;
            }
            else if (keyStruct[6].keyType == LONG_WITH_SHORT || keyStruct[6].keyType == LONG)
            {
                if (++keyStruct[6].trigCnt >= KEY6_LONG_CNT)
                {
                    keyStruct[6].trigCnt = 0;
                    keyStruct[6].trigType = TRIG_LONG;
                    keyStruct[6].preKeyValue = TRIG_LONG;
                }
            }
        }
    }

    // if (keyStruct[7].preKeyValue == NO_TRIG)
    // {
    //     if (keyFlags == KR1)
    //     {
    //         // beepOnce();
    //         if (keyStruct[7].keyType == SHORT || keyStruct[7].keyType == CONTINUOUS)
    //         {
    //             keyStruct[7].trigType = TRIG_SHORT;
    //             keyStruct[7].preKeyValue = TRIG_SHORT;
    //         }
    //         else if (keyStruct[7].keyType == LONG_WITH_SHORT || keyStruct[7].keyType == LONG)
    //         {
    //             if (++keyStruct[7].trigCnt >= KEY7_LONG_CNT)
    //             {
    //                 keyStruct[7].trigCnt = 0;
    //                 keyStruct[7].trigType = TRIG_LONG;
    //                 keyStruct[7].preKeyValue = TRIG_LONG;
    //             }
    //         }
    //     }
    // }
    // else if (keyStruct[7].keyType == CONTINUOUS)
    // {
    //     if (keyStruct[7].preKeyValue == TRIG_SHORT) // short key
    //     {
    //         if (++keyStruct[7].trigCnt >= CONTINUOUS_TRIG_CNT)
    //         {
    //             keyStruct[7].trigCnt = 0;
    //             keyStruct[7].trigType = TRIG_LONG; // long
    //             keyStruct[7].preKeyValue = TRIG_LONG;
    //         }
    //     }
    //     else if (keyStruct[7].preKeyValue == TRIG_LONG) // long key
    //     {
    //         if (++keyStruct[7].trigCnt >= CONTINUOUS_INTEVAL)
    //         {
    //             keyStruct[7].trigCnt = 0;
    //             keyStruct[7].trigType = keyStruct[7].preKeyValue;
    //         }
    //     }
    // }

    // if (keyStruct[8].preKeyValue == NO_TRIG)
    // {
    //     if (keyFlags == KR2)
    //     {

    //         if (keyStruct[8].keyType == SHORT || keyStruct[8].keyType == CONTINUOUS)
    //         {
    //             keyStruct[8].trigType = TRIG_SHORT;
    //             keyStruct[8].preKeyValue = TRIG_SHORT;
    //         }
    //         else if (keyStruct[8].keyType == LONG_WITH_SHORT || keyStruct[8].keyType == LONG)
    //         {
    //             if (++keyStruct[8].trigCnt >= KEY8_LONG_CNT)
    //             {
    //                 keyStruct[8].trigCnt = 0;
    //                 keyStruct[8].trigType = TRIG_LONG;
    //                 keyStruct[8].preKeyValue = TRIG_LONG;
    //             }
    //         }
    //     }
    // }

    // if (keyStruct[9].preKeyValue == NO_TRIG)
    // {
    //     if (keyFlags == KR3)
    //     {
    //         // beepOnce();
    //         if (keyStruct[9].keyType == SHORT || keyStruct[9].keyType == CONTINUOUS)
    //         {
    //             keyStruct[9].trigType = TRIG_SHORT;
    //             keyStruct[9].preKeyValue = TRIG_SHORT;
    //         }
    //         else if (keyStruct[9].keyType == LONG_WITH_SHORT)
    //         {
    //             if (++keyStruct[9].trigCnt >= KEY9_LONG_CNT)
    //             {
    //                 keyStruct[9].trigCnt = 0;
    //                 keyStruct[9].trigType = TRIG_LONG;
    //                 keyStruct[9].preKeyValue = TRIG_LONG;
    //             }
    //         }
    //     }
    // }

    // if (keyStruct[10].preKeyValue == NO_TRIG)
    // {
    //     if (keyFlags == KR4)
    //     {

    //         if (keyStruct[10].keyType == SHORT || keyStruct[10].keyType == CONTINUOUS)
    //         {
    //             keyStruct[10].trigType = TRIG_SHORT;
    //             keyStruct[10].preKeyValue = TRIG_SHORT;
    //         }
    //         else if (keyStruct[10].keyType == LONG_WITH_SHORT || keyStruct[10].keyType == LONG)
    //         {
    //             if (++keyStruct[10].trigCnt >= KEY10_LONG_CNT)
    //             {
    //                 keyStruct[10].trigCnt = 0;
    //                 keyStruct[10].trigType = TRIG_LONG;
    //                 keyStruct[10].preKeyValue = TRIG_LONG;
    //             }
    //         }
    //     }
    // }
    // else if (keyStruct[10].keyType == CONTINUOUS)
    // {
    //     if (keyStruct[10].preKeyValue == TRIG_SHORT) // short key
    //     {
    //         if (++keyStruct[10].trigCnt >= CONTINUOUS_TRIG_CNT)
    //         {
    //             keyStruct[10].trigCnt = 0;
    //             keyStruct[10].trigType = TRIG_LONG; // long
    //             keyStruct[10].preKeyValue = TRIG_LONG;
    //         }
    //     }
    //     else if (keyStruct[10].preKeyValue == TRIG_LONG) // long key
    //     {
    //         if (++keyStruct[10].trigCnt >= CONTINUOUS_INTEVAL)
    //         {
    //             keyStruct[10].trigCnt = 0;
    //             keyStruct[10].trigType = keyStruct[10].preKeyValue;
    //         }
    //     }
    // }

    // if (keyStruct[11].preKeyValue == NO_TRIG)
    // {
    //     if (keyFlags == KR5)
    //     {
    //         // beepOnce();
    //         if (keyStruct[11].keyType == SHORT || keyStruct[11].keyType == CONTINUOUS)
    //         {
    //             keyStruct[11].trigType = TRIG_SHORT;
    //             keyStruct[11].preKeyValue = TRIG_SHORT;
    //         }
    //         else if (keyStruct[11].keyType == LONG_WITH_SHORT || keyStruct[11].keyType == LONG)
    //         {
    //             if (++keyStruct[11].trigCnt >= KEY11_LONG_CNT)
    //             {
    //                 keyStruct[11].trigCnt = 0;
    //                 keyStruct[11].trigType = TRIG_LONG;
    //                 keyStruct[11].preKeyValue = TRIG_LONG;
    //             }
    //         }
    //     }
    // }
    // else if (keyStruct[11].keyType == CONTINUOUS)
    // {
    //     if (keyStruct[11].preKeyValue == TRIG_SHORT) // short key
    //     {
    //         if (++keyStruct[11].trigCnt >= CONTINUOUS_TRIG_CNT)
    //         {
    //             keyStruct[11].trigCnt = 0;
    //             keyStruct[11].trigType = TRIG_LONG; // long
    //             keyStruct[11].preKeyValue = TRIG_LONG;
    //         }
    //     }
    //     else if (keyStruct[11].preKeyValue == TRIG_LONG) // long key
    //     {
    //         if (++keyStruct[11].trigCnt >= CONTINUOUS_INTEVAL)
    //         {
    //             keyStruct[11].trigCnt = 0;
    //             keyStruct[11].trigType = keyStruct[11].preKeyValue;
    //         }
    //     }
    // }

    // if (keyStruct[12].preKeyValue == NO_TRIG)
    // {
    //     if (keyFlags == KR6)
    //     {

    //         if (keyStruct[12].keyType == SHORT || keyStruct[12].keyType == CONTINUOUS)
    //         {
    //             keyStruct[12].trigType = TRIG_SHORT;
    //             keyStruct[12].preKeyValue = TRIG_SHORT;
    //         }
    //         else if (keyStruct[12].keyType == LONG_WITH_SHORT || keyStruct[12].keyType == LONG)
    //         {
    //             if (++keyStruct[12].trigCnt >= KEY12_LONG_CNT)
    //             {
    //                 keyStruct[12].trigCnt = 0;
    //                 keyStruct[12].trigType = TRIG_LONG;
    //                 keyStruct[12].preKeyValue = TRIG_LONG;
    //             }
    //         }
    //     }
    // }
    // else if (keyStruct[12].keyType == CONTINUOUS)
    // {
    //     if (keyStruct[12].preKeyValue == TRIG_SHORT) // short key
    //     {
    //         if (++keyStruct[12].trigCnt >= CONTINUOUS_TRIG_CNT)
    //         {
    //             keyStruct[12].trigCnt = 0;
    //             keyStruct[12].trigType = TRIG_LONG; // long
    //             keyStruct[12].preKeyValue = TRIG_LONG;
    //         }
    //     }
    //     else if (keyStruct[12].preKeyValue == TRIG_LONG) // long key
    //     {
    //         if (++keyStruct[12].trigCnt >= CONTINUOUS_INTEVAL)
    //         {
    //             keyStruct[12].trigCnt = 0;
    //             keyStruct[12].trigType = keyStruct[12].preKeyValue;
    //         }
    //     }
    // }

    //     if (++key1edCnt >= LONG_PRESS_TRIG_CNT)
    //     {
    //         trigType = KEY1_LONG;
    //         preKeyValue = trigType;
    //     }
    // }
    // else if (preKeyValue == KEY1_LONG)
    // {
    //     if (++key1LongCnt > LONG_PRESS_INTEVAL)
    //     {
    //         key1LongCnt = 0;
    //         trigType = KEY1_LONG;
    //     }
    // }
    // {
    //     static unsigned char cnt;

    //     if (!switchClosed && SWITCH_CLOSE)
    //     {
    //         if (++cnt >= 5)
    //         {
    //             cnt = 0;
    //             switchClosed = 1;
    //         }
    //     }
    //     else if (switchClosed && SWITCH_OPEN)
    //     {
    //         if (++cnt >= 5)
    //         {
    //             cnt = 0;
    //             switchClosed = 0;
    //         }
    //     }
    //     else
    //         cnt = 0;
    // }

    // {
    //     static unsigned char cnt;

    //     if (!switch2Closed && SWITCH2_CLOSE)
    //     {
    //         if (++cnt >= 5)
    //         {
    //             cnt = 0;
    //             switch2Closed = 1;
    //         }
    //     }
    //     else if (switch2Closed && SWITCH2_OPEN)
    //     {
    //         if (++cnt >= 5)
    //         {
    //             cnt = 0;
    //             switch2Closed = 0;
    //         }
    //     }
    //     else
    //         cnt = 0;
    // }
}

/*
transfer physical key to logical key
 */
bool getSwitchClosed()
{
    return switchClosed;
}

void getKeyState(KeyState *keyState)
{
    uchar i;

    // if (keyStruct[8].trigType == TRIG_SHORT)
    //     *keyState = ONnOFF_SHORT;
    // else if (keyStruct[12].trigType == TRIG_SHORT)
    //     *keyState = MENU_SHORT;
    // else if (keyStruct[7].trigType == TRIG_SHORT)
    //     *keyState = PLUS_SHORT;
    // else if (keyStruct[7].trigType == TRIG_LONG)
    //     *keyState = PLUS_LONG;
    // else if (keyStruct[10].trigType == TRIG_SHORT)
    //     *keyState = MINUS_SHORT;
    // else if (keyStruct[10].trigType == TRIG_LONG)
    //     *keyState = MINUS_LONG;
    // else if (keyStruct[11].trigType == TRIG_SHORT)
    //     *keyState = TEMPnTIME_SHORT;
    // else if (keyStruct[6].trigType == TRIG_SHORT)
    //     *keyState = AIR_FRY_SHORT;
    // else if (keyStruct[5].trigType == TRIG_SHORT)
    //     *keyState = STEAM_BAKE_SHORT;
    // else if (keyStruct[4].trigType == TRIG_SHORT)
    //     *keyState = SMART_STEAM_SHORT;
    // else if (keyStruct[3].trigType == TRIG_SHORT)
    //     *keyState = STEAM_SHORT;
    // else
    *keyState = NONE_KEY;

    for (i = 0; i < KEY_NUM; i++)
    {
        keyStruct[i].trigType = NO_TRIG;
    }
}
