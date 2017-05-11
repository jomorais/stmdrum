/*
 * lcd16x2.c
 *
 *  Created on: 17/04/2017
 *      Author: jomorais
 */

#include <lcd16x2.h>

void lcd16x2_init_hw ( void )
{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC , ENABLE );

		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_StructInit( &GPIO_InitStructure );
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init( GPIOC , &GPIO_InitStructure );

		GPIO_StructInit( &GPIO_InitStructure );
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init( GPIOA , &GPIO_InitStructure );
}

void lcd16x2_init ( void )
{
		lcd16x2_init_hw();
		delay_ms( 30 );
		lcd16x2_write_cmd( 0x33 );
		delay_ms( 5 );
		lcd16x2_write_cmd( 0x32 );
		delay_us( 100 );
		lcd16x2_write_cmd( 0x28 );
		delay_ms( 5 );
		lcd16x2_write_cmd( 0x0C );
		delay_ms( 5 );
		memset( LCD_BUFFER , ' ' , sizeof ( LCD_BUFFER ) );
		lcd_tick = millis();
}

void lcd16x2_lcd_strobe ( void )
{
		GPIO_WriteBit( LCD_PORT_CONTROL , LCD_EN , 1 );  // EN = 1
		delay_us( 40 );
		GPIO_WriteBit( LCD_PORT_CONTROL , LCD_EN , 0 );  // EN = 0
}

void lcd16x2_write_bus ( unsigned char d )
{
		GPIO_WriteBit( LCD_PORT_DATA , LCD_DB4 , d & 0x01 );  // LCD_B0
		GPIO_WriteBit( LCD_PORT_DATA , LCD_DB5 , d & 0x02 );  // LCD_B1
		GPIO_WriteBit( LCD_PORT_DATA , LCD_DB6 , d & 0x04 );  // LCD_B2
		GPIO_WriteBit( LCD_PORT_DATA , LCD_DB7 , d & 0x08 );  // LCD_B3
}

void lcd16x2_write_cmd ( unsigned char cmd )
{
		GPIO_WriteBit( LCD_PORT_CONTROL , LCD_RS , 0 );  // RS = 0 (command)
		delay_us( 60 );
		lcd16x2_write_bus( cmd >> 4 );
		lcd16x2_lcd_strobe();
		lcd16x2_write_bus( cmd );
		lcd16x2_lcd_strobe();
}

void lcd16x2_write_data ( unsigned char data )
{
		GPIO_WriteBit( LCD_PORT_CONTROL , LCD_RS , 1 );  // RS = 1 (data)
		delay_us( 40 );
		lcd16x2_write_bus( data >> 4 );
		lcd16x2_lcd_strobe();
		lcd16x2_write_bus( data );
		lcd16x2_lcd_strobe();
}

void lcd16x2_clear ( void )
{
		lcd16x2_write_cmd( 0x01 );
		delay_ms( 2 );
}

void lcd16x2_clear_buffer ( void )
{
		memset( LCD_BUFFER , ' ' , sizeof ( LCD_BUFFER ) );
}

void lcd16x2_update ( void )
{
		if ( (( millis() - lcd_tick ) > ( (float) ( 1.0 / LCD_FRAMERATE ) * 1000 )) && (lcd_update_needed == 1) )
		{
				lcd_tick = millis();
				lcd16x2_clear();
				int s_idx_column = 0;
				int s_idx_line = 0;
				lcd16x2_write_cmd( LCD_JUMP_LINE_1 );
				for ( s_idx_line = 0; s_idx_line < N_LINES ; s_idx_line++ )
				{
						for ( s_idx_column = 0; s_idx_column < N_COLUMN - 1 ; s_idx_column++ )
								lcd16x2_write_data( LCD_BUFFER[s_idx_line][s_idx_column] );
						if ( s_idx_line == 0 )
								lcd16x2_write_cmd( LCD_JUMP_LINE_2 );
						if ( s_idx_line == 1 )
								lcd16x2_write_cmd( LCD_JUMP_LINE_3 );
						if ( s_idx_line == 2 )
								lcd16x2_write_cmd( LCD_JUMP_LINE_4 );
				}
				lcd_update_needed = 0;
		}
}

void lcd16x2_write_string ( u8 column , u8 line , const char * s , u8 length )
{
		if ( column < N_COLUMN && line < N_LINES )
		{
				lcd_update_needed = 1;
				u8 idx = 0;
				for ( idx = 0; idx < length ; idx++ )
						LCD_BUFFER[line][column + idx] = s[idx];
		}
}

