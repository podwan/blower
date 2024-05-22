#include "led.h"

bool led1On, led2On;

void LED_drive()
{
    if (led1On)
        LED1_ON;
    else
        LED1_OFF;

    if (led2On)
        LED2_ON;
    else
        LED2_OFF;
}
