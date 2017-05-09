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

/* FSM STATES */

void gui_init ( void );
void gui_update ( void );
void gui_next_page (void);
void gui_previous_page(void);
void gui_show_page(u8 page);

#endif /* GUI_H_ */
