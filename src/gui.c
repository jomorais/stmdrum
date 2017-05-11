/*
 * menu.c
 *
 *  Created on: 17/04/2017
 *      Author: jomorais
 */
#include <gui.h>
#include <input.h>
#include <settings.h>
int i;
char buffer[16];


void gui_init ( void )
{
		lcd16x2_init();
		input_init();
		lcd16x2_write_string( 0 , 0 , "###  stmDRUM ###" , 16 );
		menu_controller.current_page = 0;
		menu_controller.menu_state = RUN;
		strcpy( menu_controller.menu_page[PAGE_1].title , "MIDI.THRES  1/9" );
		menu_controller.menu_page[PAGE_1].step = 10;
		menu_controller.menu_page[PAGE_1].max = 2048;
		menu_controller.menu_page[PAGE_1].min = 0;
		menu_controller.menu_page[PAGE_1].eeprom_addr = MIDI_THRESHOLD_ADDR;
		menu_controller.menu_page[PAGE_1].attribute = &stmdrum_settings.MIDI_THRESHOLD;
		
		strcpy( menu_controller.menu_page[PAGE_2].title , "NOTE.TIME   2/9" );
		menu_controller.menu_page[PAGE_2].step = 1;
		menu_controller.menu_page[PAGE_2].max = 256;
		menu_controller.menu_page[PAGE_2].min = 5;
		menu_controller.menu_page[PAGE_2].eeprom_addr = MAX_TIME_NOTE_ADDR;
		menu_controller.menu_page[PAGE_2].attribute = &stmdrum_settings.MAX_TIME_NOTE;
		
		strcpy( menu_controller.menu_page[PAGE_3].title , "MAXVELOCITY 3/9" );
		menu_controller.menu_page[PAGE_3].step = 1;
		menu_controller.menu_page[PAGE_3].max = 127;
		menu_controller.menu_page[PAGE_3].min = 1;
		menu_controller.menu_page[PAGE_3].eeprom_addr = MAX_VELOCITY_ADDR;
		menu_controller.menu_page[PAGE_3].attribute = &stmdrum_settings.MAX_VELOCITY;

		strcpy( menu_controller.menu_page[PAGE_4].title , "VELOCITYSEN 4/9" );
		menu_controller.menu_page[PAGE_4].step = 1;
		menu_controller.menu_page[PAGE_4].max = 30;
		menu_controller.menu_page[PAGE_4].min = 10;
		menu_controller.menu_page[PAGE_4].eeprom_addr = VELOCITY_SENSE_ADDR;
		menu_controller.menu_page[PAGE_4].attribute = &stmdrum_settings.VELOCITY_SENSE;

		strcpy( menu_controller.menu_page[PAGE_5].title , "MAX.RATE.HZ 5/9" );
		menu_controller.menu_page[PAGE_5].step = 1;
		menu_controller.menu_page[PAGE_5].max = 200;
		menu_controller.menu_page[PAGE_5].min = 100;
		menu_controller.menu_page[PAGE_5].eeprom_addr = MAX_RATE_HZ_ADDR;
		menu_controller.menu_page[PAGE_5].attribute = &stmdrum_settings.MAX_RATE_HZ;

		strcpy( menu_controller.menu_page[PAGE_6].title , "E.VELOCITY  6/9" );
		menu_controller.menu_page[PAGE_6].step = 1;
		menu_controller.menu_page[PAGE_6].max = 1;
		menu_controller.menu_page[PAGE_6].min = 0;
		menu_controller.menu_page[PAGE_6].eeprom_addr = ENABLE_VELOCITY_ADDR;
		menu_controller.menu_page[PAGE_6].attribute = &stmdrum_settings.ENABLE_VELOCITY;

		strcpy( menu_controller.menu_page[PAGE_7].title , "E.FILTER    7/9" );
		menu_controller.menu_page[PAGE_7].step = 1;
		menu_controller.menu_page[PAGE_7].max = 1;
		menu_controller.menu_page[PAGE_7].min = 0;
		menu_controller.menu_page[PAGE_7].eeprom_addr = ENABLE_KALMAN_ADDR;
		menu_controller.menu_page[PAGE_7].attribute = &stmdrum_settings.ENABLE_KALMAN;

		strcpy( menu_controller.menu_page[PAGE_8].title , "E.MIDIPORT2 8/9" );
		menu_controller.menu_page[PAGE_8].step = 1;
		menu_controller.menu_page[PAGE_8].max = 1;
		menu_controller.menu_page[PAGE_8].min = 0;
		menu_controller.menu_page[PAGE_8].eeprom_addr = ENABLE_UART3_ADDR;
		menu_controller.menu_page[PAGE_8].attribute = &stmdrum_settings.ENABLE_UART3;

		strcpy( menu_controller.menu_page[PAGE_9].title , "E.NOTE_OFF 9/9" );
		menu_controller.menu_page[PAGE_9].step = 1;
		menu_controller.menu_page[PAGE_9].max = 1;
		menu_controller.menu_page[PAGE_9].min = 0;
		menu_controller.menu_page[PAGE_9].eeprom_addr = NOTE_OFF_ACTIVE_ADDR;
		menu_controller.menu_page[PAGE_9].attribute = &stmdrum_settings.ENABLE_NOTE_OFF;

		strcpy( menu_controller.menu_page[PAGE_EXIT].title , "---   EXIT   ---" );

}

