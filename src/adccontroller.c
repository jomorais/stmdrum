/*
 * adccontroller.c
 *
 *  Created on: 27/03/2017
 *      Author: jomorais
 */

#include <adccontroller.h>

void adccontroller_init(void) {
	//--Enable ADC1 and GPIOA--
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	//==Configure ADC pins (PA0 -> Channel 0 to PA7 -> Channel 7) as analog inputs==
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//==Configure ADC pins (PB0 -> Channel 8 to PB1 -> Channel 9) as analog inputs==
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//==Configure ADC pins (PC0 -> Channel 10 to PC5 -> Channel 15) as analog inputs==
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//ADC1 configuration
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	//We will convert multiple channels
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//select continuous conversion mode
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //!
	//select no external triggering
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	//right 12-bit data alignment in ADC data register
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//8 channels conversion
	ADC_InitStructure.ADC_NbrOfChannel = 15;
	//load structure values to control and status registers
	ADC_Init(ADC1, &ADC_InitStructure);
	//Enable ADC1
	ADC_Cmd(ADC1, ENABLE);
	//Enable ADC1 reset calibration register
	ADC_ResetCalibration(ADC1);
	//Check the end of ADC1 reset calibration register
	while (ADC_GetResetCalibrationStatus(ADC1));
	//Start ADC1 calibration
	ADC_StartCalibration(ADC1);
	//Check the end of ADC1 calibration
	while (ADC_GetCalibrationStatus(ADC1));
	adccontroller_update_all();
}

u16 adccontroller_read_channel(u8 channel)
{
	u16 adc;
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
	// Start the conversion
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	// Wait until conversion completion
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	// Get the conversion value
	adc = ADC_GetConversionValue(ADC1);
	return adc;
}

void adccontroller_update_all(void)
{
	u8 channel;
	for(channel = 0 ; channel < N_CHANNELS; channel++)
		adc_raw[channel] = adccontroller_read_channel(channel) * GAIN;
}


