

#include "userMain.h"
#include "userTimer.h"
// #include "app.h"
// #include "beeper.h"
// #include "sensor.h"
// #include "key.h"
static bool powerLost;
void userMain(void)
{
	static uchar _5msCnt, _30msCnt, _20msCnt, _100msCnt, _250msCnt;
	static uint _500msCnt;
#if NEED_POWER_OFF_MEMORY
#include "memory.h"
	static bool memorized, recalled;
	if (!recalled)
	{
		recalled = 1;
		recall();
	}
	if (powerLost && !memorized)
	{
		memorize();
		memorized = 1;
	}
#endif

	if (getOneMsFlag())
	{
		// if (_10ms)
		// {
		
		// 	_10ms = 0;
		// 	display();
		// }

		// if (_20ms)
		// {
		// 	_20ms = 0;
		// 	beepPolling();
		// }
	
		// if (_5ms)
		// {
		// 	_5ms = 0;
		// 	keyScan();
		// }

		// if (_30ms)
		// {
		// 	_30ms = 0;
		// 	sensoring();
		// }

		// if (_100ms)
		// {
		// 	_100ms = 0;
		// 	appRunning();
		// }
	}
}
void delay(uint t)
{
	// uint i;
	// for (i = 0; i < t; i++)
	// {
	// 	asm("nop");
	// }
}
void setPowerLost()
{
	powerLost = 1;
}