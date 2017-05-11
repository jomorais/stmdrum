/*
 * midicontroller.h
 *
 *  Created on: 28/03/2017
 *      Author: jomorais
 */

#ifndef MIDICONTROLLER_H_
#define MIDICONTROLLER_H_
#include <includes.h>
#include <attributes.h>
#include <protocol.h>
#include <utils.h>
#include <adccontroller.h>
#include <kalman.h>

#define NOT_ACTIVE_NOTE 0
#define ACTIVE_NOTE     1

void midicontroller_init ( void );
void midicontroller_update ( void );

#endif /* MIDICONTROLLER_H_ */
