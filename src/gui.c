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
		
		menu_controller.current_page = 0;
		strcpy(menu_controller.menu_page[PAGE_1].title,"MIDI.THRES  1/8");
		menu_controller.menu_page[PAGE_1].step = 10;
		menu_controller.menu_page[PAGE_1].attribute = &stmdrum_settings.MIDI_THRESHOLD;
		
		strcpy(menu_controller.menu_page[PAGE_2].title,"NOTE.TIME   2/8");
		menu_controller.menu_page[PAGE_2].step = 1;
		menu_controller.menu_page[PAGE_2].attribute = &stmdrum_settings.MAX_TIME_NOTE;
		
		strcpy(menu_controller.menu_page[PAGE_3].title,"MAXVELOCITY 3/8");
		menu_controller.menu_page[PAGE_3].step = 1;
		menu_controller.menu_page[PAGE_3].attribute = &stmdrum_settings.MAX_VELOCITY;

		strcpy(menu_controller.menu_page[PAGE_4].title,"VELOCITYSEN 4/8");
		menu_controller.menu_page[PAGE_4].step = 1;
		menu_controller.menu_page[PAGE_4].attribute = &stmdrum_settings.VELOCITY_SENSE;

		strcpy(menu_controller.menu_page[PAGE_5].title,"MAX.RATE.HZ 5/8");
		menu_controller.menu_page[PAGE_5].step = 1;
		menu_controller.menu_page[PAGE_5].attribute = &stmdrum_settings.MAX_RATE_HZ;

		strcpy(menu_controller.menu_page[PAGE_6].title,"E.VELOCITY  6/9");
		menu_controller.menu_page[PAGE_6].step = 1;
		menu_controller.menu_page[PAGE_6].attribute = &stmdrum_settings.ENABLE_VELOCITY;

		strcpy(menu_controller.menu_page[PAGE_7].title,"E.FILTER    7/9");
		menu_controller.menu_page[PAGE_7].step = 1;
		menu_controller.menu_page[PAGE_7].attribute = &stmdrum_settings.ENABLE_KALMAN;

		strcpy(menu_controller.menu_page[PAGE_8].title,"E.MIDIPORT2 8/8");
		menu_controller.menu_page[PAGE_8].step = 1;
		menu_controller.menu_page[PAGE_8].attribute = &stmdrum_settings.ENABLE_KALMAN;

		strcpy(menu_controller.menu_page[PAGE_EXIT].title,"---   EXIT   ---");

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

void gui_next_page(void)
{
		menu_controller.current_page++;
		if(menu_controller.current_page > (N_PAGES))
				menu_controller.current_page = PAGE_EXIT;
		gui_show_page(menu_controller.current_page);

}

void gui_previous_page(void)
{
		menu_controller.current_page--;
		if(menu_controller.current_page < PAGE_EXIT)
				menu_controller.current_page = PAGE_8;
		gui_show_page(menu_controller.current_page);
}

void gui_show_page(u8 page)
{
		char attribute_line[16];
		memset(attribute_line,' ',sizeof(attribute_line));
		lcd16x2_clear_buffer();
		lcd16x2_write_string(0, 0, menu_controller.menu_page[page].title, sizeof(menu_controller.menu_page[page].title));
		if(page != PAGE_EXIT)
		{
				int s = sprintf(attribute_line,"VLR: %d", *(u16*)menu_controller.menu_page[page].attribute);
				lcd16x2_write_string(0, 1, attribute_line, s);
				lcd16x2_write_cmd(0x0F);
		}

;
}

void gui_fsm_update ( void )
{
		input_update();
		if(menu_button_pressed)
		{
				gui_fsm_set_state(menu_controller.current_page);
				menu_button_pressed = 0;
		}

		if(encoder_state != ENC_STOP)
		{
				if(encoder_state == ENC_RIGHT)
				{
						gui_next_page();
				}
				else
				{
						if(encoder_state == ENC_LEFT)
						{
								gui_previous_page();
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
				case PAGE_1:
				{

						// todo
				}
				break;
				default :
				{
						// todo
				}
						break;
		}
}
