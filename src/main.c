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
	utils_systick_init(1000);
	lcd16x2_init();
	adccontroller_init();
	kalman_init();
	midicontroller_init();

	for(;;)
	{
		kalman_update();
		midicontroller_update();
	}
}
