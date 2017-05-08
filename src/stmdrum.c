/*
 * stmdrum.c
 *
 *  Created on: 27/04/2017
 *      Author: jomorais
 */
#include <stmdrum.h>

void stmdrum_init ( void )
{
		stmdrum_settings.ENABLE_KALMAN = 1;
		stmdrum_settings.ENABLE_VELOCITY = 1;
		stmdrum_settings.ENABLE_UART3 = 0;
		stmdrum_settings.MAX_RATE_HZ = 100;
		stmdrum_settings.MAX_TIME_NOTE = 30;
		stmdrum_settings.MIDI_THRESHOLD = 1000;
		stmdrum_settings.MAX_VELOCITY = 127;
		stmdrum_settings.VELOCITY_SENSE= 80;
		utils_systick_init();
		adccontroller_init();
		kalman_init();
		midicontroller_init();
		gui_init();
}

void stmdrum_run ( void )
{
		stmdrum_init();
		while(1)
		{
				midicontroller_update();
				gui_update();
		}
}
