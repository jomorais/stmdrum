/*
 * input.c
 *
 *  Created on: 27/04/2017
 *      Author: jomorais
 */

#include <input.h>

void input_init()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // button
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13; // encoder
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		menu_button_last = 1;
		menu_encoder_a_last = 0;
}

void input_menu_button_update()
{
		if(menu_button_last == 1 && GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0) // falling edge
		{
				menu_button_pressed = 1;
				menu_button_last = 0;
		}
		else
		{
				if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 1)
				{
						menu_button_last = 1;
				}
		}
}

void input_encoder_update()
{
		u8 a_pin = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
		if((menu_encoder_a_last == 0) && (a_pin == 1))
		{
				u8 b_pin = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
				if (b_pin == 0)
				{
						encoder_state = ENC_RIGHT;
				}
				else
				{
						encoder_state = ENC_LEFT;
				}
		}
		else
		{
				encoder_state = ENC_STOP;
		}
		menu_encoder_a_last = a_pin;
}


void input_update()
{
		input_menu_button_update();
		input_encoder_update();
}
u8  input_button_pressed()
{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
				return 0;
		else
				return 1;
}
