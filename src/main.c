/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include <stm32f10x.h>
#include <includes.h>
#include <kalman.h>
#include <adccontroller.h>
#include <midicontroller.h>
#include <utils.h>
			

void send_adc(u8 channel, u16 adc_raw, u16 adc_smooth)
{
	char msg[64];
	bzero(msg,sizeof(msg));
	int size = sprintf(msg,"\rADC%d -> RAW = %d | SMOOTH: %d\r\n",channel, adc_raw, adc_smooth);
	protocol_raw_send(msg, size);
}

int main(void)
{
	utils_systick_init(1000);
	adccontroller_init();
	kalman_init();
	midicontroller_init();

	for(;;)
	{
		adccontroller_update_all();
		kalman_update();
		midicontroller_update();
		/*
		int adc_channel;
		for(adc_channel = 4; adc_channel < 8; adc_channel++)
		{
			send_adc(adc_channel, adc_raw[adc_channel],adc_smooth[adc_channel]);
		}

		_delay_ms(100);
		*/
	}
}
