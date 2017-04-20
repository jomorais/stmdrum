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
#include <lcd16x2.h>
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
	utils_systick_init();
	adccontroller_init();
	kalman_init();
	midicontroller_init();
	lcd16x2_init();
	main_tick = millis();

	char adc[16];

	for(;;)
	{
		if( (millis() - main_tick) > TICK_RATE_MS )
		{
			bzero(adc,sizeof(adc));
			int size = sprintf(adc, "A4:%d", adc_smooth[CHANNEL_4]);
			lcd16x2_write_string(0,0,adc, size);
			bzero(adc,sizeof(adc));
			size = sprintf(adc, "A5:%d", adc_smooth[CHANNEL_5]);
			lcd16x2_write_string(0,1,adc, size);
			bzero(adc,sizeof(adc));
			size = sprintf(adc, "A6:%d", adc_smooth[CHANNEL_6]);
			lcd16x2_write_string(8,0,adc, size);
			bzero(adc,sizeof(adc));
			size = sprintf(adc, "A7:%d", adc_smooth[CHANNEL_7]);
			lcd16x2_write_string(8,1,adc, size);
			kalman_update();
			midicontroller_update();
			main_tick = millis();
		}


		lcd16x2_update();
	}
}
