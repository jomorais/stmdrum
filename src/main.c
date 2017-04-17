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
	adccontroller_init();
	kalman_init();
	midicontroller_init();
	lcd16x2_init();
	lcd16x2_clear_buffer();
	lcd16x2_write_string(0,0,"STM-DRUMM", 9);
	lcd16x2_write_string(0,1,"ADC: 1913", 9);

	char adc[16];


	//Enable DMA1 Channel transfer
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//Start ADC1 Software Conversion
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	//wait for DMA complete
	while (!status){};
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);

	for(;;)
	{
		int size = sprintf(adc, "ADC0: %d", adc_raw[CHANNEL_0]);
		lcd16x2_write_string(0,0,adc, size);
		kalman_update();
		midicontroller_update();

		lcd16x2_update();
	}
}
