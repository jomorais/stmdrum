/*
 * stmdrum.c
 *
 *  Created on: 27/04/2017
 *      Author: jomorais
 */
#include <stmdrum.h>
#include <settings.h>

void stmdrum_init ( void )
{
		settings_init();
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
