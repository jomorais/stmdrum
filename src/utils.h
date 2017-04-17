/*
 * utils.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stm32f10x.h>


volatile uint32_t ticks;

void delay_ms (uint32_t t);

uint32_t millis (void);


void utils_systick_init(uint16_t frequency);

#endif /* UTILS_H_ */
