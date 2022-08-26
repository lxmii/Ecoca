/*
 * debug.h
 *
 *  Created on: 23 Apr 2019
 *      Author: lxmi
 */

#ifndef DEBUG_H_
#define DEBUG_H_



#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#define DBG 6U // PTD6
#define MASK(x) (1U<<(x))
extern void initDebug(void);
extern void clearDebug(void);
extern void setDebug(void);
extern void toggleDebug(void);
#endif /* DEBUG_H_ */
