/*
 * attributes.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_
#include <config.h>


#define N_PAGES			9

#define PAGE_EXIT		0
#define PAGE_1			1
#define PAGE_2			2
#define PAGE_3			3
#define PAGE_4			4
#define PAGE_5			5
#define PAGE_6			6
#define PAGE_7			7
#define PAGE_8			8
#define PAGE_9			9
#define RUN					250
#define ON_MENU			251

#define EDIT_MODE		1

#define DEFAULT_ENABLE_KALMAN			1
#define DEFAULT_ENABLE_VELOCITY 	1
#define DEFAULT_ENABLE_UART3			0
#define DEFAULT_MAX_RATE_HZ				200
#define DEFAULT_MAX_TIME_NOTE			30
#define DEFAULT_MIDI_THRESHOLD		300
#define DEFAULT_MAX_VELOCITY			127
#define DEFAULT_VELOCITY_SENSE		20
#define DEFAULT_NOTE_OFF_ACTIVE		0


typedef struct
{
	char title[16];
	u8 page;
	void *attribute;
	u16 step;
	u8 data_type;
	u16 max;
	u16 min;
	u16 eeprom_addr;
} menu_page_t;


typedef struct
{
	int current_page;
	u8 editmode;
	u8 menu_state;
	menu_page_t menu_page[N_PAGES + 1];
} menu_controller_t;

menu_controller_t menu_controller;

typedef struct
{
		u8 fsm_state;
		u8 fsm_last_state;
} fsm_controller_t;

typedef struct
{
		u16 MIDI_THRESHOLD;
		u16 VELOCITY_SENSE;
		u16 MAX_VELOCITY;
		u16 MAX_TIME_NOTE;
		u16 MAX_RATE_HZ;
		u16 ENABLE_KALMAN;
		u16 ENABLE_UART3;
		u16 ENABLE_VELOCITY;
		u16 ENABLE_NOTE_OFF;
		float tick_rate_ms;
} stmdrum_settings_t;

u8 status;
u8 menu_button_pressed;
u8 menu_button_last;
u16 adc_raw[N_CHANNELS];
u16 adc_smooth[N_CHANNELS];
u32 note_play_time[N_CHANNELS];
u8 active_note[N_CHANNELS];
u8 notes[N_CHANNELS];
u32 max_play_time[N_CHANNELS];
u32 main_tick;

stmdrum_settings_t stmdrum_settings;
fsm_controller_t fsm_controller;

#endif /* ATTRIBUTES_H_ */
