/*
 * pwm.h
 *
 *  Created on: 7 Nov 2018
 *      Author: lxmi
 */

#ifndef PWM_H_
#define PWM_H_
/**
 * @file pwm.h
 * @author Poornima Lakshmi
 * @param integer representing duty cycle in %
 *
 *
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"




void initPWM(int pwmnr, int *pins,  unsigned short period);
void setDutycycle(int port, unsigned short *dc, int *pins);
#endif /* PWM_H_ */
