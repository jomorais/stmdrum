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

#define N_PAGES			10

typedef struct
{
	char title[16];
	u8 page;
	void *attribute;
	float step;
} menu_page_t;


typedef struct
{
	u8 current_page;
	menu_page_t menu_page[N_PAGES];
} menu_controller_t;

menu_controller_t menu_controller;

/* FSM STATES */

void gui_init ( void );
void gui_update ( void );
void gui_fsm_late_update ( void );
void gui_fsm_start ( void );
void gui_fsm_set_state ( int fsm_state );
u8 gui_fsm_get_state ( void );
void gui_fsm_update ();
void gui_fsm_states ( void );

#endif /* GUI_H_ */
