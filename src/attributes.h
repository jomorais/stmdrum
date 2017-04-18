/*
 * attributes.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef ATTRIBUTES_H_
#define ATTRIBUTES_H_
#include <config.h>
u8 status;
u32 adc_raw[N_CHANNELS];
u16 adc_smooth[N_CHANNELS];
u32 note_play_time[N_CHANNELS];
u8 active_note[N_CHANNELS];
u8 notes[N_CHANNELS];
u32 max_play_time[N_CHANNELS];


#endif /* ATTRIBUTES_H_ */
