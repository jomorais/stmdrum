/*
 * minicontroller.c
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#include <midicontroller.h>

void midicontroller_init ( void )
{
		protocol_init();
		notes[CHANNEL_0] = 50;
		notes[CHANNEL_1] = 60;
		notes[CHANNEL_2] = 67;
		notes[CHANNEL_3] = 69;
		notes[CHANNEL_4] = 40;
		notes[CHANNEL_5] = 52;
		notes[CHANNEL_6] = 36;
		notes[CHANNEL_7] = 55;
		int channel;
		for ( channel = START_CHANNEL; channel < N_CHANNELS ; channel++ )
		{
				max_play_time[channel] = MAX_TIME_NOTE;
				note_play_time[channel] = 0;
				active_note[channel] = NOT_ACTIVE_NOTE;
		}
}
void midicontroller_update ( void )
{
		int channel;
		float velocity;
		if ( ( millis() - main_tick ) > TICK_RATE_MS )
		{
				main_tick = millis();
				for ( channel = START_CHANNEL; channel < N_CHANNELS ; channel++ )
				{
						adc_raw[channel] = adccontroller_read_channel(channel) * GAIN;

						if ( ENABLE_KALMAN )
						{
								kalman_update(channel);
								velocity = (float) adc_smooth[channel];
						}
						else
								velocity = (float) adc_raw[channel];

						if ( velocity > MIDI_THRESHOLD )
						{
								if ( active_note[channel] == NOT_ACTIVE_NOTE )
								{
										if ( MIDI_ENABLE_VELOCITY )
										{
												velocity = velocity * (float)(1 / VELOCITY_SENSE);
												if ( velocity > MAX_VELOCITY )
														velocity = MAX_VELOCITY;
										}
										else
										{
												velocity = MAX_VELOCITY;
										}
										protocol_midi_note_on( 0 , notes[channel] , (u8) velocity );
										note_play_time[channel] = millis();
										active_note[channel] = ACTIVE_NOTE;
								}
						}
						else
						{
								if ( active_note[channel] == ACTIVE_NOTE )
								{
										if ( ( millis() - note_play_time[channel] ) > max_play_time[channel] )
										{
												note_play_time[channel] = millis();
												active_note[channel] = NOT_ACTIVE_NOTE;
												protocol_midi_note_off( 0 , notes[channel] , (u8) velocity );
										}
								}
						}
				}
		}
}
