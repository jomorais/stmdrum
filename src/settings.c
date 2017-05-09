/*
 * settings.c
 *
 *  Created on: 29/03/2017
 *      Author: jomorais
 */

#include <settings.h>
#include <eeprom.h>
#include <stm32f10x_flash.h>
uint16_t VirtAddVarTab[NumbOfVar];

u16 settings_init(void)
{
		FLASH_Unlock();
		EE_Init();
		u16 data;
		if( EE_ReadVariable( FORMATTED_ADDR, &data) == 0)
		{
				if(data == FORMATTED)
				{
						EE_ReadVariable( ENABLE_KALMAN_ADDR, &stmdrum_settings.ENABLE_KALMAN);
						EE_ReadVariable( ENABLE_VELOCITY_ADDR, &stmdrum_settings.ENABLE_VELOCITY);
						EE_ReadVariable( ENABLE_UART3_ADDR, &stmdrum_settings.ENABLE_UART3);
						EE_ReadVariable( MAX_RATE_HZ_ADDR, &stmdrum_settings.MAX_RATE_HZ);
						EE_ReadVariable( MAX_TIME_NOTE_ADDR, &stmdrum_settings.MAX_TIME_NOTE);
						EE_ReadVariable( MIDI_THRESHOLD_ADDR, &stmdrum_settings.MIDI_THRESHOLD);
						EE_ReadVariable( MAX_VELOCITY_ADDR, &stmdrum_settings.MAX_VELOCITY);
						EE_ReadVariable( VELOCITY_SENSE_ADDR, &stmdrum_settings.VELOCITY_SENSE);

						return 0;
				}
				else
				{
						stmdrum_settings.ENABLE_KALMAN = DEFAULT_ENABLE_KALMAN;
						stmdrum_settings.ENABLE_VELOCITY = DEFAULT_ENABLE_VELOCITY;
						stmdrum_settings.ENABLE_UART3 = DEFAULT_ENABLE_UART3;
						stmdrum_settings.MAX_RATE_HZ = DEFAULT_MAX_RATE_HZ;
						stmdrum_settings.MAX_TIME_NOTE = DEFAULT_MAX_TIME_NOTE;
						stmdrum_settings.MIDI_THRESHOLD = DEFAULT_MIDI_THRESHOLD;
						stmdrum_settings.MAX_VELOCITY = DEFAULT_MAX_VELOCITY;
						stmdrum_settings.VELOCITY_SENSE = DEFAULT_VELOCITY_SENSE;

						EE_WriteVariable( FORMATTED_ADDR, FORMATTED);
						EE_WriteVariable( ENABLE_KALMAN_ADDR, stmdrum_settings.ENABLE_KALMAN);
						EE_WriteVariable( ENABLE_VELOCITY_ADDR, stmdrum_settings.ENABLE_VELOCITY);
						EE_WriteVariable( ENABLE_UART3_ADDR, stmdrum_settings.ENABLE_UART3);
						EE_WriteVariable( MAX_RATE_HZ_ADDR, stmdrum_settings.MAX_RATE_HZ);
						EE_WriteVariable( MAX_TIME_NOTE_ADDR, stmdrum_settings.MAX_TIME_NOTE);
						EE_WriteVariable( MIDI_THRESHOLD_ADDR, stmdrum_settings.MIDI_THRESHOLD);
						EE_WriteVariable( MAX_VELOCITY_ADDR, stmdrum_settings.MAX_VELOCITY);
						EE_WriteVariable( VELOCITY_SENSE_ADDR, stmdrum_settings.VELOCITY_SENSE);

						return 1;
				}

		}
		return 1;
}

u16 settings_write(u16 addr, u16 data)
{
		return EE_WriteVariable( addr, data);
}

u16 settings_read(u16 addr, u16 *data)
{
		return EE_ReadVariable( addr, data);
}
