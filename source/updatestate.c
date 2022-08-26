/*
 * updatestate.c
 *
 *  Created on: 29 Nov 2019
 *      Author: lxmi
 */
#include "commonheader.h"
#include "LCD_4bit.h"
#include "init.h"

extern volatile enum state_heater State_heater;
extern volatile enum state_heater State_heater_next;
extern volatile enum state_ecoca State_ecoca;
extern volatile enum state_ecoca State_ecoca_next;
void updateHeaterState(void);
volatile unsigned short SP;
void updateHeaterState(void) {

	if (State_ecoca == run) {

		if ((minute == TIM)) { //when timer goes off
			if (State_heater == rise) {
				count = 0;
				minute = 0;
				State_heater_next = steady;
				SP = _FOOD.sp;
				TIM = _FOOD.t2;
				Clear_LCD();
				Set_Cursor(0U, 0U);
				char tm[20];
				memset(tm, 0, 20 * sizeof(char));
				sprintf(tm, "Steady", TIM);
				Print_LCD(tm);
				Set_Cursor(0U, 1U);



				memset(tm, 0, 20 * sizeof(char));
				sprintf(tm, "%s- %d x.1s", _FOOD.name,TIM );
				Set_Cursor(0U, 1U);
				Print_LCD(tm);
			}

			else if (State_heater == steady) {
				State_heater_next = fall;
				count = 0;
				minute = 0;
				SP = SP_ROOM_T;
				TIM = _FOOD.t3;
				Clear_LCD();
				Set_Cursor(0U, 0U);
				char tm[20];
				memset(tm, 0, 20 * sizeof(char));
				sprintf(tm, "Falling", TIM);
				Print_LCD(tm);
				Set_Cursor(0U, 1U);
				memset(tm, 0, 20 * sizeof(char));
				sprintf(tm, "%s- %d x.1s", _FOOD.name,TIM );
				Set_Cursor(0U, 1U);
				Print_LCD(tm);
			} else if (State_heater == fall) {
				State_ecoca_next = Browse;
				State_heater_next = rise;
				SP = SP_ROOM_T;
				TIM = 60000;
				Clear_LCD();
				Set_Cursor(0U, 0U);
				char tm[20];
				memset(tm, 0, 20 * sizeof(char));
				sprintf(tm, "Brws-%s", _FOOD.name);
				Set_Cursor(0U, 0U);
				Print_LCD(tm);
				Set_Cursor(0U, 1U);
				memset(tm, 0, 20 * sizeof(char));
				sprintf(tm, "OK to Confirm");
				Print_LCD(tm);

			}
		}

	} else {

		SP = SP_ROOM_T;

	}

}

/**Activate is a function that revieves the state along with the set point and
 *
 */
