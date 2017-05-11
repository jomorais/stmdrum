/*
 * kalman.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef KALMAN_H_
#define KALMAN_H_

#include <includes.h>
#include <config.h>
#include <attributes.h>

#define ADC_KALMAN_P 0.05728
#define ADC_KALMAN_Q 0.525
#define ADC_KALMAN_R 0.051233
#define ADC_KALMAN_K 0.10572799

typedef struct
{
		float q; //process noise covariance
		float r; //measurement noise covariance
		float x; //value
		float p; //estimation error covariance
		float k; //kalman gain
} kalman_state;

kalman_state adc_kalman_state[N_CHANNELS];

void kalman_init ( void );
void kalman_update ( u8 channel );

#endif /* KALMAN_H_ */
