#include "gd32f30x.h"

volatile uint32_t delay_tick;

void Delay_Init()
{
	SysTick_Config(SystemCoreClock/1000);
}

void Delay(uint16_t ms)
{
	delay_tick = ms;
	while(delay_tick);
}