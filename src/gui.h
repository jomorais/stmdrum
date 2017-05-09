/*
 * menu.h
 *
 *  Created on: 17/04/2017
 *      Author: jomorais
 */

#ifndef GUI_H_
#define GUI_H_
#include <lcd16x2.h>
#include <settings.h>
#include <attributes.h>

#define N_PAGES			8

#define PAGE_EXIT		0
#define PAGE_1			1
#define PAGE_2			2
#define PAGE_3			3
#define PAGE_4			4
#define PAGE_5			5
#define PAGE_6			6
#define PAGE_7			7
#define PAGE_8			8
#define RUN				9
#define ON_MENU			10

#define EDIT_MODE		1

typedef struct
{
	char title[16];
	u8 page;
	void *attribute;
	u16 step;
	u8 data_type;
	u16 max;
	u16 min;
} menu_page_t;


typedef struct
{
	int current_page;
	u8 editmode;
	u8 menu_state;
	menu_page_t menu_page[N_PAGES + 1];
} menu_controller_t;

menu_controller_t menu_controller;

/* FSM STATES */

void gui_init ( void );
void gui_update ( void );
void gui_next_page (void);
void gui_previous_page(void);
void gui_show_page(u8 page);

#endif /* GUI_H_ */