void gui_update ( void )
{

		input_update();
		if ( menu_button_pressed )
		{
				menu_button_pressed = 0;
				
				if ( menu_controller.menu_state == ON_MENU )
				{
						if ( menu_controller.current_page != PAGE_EXIT && menu_controller.editmode == 0 )
						{
								menu_controller.editmode = 1;
								gui_show_page( menu_controller.current_page );

						}
						else
						{
								if ( menu_controller.current_page != PAGE_EXIT && menu_controller.editmode == 1 )
								{
										menu_controller.editmode = 0;
										gui_show_page( menu_controller.current_page );
										settings_write(menu_controller.menu_page[menu_controller.current_page].eeprom_addr, *(u16*)menu_controller.menu_page[menu_controller.current_page].attribute);
								}
						}
				}
				
				if ( menu_controller.menu_state == RUN )
				{
						menu_controller.menu_state = ON_MENU;
						menu_controller.current_page = PAGE_1;
						gui_show_page( menu_controller.current_page );
						menu_controller.editmode = 0;
				}
				
				if ( menu_controller.current_page == PAGE_EXIT )
				{
						menu_controller.editmode = 0;
						menu_controller.menu_state = RUN;
						lcd16x2_write_string( 0 , 0 , "###  stmDRUM ###" , 16 );
				}

		}

		if ( menu_controller.menu_state == ON_MENU )
		{
				if ( encoder_state != ENC_STOP )
				{
						if ( menu_controller.editmode == 1 )
						{
								if ( encoder_state == ENC_RIGHT )
								{
										*(u16*) menu_controller.menu_page[menu_controller.current_page].attribute += menu_controller.menu_page[menu_controller.current_page].step;
										if ( *(u16*) menu_controller.menu_page[menu_controller.current_page].attribute > menu_controller.menu_page[menu_controller.current_page].max )
												*(u16*) menu_controller.menu_page[menu_controller.current_page].attribute = menu_controller.menu_page[menu_controller.current_page].max;

								}
								else
								{
										*(u16*) menu_controller.menu_page[menu_controller.current_page].attribute -= menu_controller.menu_page[menu_controller.current_page].step;
										if ( *(u16*) menu_controller.menu_page[menu_controller.current_page].attribute >= 65535 || *(u16*) menu_controller.menu_page[menu_controller.current_page].attribute < menu_controller.menu_page[menu_controller.current_page].min )
												*(u16*) menu_controller.menu_page[menu_controller.current_page].attribute = menu_controller.menu_page[menu_controller.current_page].min;
								}
								gui_show_page( menu_controller.current_page );
						}
						else
						{
								if ( encoder_state == ENC_RIGHT )
								{
										gui_next_page();
										gui_show_page( menu_controller.current_page );
								}
								else
								{
										gui_previous_page();
										gui_show_page( menu_controller.current_page );
								}
						}
				}
		}

		// update lcd
		lcd16x2_update();
}

void gui_next_page ( void )
{
		menu_controller.current_page++;
		if ( menu_controller.current_page > ( N_PAGES ) )
				menu_controller.current_page = PAGE_EXIT;
}

void gui_previous_page ( void )
{
		menu_controller.current_page--;
		if ( menu_controller.current_page < PAGE_EXIT )
				menu_controller.current_page = PAGE_9;
}

void gui_show_page ( u8 page )
{
		char attribute_line[16];
		memset( attribute_line , ' ' , sizeof ( attribute_line ) );
		lcd16x2_clear_buffer();
		lcd16x2_write_string( 0 , 0 , menu_controller.menu_page[page].title , sizeof ( menu_controller.menu_page[page].title ) );
		if ( page != PAGE_EXIT )
		{
				int s;
				if ( menu_controller.editmode == 1 )
				{
						s = sprintf( attribute_line , "> VLR: %d" , *(u16*) menu_controller.menu_page[page].attribute );
				}
				else
				{
						s = sprintf( attribute_line , "  VLR: %d" , *(u16*) menu_controller.menu_page[page].attribute );
				}

				lcd16x2_write_string( 0 , 1 , attribute_line , s );
		}
}
