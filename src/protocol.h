/*
 * protocol.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stm32f10x_usart.h>
#include <stm32f10x_rcc.h>
#include <config.h>
#include <attributes.h>

#define MIDI_NOTE_OFF          0x80
#define MIDI_NOTE_ON           0x90
#define MIDI_PRESSURE          0xA0
#define MIDI_CONTROLLER_CHANGE 0xB0
#define MIDI_PROGRAM_CHANGE    0xC0
#define MIDI_CHANNEL_PRESSURE  0xD0
#define MIDI_PITCH_BEND        0xE0

//MIDI defines
#define NOTE_ON_CMD 		0x90
#define NOTE_OFF_CMD 		0x80
#define MAX_MIDI_VELOCITY 	127

void protocol_init ( void );
uint16_t protocol_raw_send ( char * data , uint16_t size );
void protocol_send_midi ( char status , char pitch , char velocity );

void protocol_midi_note_off ( u8 channel , u8 key , u8 velocity );
void protocol_midi_note_on ( u8 channel , u8 key , u8 velocity );
void protocol_midi_key_pressure ( u8 channel , u8 key , u8 value );
void protocol_midi_controller_change ( u8 channel , u8 control , u8 value );
void protocol_midi_program_change ( u8 channel , u8 program );
void protocol_midi_channel_pressure ( u8 channel , u8 value );
void protocol_midi_pitch_bend ( u8 channel , int value );
void protocol_midi_command ( u8 command , u8 channel , u8 param1 , u8 param2 );
void protocol_midi_command_short ( u8 command , u8 channel , u8 param1 );

#endif /* PROTOCOL_H_ */
