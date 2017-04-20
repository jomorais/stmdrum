/*
 * lcd16x2.h
 *
 *  Created on: 17/04/2017
 *      Author: jomorais
 */

#ifndef LCD16X2_H_
#define LCD16X2_H_

#include <stm32f10x.h>
#include <includes.h>
#include <utils.h>

#define LCD_PORT_CONTROL 	GPIOA
#define LCD_EN 	GPIO_Pin_8
#define LCD_RS 	GPIO_Pin_11

#define LCD_PORT_DATA 		GPIOC
#define LCD_DB4 	GPIO_Pin_9
#define LCD_DB5 	GPIO_Pin_8
#define LCD_DB6 	GPIO_Pin_7
#define LCD_DB7 	GPIO_Pin_6

#define LCD_JUMP_LINE_1 0x80
#define LCD_JUMP_LINE_2 0xC0
#define LCD_JUMP_LINE_3 0x90
#define LCD_JUMP_LINE_4 0xD0
#define LCD_FRAMERATE 5 // Hz

#define N_LINES 	2
#define N_COLUMN 	16
#define N_CHARACTERS N_COLUMN * N_LINES
char LCD_BUFFER[N_LINES][N_COLUMN];
uint32_t lcd_tick;


void lcd16x2_init_hw( void );
void lcd16x2_init ( void );
void lcd16x2_write_cmd( unsigned char cmd );
void lcd16x2_write_data( unsigned char data );
void lcd16x2_write_string ( u8 column, u8 line, const char * s , u8 length );
void lcd16x2_clear ( void );
void lcd16x2_clear_buffer ( void );
void lcd16x2_update( void );

#endif /* LCD16X2_H_ */
