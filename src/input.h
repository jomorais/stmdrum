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
u8 menu_encoder_a_last;
u8 encoder_state;

#define ENC_RIGHT		1
#define ENC_LEFT  	2
#define ENC_STOP  	0

void input_init();
void input_update();
u8  input_button_pressed();
#endif /* INPUT_H_ */
