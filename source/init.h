/*
 * init.h
 *
 *  Created on: 20 Nov 2019
 *      Author: lxmi
 */

#ifndef INIT_H_
#define INIT_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "commonheader.h"
#include "systick.h"
#include "LCD_4bit.h"

#define RICE 0U
#define BEANS 1U
#define WATER 2U
#define MAXADC 6530 //Max ADC value

typedef struct key {
	volatile bool key, debounce;
	int pin;

} Key;

typedef struct food {
	int id;
	char name[20];
	int t1, t2,t3;
	double sp;
} Food;
extern Food FOOD_LIST[3];

extern Food _FOOD; //Main food selected

extern void initFood(Food* st, int id, char *name, const int *timers,
		double sp);
extern volatile Key ok, stop, browse;

extern void toggleDebug(void);
void debounced(void);
extern int pins0[6];
extern void init();
extern volatile int deb;
extern volatile int count;
extern volatile short minute;
extern volatile int TIM;
extern volatile enum state_heater State_heater;
extern volatile enum state_heater State_heater_next;
extern volatile enum state_ecoca State_ecoca;
extern volatile enum state_ecoca State_ecoca_next;
extern unsigned short period0;
extern unsigned short periodservo;
extern volatile int curr;
//extern int dc0[5] ;
extern volatile unsigned short SP;
extern int pins1[2];
extern unsigned short period1;
extern void initTempIP(void);
extern void initHeaterPWM(void);

extern void initDebug(void);
extern void ctrlR(void);
extern void updateState(void);

#endif /* INIT_H_ */
