/*
 * stmdrum.h
 *
 *  Created on: 27/04/2017
 *      Author: jomorais
 */

#ifndef STMDRUM_H_
#define STMDRUM_H_
#include <stm32f10x.h>
#include <includes.h>
#include <kalman.h>
#include <adccontroller.h>
#include <midicontroller.h>
#include <lcd16x2.h>
#include <utils.h>
#include <gui.h>

void fsm_start ( void );
void fsm_set_state ( int fsm_state );
u8 fsm_get_state ( void );
void fsm_update ();
void finite_state_machine ( void );

void stmdrum_run ( void );
void stmdrum_midi_controller ( void );

#endif /* STMDRUM_H_ */
