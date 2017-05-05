/*
 * input.h
 *
 *  Created on: 27/04/2017
 *      Author: jomorais
 */

#ifndef INPUT_H_
#define INPUT_H_
#include <stm32f10x_gpio.h>
#include <attributes.h>

void input_init();
void input_update();
u8  input_button_pressed();
#endif /* INPUT_H_ */
