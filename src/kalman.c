/*
 * kalman.c
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */


#include <kalman.h>

void kalman_init ( void )
{
	uint8_t channel;
	// init kalman terms
	for ( channel = 0; channel < N_CHANNELS ; channel++ )
	{
		adc_kalman_state[channel].q = ADC_KALMAN_Q;
		adc_kalman_state[channel].r = ADC_KALMAN_R;
		adc_kalman_state[channel].p = ADC_KALMAN_P;
		adc_kalman_state[channel].x = adc_raw[channel];
	}
}

void kalman_update ( void )
{
	uint8_t channel;
	for ( channel = 0; channel < N_CHANNELS ; channel++ )
	{
		//prediction update
		adc_kalman_state[channel].p = adc_kalman_state[channel].p + adc_kalman_state[channel].q;
		//measurement update
		adc_kalman_state[channel].k = adc_kalman_state[channel].p / ( adc_kalman_state[channel].p + adc_kalman_state[channel].r );
		adc_kalman_state[channel].x = adc_kalman_state[channel].x + adc_kalman_state[channel].k * ( adc_raw[channel] - adc_kalman_state[channel].x );
		adc_smooth[channel] = adc_kalman_state[channel].x;
		adc_kalman_state[channel].p = ( 1 - adc_kalman_state[channel].k ) * adc_kalman_state[channel].p;
	}
}
