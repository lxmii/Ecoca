/*
 * commonheader.h
 *
 *  Created on: 19 Nov 2019
 *      Author: lxmi
 */

#ifndef COMMONHEADER_H_
#define COMMONHEADER_H_



#include "adc.h"
#include "pwm.h"



#define MASK(x) (1U<<(x))

#define HEATER 1U //FTM1_CH1  PTB1 o/p to heater
#define TMPS 0U //PTB0	Analog in from tempSensor
#define BRWS 3U // (PTD3 i/p) switch ip browse
#define OK 4U // (PTD4 i/p) switch ip
#define STOP 5U // (PTD5 i/p) switch ip
#define SP_ROOM_T 25 //room temperature

#define P1 20000000
#define P2 40000000
#define P3 60000000
#define P4 80000000

//#define ticks 24000 // 2test
#define ms500 24000000 // 24000000 500ms (48MHz clock) interrupts
//#define pw    480 // test
#define ms10    480000 // 480000 Pulsewidth of a debounced sg 1/100 of a second or 10ms interrupts
#define ms50	2400000
#define ms100 4800000 //100ms interrupts
#define ms2000 96000000 //2s interrupts
#define PB	1U
#define PD	0U
#define M	3//number of food items
#define N	10
#define R_ADC 10000
extern const int TIMER_RICE[3];
extern const int TIMER_WATER[3];
extern const int TIMER_BEANS[3];


extern int pins1[2];

enum state_heater {
	rise, steady, fall
};

enum state_ecoca {
	run, Browse
};



extern volatile unsigned short SP;
extern void ctrlR(void);
extern void initswitch(int);
extern void debounced(void) ;
extern volatile bool double_check;
extern volatile short minute;
extern volatile int deb;
extern volatile int count;
extern volatile bool debounce;
extern volatile bool key_browse ;
extern volatile bool key_ok;
extern volatile bool key_STOP;
extern volatile enum state State;
extern volatile enum state State_next;
extern unsigned short period0 ;
extern unsigned short periodservo ;
extern float prop;
extern float integral;

#endif /* COMMONHEADER_H_ */
