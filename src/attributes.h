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

u8 status;
u16 adc_raw[N_CHANNELS];
u16 adc_smooth[N_CHANNELS];
u32 note_play_time[N_CHANNELS];
u8 active_note[N_CHANNELS];
u8 notes[N_CHANNELS];
u32 max_play_time[N_CHANNELS];
u32 main_tick;
fsm_controller_t fsm_controller;

#endif /* ATTRIBUTES_H_ */
