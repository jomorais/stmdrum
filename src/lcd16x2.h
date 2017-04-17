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
#define LCD_D0 	GPIO_Pin_6
#define LCD_D1 	GPIO_Pin_7
#define LCD_D2 	GPIO_Pin_8
#define LCD_D3 	GPIO_Pin_9

void lcd16x2_init_hw( void );
void lcd16x2_init ( void );
void lcd16x2_write_cmd( unsigned char cmd );
void lcd16x2_write_data( unsigned char data );
void lcd16x2_write_string ( const char * s , u16 length );
void lcd16x2_clear ( void );

#endif /* LCD16X2_H_ */
