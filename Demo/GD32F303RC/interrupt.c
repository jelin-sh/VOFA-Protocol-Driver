#include "gd32f30x.h"
#include "Vofa.h"
#include "arm_math.h"

extern volatile uint32_t delay_tick;
extern Vofa_HandleTypedef vofa1;

static volatile float testData[5] = {0};
volatile uint32_t sysTick;

void SysTick_Handler()
{
	sysTick++;
	if(delay_tick > 0)
	{
		delay_tick--;
	}	
}

void USART1_IRQHandler()
{
	if(usart_interrupt_flag_get(USART1,USART_INT_FLAG_RBNE))
	{
		Vofa_ReceiveData(&vofa1);
	}
}

void TIMER0_UP_IRQHandler()
{
	static float time = 0;	
	gpio_bit_set(GPIOA,GPIO_PIN_8);
	time += 0.0003f;
	timer_interrupt_flag_clear(TIMER0,TIMER_INT_FLAG_UP);
	testData[0] = arm_sin_f32(time * 2 * PI);
	testData[1] = arm_sin_f32(time * 2 * PI + 5);
	testData[2] = arm_sin_f32(time * 2 * PI - 5);
	testData[3] = arm_sin_f32(time * 4 * PI);
	testData[4] = 2 * arm_sin_f32(time * 4 * PI);
	Vofa_JustFloat(&vofa1,(float*)testData,5);
	gpio_bit_reset(GPIOA,GPIO_PIN_8);	
}
