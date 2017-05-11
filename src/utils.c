/*
 * utils.c
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */
#include <utils.h>


void SysTick_Handler (void)
{
	tick_millis++;
}

// return the system clock as microseconds
uint32_t micros (void)
{
   return tick_millis * 1000 + 1000 - SysTick->VAL / 72;
}

// return the system clock as milliseconds
u32 millis (void)
{
   return tick_millis;
}

void delay_ms(u32 nTime)
{
	u32 curTime = tick_millis;
	while((nTime-(tick_millis-curTime)) > 0);
}

void delay_us(u32 nTime)
{
	while(nTime--)
	{
		u8 cycles = 16;
		while(cycles--)
		{
			asm("NOP");
		}
	}
}

void utils_systick_init (void)
{
   RCC_ClocksTypeDef RCC_Clocks;
   RCC_GetClocksFreq (&RCC_Clocks);
   (void) SysTick_Config (RCC_Clocks.HCLK_Frequency / 1000);
   tick_millis = 0;
}



