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

#define INIT_SCREEN 	0
#define MENU_SCREEN 	1
#define MENU_PAGE_0	 	0
#define MENU_PAGE_1 	1
#define MENU_PAGE_2	 	2
#define MENU_PAGE_3 	3

typedef struct
{

} menu_controller_t;

/* FSM STATES */
#define INIT 			    							0

void gui_init ( void );
void gui_update ( void );
void gui_fsm_late_update ( void );
void gui_fsm_start ( void );
void gui_fsm_set_state ( int fsm_state );
u8 gui_fsm_get_state ( void );
void gui_fsm_update ();
void gui_fsm_states ( void );

#endif /* GUI_H_ */
