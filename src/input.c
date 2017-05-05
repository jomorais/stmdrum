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
}

void input_update()
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
u8  input_button_pressed()
{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
				return 0;
		else
				return 1;
}
