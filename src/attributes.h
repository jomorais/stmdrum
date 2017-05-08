/*
 * attributes.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_
#include <config.h>
typedef struct
{
		u8 fsm_state;
		u8 fsm_last_state;
} fsm_controller_t;

typedef struct
{
		u16 MIDI_THRESHOLD;
		u8 VELOCITY_SENSE;
		u8 MAX_VELOCITY;
		u8 MAX_TIME_NOTE;
		u16 MAX_RATE_HZ;
		u8 MIDI_ENABLE_VELOCITY;
		u8 ENABLE_KALMAN;
		u8 ENABLE_UART3;
		u8 ENABLE_VELOCITY;
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
