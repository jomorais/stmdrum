/*
 * menu.c
 *
 *  Created on: 17/04/2017
 *      Author: jomorais
 */
#include <gui.h>
#include <input.h>
int i;
char buffer[16];
void gui_init ( void )
{
		lcd16x2_init();
		input_init();
		lcd16x2_write_string(0,0,"    stmDRUM    ",15);
		
		/*
		 * 		u16 MIDI_THRESHOLD;
		 * 
		 * 		u8 MAX_TIME_NOTE;
		u8 VELOCITY_SENSE;
		u8 MAX_VELOCITY;

		u16 MAX_RATE_HZ;
		u8 MIDI_ENABLE_VELOCITY;
		u8 ENABLE_KALMAN;
		u8 ENABLE_UART3;
		u8 ENABLE_VELOCITY;
		* */
		menu_controller.current_page = 0;
		strcpy(menu_controller.menu_page[0].title,"THRESHOLD 1/10");
		menu_controller.menu_page[0].step = 10;
		menu_controller.menu_page[0].attribute = &stmdrum_settings.MIDI_THRESHOLD;
		
		strcpy(menu_controller.menu_page[1].title,"MAX_T_NOTE 1/10");
		menu_controller.menu_page[1].step = 10;
		menu_controller.menu_page[1].attribute = &stmdrum_settings.MIDI_THRESHOLD;
		
}

void gui_update ( void )
{
		// fsm_update function runs before any state of FSM
		gui_fsm_update();

		// execute main states
		gui_fsm_states();

		// fsm_update function runs after any state of FSM
		gui_fsm_late_update();

		// update lcd
		lcd16x2_update();
}


void gui_fsm_update ( void )
{
		input_update();
		if(menu_button_pressed)
		{
				menu_button_pressed = 0;
				lcd16x2_write_string(0,0,menu_controller.menu_page[0].title,16);
		}

		if(encoder_state != ENC_STOP)
		{
				bzero(buffer,sizeof(buffer));
				if(encoder_state == ENC_RIGHT)
				{
						lcd16x2_write_string(0,0,"    >>>>    ",12);
				}
				else
				{
						if(encoder_state == ENC_LEFT)
						{
								lcd16x2_write_string(0,0,"    <<<<    ",12);
						}
				}
		}
}

void gui_fsm_late_update ( void )
{
		//todo
}

void gui_fsm_set_state ( int fsm_state )
{
		fsm_controller.fsm_last_state = fsm_controller.fsm_state;
		fsm_controller.fsm_state = fsm_state;
}

u8 gui_fsm_get_state ( void )
{
		return fsm_controller.fsm_state;
}

void gui_fsm_states ( void )
{
		switch ( gui_fsm_get_state() )
		{
				case 1:
				{
						// todo
				}
				default :
				{
						// todo
				}
						break;
		}
}
