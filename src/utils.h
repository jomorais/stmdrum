/*
 * utils.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stm32f10x.h>


volatile uint32_t tick_millis;
volatile uint32_t ms_ticks;

void delay_ms (uint32_t t);
void delay_us (uint32_t t);

u32 millis (void);
u32 micros (void);


void utils_systick_init(void);

#endif /* UTILS_H_ */
