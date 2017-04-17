/*
 * lcd16x2.c
 *
 *  Created on: 17/04/2017
 *      Author: jomorais
 */

#include <lcd16x2.h>

void lcd16x2_init_hw ( void )
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void lcd16x2_init ( void )
{
	lcd16x2_init_hw();
	delay_ms(15);
	lcd16x2_write_cmd( 0x38 );
	delay_ms(1);
	lcd16x2_write_cmd( 0x38 );
	delay_us(100);
	lcd16x2_write_cmd( 0x38 );
	lcd16x2_write_cmd( 0x28 );
	lcd16x2_write_cmd( 0x28 );
	lcd16x2_write_cmd( 0x0C );
	lcd16x2_clear();
	lcd16x2_write_cmd( 0x06 );
}

void lcd16x2_lcd_strobe( void )
{
	GPIO_WriteBit(LCD_PORT_CONTROL, LCD_EN, 1);  // EN = 1
	delay_us(1);
	GPIO_WriteBit(LCD_PORT_CONTROL, LCD_EN, 0);  // EN = 0
}


void lcd16x2_write_bus( unsigned char d )
{
	GPIO_WriteBit(LCD_PORT_DATA, LCD_D0, d & 0x01);  // LCD_B0
	GPIO_WriteBit(LCD_PORT_DATA, LCD_D1, d & 0x02);  // LCD_B1
	GPIO_WriteBit(LCD_PORT_DATA, LCD_D2, d & 0x04);  // LCD_B2
	GPIO_WriteBit(LCD_PORT_DATA, LCD_D3, d & 0x08);  // LCD_B3
}

void lcd16x2_write_cmd( unsigned char cmd )
{
	GPIO_WriteBit(LCD_PORT_CONTROL, LCD_RS, 0);  // RS = 0 (command)
	delay_us(53);
	lcd16x2_write_bus( cmd >> 4);
	lcd16x2_lcd_strobe();
	lcd16x2_write_bus( cmd );
	lcd16x2_lcd_strobe();
}

void lcd16x2_write_data( unsigned char data )
{
	GPIO_WriteBit(LCD_PORT_CONTROL, LCD_RS, 1);  // RS = 1 (data)
	delay_us(53);
	lcd16x2_write_bus( data >> 4);
	lcd16x2_lcd_strobe();
	lcd16x2_write_bus( data );
	lcd16x2_lcd_strobe();
}

void lcd16x2_clear ( void )
{
	lcd16x2_write_cmd( 0x01 );
	delay_ms(2);
}

void lcd16x2_write_string ( const char * s , u16 length )
{
	lcd16x2_clear();
	int s_idx = 0;
	lcd16x2_write_cmd( 0x80 );
	for ( s_idx = 0 ; s_idx < length - 1; s_idx++ )
	{
		lcd16x2_write_data( s[ s_idx ] );
		if( s_idx == 16 )
			lcd16x2_write_cmd( 0xC0 );
	}
}
