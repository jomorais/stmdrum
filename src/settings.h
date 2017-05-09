/*
 * settings.h
 *
 *  Created on: 29/03/2017
 *      Author: jomorais
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <includes.h>
#include <attributes.h>

#define START_ADDR			0x5555
#define FORMATTED_ADDR	START_ADDR
#define FORMATTED				1155

#define ENABLE_KALMAN_ADDR 			FORMATTED_ADDR 				+ 2
#define ENABLE_VELOCITY_ADDR 		ENABLE_KALMAN_ADDR 		+ 2
#define ENABLE_UART3_ADDR				ENABLE_VELOCITY_ADDR 	+ 2
#define MAX_RATE_HZ_ADDR				ENABLE_UART3_ADDR 		+ 2
#define MAX_TIME_NOTE_ADDR			MAX_RATE_HZ_ADDR 			+ 2
#define MIDI_THRESHOLD_ADDR			MAX_TIME_NOTE_ADDR 		+ 2
#define MAX_VELOCITY_ADDR				MIDI_THRESHOLD_ADDR 	+ 2
#define VELOCITY_SENSE_ADDR			MAX_VELOCITY_ADDR 		+ 2

u16 settings_init(void);
u16 settings_write(u16 addr, u16 data);
u16 settings_read(u16 addr, u16 *data);
#endif /* SETTINGS_H_ */
