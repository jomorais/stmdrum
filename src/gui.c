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
		int i  =0;
		lcd16x2_init();
		input_init();
		lcd16x2_write_string(0,1,"TEST",5);
		// set the initial state
		gui_fsm_set_state( INIT );
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
				i++;
				bzero(buffer,sizeof(buffer));
				int size = sprintf(buffer,"i: %d",i);
				menu_button_pressed = 0;
				lcd16x2_write_string(0,1,buffer,size);
		}

		if(encoder_state != ENC_STOP)
		{
				int size = 0;
				bzero(buffer,sizeof(buffer));
				if(encoder_state == ENC_RIGHT)
				{
						size = sprintf(buffer,"enc_state: right");
						lcd16x2_write_string(0,0,buffer,size);
				}
				else
				{
						if(encoder_state == ENC_LEFT)
						{
								size = sprintf(buffer,"enc_state: left");
								lcd16x2_write_string(0,0,buffer,size);
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
				case INIT :
				{
						//todo
				}
						break;
				default :
				{
						// todo
				}
						break;
		}
}
