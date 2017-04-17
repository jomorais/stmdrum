/*
 * adccontroller.h
 *
 *  Created on: 27/03/2017
 *      Author: jomorais
 */

#ifndef ADCCONTROLLER_H_
#define ADCCONTROLLER_H_
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_adc.h>
#include <stm32f10x_it.h>
#include <includes.h>
#include <attributes.h>


void adccontroller_init(void);
u16 adccontroller_read_channel(u8 channel);
void adccontroller_update_all(void);
void adccontroller_dma1_init(void);

#endif /* ADCCONTROLLER_H_ */
