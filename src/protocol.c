/*
 * protocol.c
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */
#include <protocol.h>

void protocol_usart_Init(void) {
	GPIO_InitTypeDef gpioConfig;
	GPIO_InitTypeDef gpioConfig3;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB ,ENABLE);
	if(ENABLE_UART3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 ,ENABLE);
	}

	//PA9 = USART1.TX => Alternative Function Output
	gpioConfig.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioConfig.GPIO_Pin = GPIO_Pin_9;
	gpioConfig.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpioConfig);

	//PA10 = USART1.RX => Input
	gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioConfig.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &gpioConfig);

	if(ENABLE_UART3)
	{
		//PB10 = USART3.TX => Alternative Function Output
		gpioConfig3.GPIO_Mode = GPIO_Mode_AF_PP;
		gpioConfig3.GPIO_Pin = GPIO_Pin_10;
		gpioConfig3.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &gpioConfig3);

		//PB11 = USART3.RX => Input
		gpioConfig3.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		gpioConfig3.GPIO_Pin = GPIO_Pin_11;
		GPIO_Init(GPIOB, &gpioConfig3);
	}


	USART_InitTypeDef usartConfig;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	USART_ClockStructInit(&USART_ClockInitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);
	usartConfig.USART_BaudRate = 115200;
	usartConfig.USART_WordLength = USART_WordLength_8b;
	usartConfig.USART_StopBits = USART_StopBits_1;
	usartConfig.USART_Parity = USART_Parity_No;
	usartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &usartConfig);
	USART_Cmd(USART1, ENABLE);

	if(ENABLE_UART3)
	{
		USART_InitTypeDef usartConfig3;
		USART_ClockInitTypeDef USART_ClockInitStructure3;
		USART_ClockStructInit(&USART_ClockInitStructure3);
		USART_ClockInit(USART3, &USART_ClockInitStructure3);
		usartConfig3.USART_BaudRate = 31250;
		usartConfig3.USART_WordLength = USART_WordLength_8b;
		usartConfig3.USART_StopBits = USART_StopBits_1;
		usartConfig3.USART_Parity = USART_Parity_No;
		usartConfig3.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		usartConfig3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART3, &usartConfig3);
		USART_Cmd(USART3, ENABLE);
	}
}

void protocol_init(void) {
	protocol_usart_Init();
}

uint16_t protocol_raw_send(char * data, uint16_t size) {
	uint16_t idx = 0;
	for (idx = 0; idx < size; idx++) {
		USART_SendData(USART1, data[idx]);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {
		}

		if(ENABLE_UART3)
		{
			USART_SendData(USART3, data[idx]);
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {
			}
		}
	}
	return size;
}

void protocol_midi_command(u8 command, u8 channel, u8 param1, u8 param2)
{
	char midi_package[3];
	midi_package[0] = command | (channel & 0x0F);
	midi_package[1] = param1 & 0x7F;
	midi_package[2] = param2 & 0x7F;
	protocol_raw_send(midi_package, sizeof(midi_package));
}

void protocol_midi_command_short(u8 command, u8 channel, u8 param1)
{
	char midi_package[2];
	midi_package[0] = command | (channel & 0x0F);
	midi_package[1] = param1 & 0x7F;
	protocol_raw_send(midi_package, sizeof(midi_package));
}

void protocol_midi_note_off(u8 channel, u8 key, u8 velocity)
{
	protocol_midi_command(MIDI_NOTE_OFF, channel, key, velocity);
}

void protocol_midi_note_on(u8 channel, u8 key, u8 velocity)
{
	protocol_midi_command(MIDI_NOTE_ON, channel, key, velocity);
}

void protocol_midi_key_pressure(u8 channel, u8 key, u8 value)
{
	protocol_midi_command(MIDI_PRESSURE, channel, key, value);
}

void protocol_midi_controller_change(u8 channel, u8 control, u8 value)
{
	protocol_midi_command(MIDI_CONTROLLER_CHANGE, channel, control, value);
}

void protocol_midi_program_change(u8 channel, u8 program)
{
	protocol_midi_command_short(MIDI_PROGRAM_CHANGE, channel, program);
}

void protocol_midi_channel_pressure(u8 channel, u8 value)
{
	protocol_midi_command_short(MIDI_CHANNEL_PRESSURE, channel, value);
}

void protocol_midi_pitch_bend(u8 channel, int value)
{
	protocol_midi_command(MIDI_PITCH_BEND, channel, value & 0x7F, value >> 7);
}
