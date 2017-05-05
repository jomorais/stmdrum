/*
 * stmdrum.c
 *
 *  Created on: 27/04/2017
 *      Author: jomorais
 */
#include <stmdrum.h>

void stmdrum_init ( void )
{
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
