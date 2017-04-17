/*
 * utils.c
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */
#include <utils.h>


void SysTick_Handler (void)
{
	ticks++;
}

// return the system clock as milliseconds
uint32_t millis (void)
{
   return ticks;
}

void delay_ms (uint32_t t)
{
  uint32_t start, end;
  start = millis();
  end = start + t;
  if (start < end) {
    while ((millis() >= start) && (millis() < end)) {
      // do nothing
    }
  } else {
    while ((millis() >= start) || (millis() < end)) {
      // do nothing
    };
  }
}


void utils_systick_init (uint16_t frequency)
{
   RCC_ClocksTypeDef RCC_Clocks;
   RCC_GetClocksFreq (&RCC_Clocks);
   (void) SysTick_Config (RCC_Clocks.HCLK_Frequency / frequency);
}



