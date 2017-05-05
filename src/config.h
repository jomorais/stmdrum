/*
 * config.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define N_CHANNELS 			 8
#define CHANNEL_0 			 0
#define CHANNEL_1 			 1
#define CHANNEL_2 			 2
#define CHANNEL_3 			 3
#define CHANNEL_4 			 4
#define CHANNEL_5 			 5
#define CHANNEL_6 			 6
#define CHANNEL_7 			 7
#define START_CHANNEL		 CHANNEL_0
#define GAIN 				 1

// desabilita filtro
#define ENABLE_KALMAN 		 	  0
#define ENABLE_UART3 		 		  1
#define ADC_FULLSCALE		 			4096
#define MIDI_THRESHOLD        1000
#define MAX_TIME_NOTE         30
#define MIDI_ENABLE_VELOCITY  1
#define VELOCITY_SENSE        0.042011719
#define MAX_VELOCITY          127
#define MAX_RATE_HZ			 			100
#define TICK_RATE_MS		 (float)(1.0 / MAX_RATE_HZ) * 1000

#endif /* CONFIG_H_ */
