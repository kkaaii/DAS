/*
** Rule #1: The value of last element is 0, which indicates to adjust blink rate.
** Rule #2: The sum of all elements in the array is 1000 (milliseconds).
** Rule #3: Meet the 45-55% duty cycle requirement.
** Rule #4: The value of each element is multiple of 10 (milliseconds).
*/
static const uint32 awPowerOn[] = {500, 500, 0}; /* 1 Hz */
static const uint32 awNonMedia[] = {250, 250, 250, 250, 0};	/* 2 Hz */
static const uint32 awLowSpeed[] = {200, 200, 200, 200, 200, 0};	/* 2.5 Hz */
static const uint32 awMedSpeed[] = {160, 170, 160, 170, 170, 170, 0};	/* 3 Hz */
static const uint32 awHighSpeed[]= {120, 130, 120, 130, 120, 130, 120, 130, 0};	/* 4 Hz */

static const uint32 *pwBlinkInterval = 0;
static uint32 wNonMediaCommands = 0;
static uint32 gwIoRate = 0;

void DAS_SetNonMedia(uint wCount)
{
	wNonMediaCommands = wCount;
}

void DAS_SetIoRate(uint32 wIoRate)
{
	gwIoRate = wIoRate;
}

static uint32 DAS_GetIoRate(void)
{
	return gwIoRate;
}

static Bool DAS_SelectBlinkRate(void)
{
	uint32 wIoRate = DAS_GetIoRate();
	if (0 == wIoRate) {
		if (0 == wNonMediaCommands) {
			return FALSE;
		}
		pwBlinkInterval = &awNonMedia[0];
	} else if (wIoRate < 200) {
		pwBlinkInterval = &awLowSpeed[0];
	} else if (wIoRate < 400) {
		pwBlinkInterval = &awMedSpeed[0];
	} else {
		pwBlinkInterval = &awHighSpeed[0];
	}

	wNonMediaCommands = 0;
	gwIoRate = 0;
	return TRUE;
}


static void DAS_TimerHandler(void)
{
	uint32 wBlinkInterval;
	if (0 == *pwBlinkInterval) {
		if (!DAS_SelectBlinkRate()) {
			LED_TurnOff();
			wBlinkInterval = 1000;
		} else {
			LED_TurnOn();
			wBlinkInterval = *pwBlinkInterval++;
		}
	} else {
		LED_Switch();
		wBlinkInterval = *pwBlinkInterval++;
	}

	Timer_Set(wBlinkInterval, DAS_TimerHandler);
}

void DAS_Init(void)
{
	pwBlinkInterval = &awPowerOn[0];
	LED_TurnOn();
	Timer_Set(*pwBlinkInterval++, DAS_TimerHandler);
}

