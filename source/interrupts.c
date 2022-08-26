/*
 * systick.c
 *
 *  Created on: 24 Nov 2019
 *      Author: lxmi
 */

#include "MKL25Z4.h"
#include "debug.h"
#include "commonheader.h"
#include "LCD_4bit.h"
#include "init.h"

extern volatile int curr;
extern void display(Food f);
extern void Run();
int cnt = 0;
bool processDebounce(volatile Key *button) {

	if ((button->key == 1)) { //Key pressed at first sample
		++cnt;
		if (cnt == 5) { //after 300 ms

			button->key = 0;
			cnt = 0;
			return (button->debounce = 1);
		}

	}

	else if (button->debounce == 1) { //A button has been pushed and debounced
		button->debounce = 0; //reset
		//clearDebug();
		button->key = 0;

	}

	return 0;

}

void SysTick_Handler(void) {
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	toggleDebug();
	State_ecoca = State_ecoca_next;
	State_heater = State_heater_next;
	if (++count == 600000) {
		count = 0;
	}
	//minute = (short) count / 600.0;
	minute = count;

	if (State_ecoca == Browse) {
		if (processDebounce(&browse) == 1) {
			//update food id corresponding to displaynext item on food list
			State_ecoca_next = Browse;
			++curr;
			if (curr > 2) {
				curr = 0;
			}
			memset(&_FOOD, 0, sizeof(Food));
			memcpy(&_FOOD, &(FOOD_LIST[curr]), sizeof(Food)); //Update current food
			Clear_LCD();
			Set_Cursor(0U, 0U);
			char tm[20];
			memset(tm, 0, 20 * sizeof(char));
			sprintf(tm, "Brws-%s", _FOOD.name);
			Print_LCD(tm);
			memset(tm, 0, 20 * sizeof(char));
			Set_Cursor(0U, 1U);
			sprintf(tm, "OK to Confirm");
			Print_LCD(tm);

		} else if (processDebounce(&ok) == 1) {

			State_ecoca_next = run;
			//State_heater_next= rise;
			//change state heater to run
			//SysTick_Config(ms100);
			count = 0;
			minute = 0;
			TIM = _FOOD.t1;
			SP = 100;
			Clear_LCD();
			Set_Cursor(0U, 0U);
			char tm[20];
			memset(tm, 0, 20 * sizeof(char));
			sprintf(tm, "OK..warming", TIM);
			Print_LCD(tm);
			memset(tm, 0, 20 * sizeof(char));
			sprintf(tm, "%s- %d x.1s", _FOOD.name, TIM);
			Set_Cursor(0U, 1U);
			Print_LCD(tm);
			//char tm[8];
			//sprintf(tm, "%d mts",TIM);
			//Print_LCD(tm);

		}
	} else if (processDebounce(&stop) == 1)

	{
		//set duty cycle as 0
		//update display
		State_heater_next = rise;
		State_ecoca_next = Browse;
		State_ecoca = Browse;

		TIM = 60000;
		SP = SP_ROOM_T;

		char tm[20];
		memset(tm, 0, 20 * sizeof(char));
		Clear_LCD();
		sprintf(tm, "Brws-%s", _FOOD.name);
		Set_Cursor(0U, 0U);
		Print_LCD(tm);
		Set_Cursor(0U, 1U);
		sprintf(tm, "OK to Confirm");
		Print_LCD(tm);

	}

	/* minute debugger
	 if((minute %2)==0)
	 {
	 setDebug();
	 }

	 else if ((minute %2)==1)
	 {
	 clearDebug();
	 }
	 */

	return;

}
bool processIRQ(volatile Key *button) {

	if ((PORTD->ISFR & MASK(button->pin)) && button->key == 0) { //PORTD->ISFR & MASK(POS))  is high when a debounce is pressed from rest state
//toggleDebug();
		button->key = 1; //key pressed first time
		//setDebug();
		//toggleDebug();
		return 1;

	} //PORTD->ISFR & MASK(POS))  is high when a debounce is pressed from rest state
//	else if ((PORTD->ISFR & MASK(button->pin)) && button->double_check == 1) {
	else {
		button->key = 0;
		return 0;
	}
	return 0;
}

void PORTD_IRQHandler(void) {

// -----------------------

// clear pending interrupts

	if(processIRQ(&ok))
	{
		PORTD->ISFR = 0xffffffff;
		return;
	}
	if(processIRQ(&stop))
	{
		PORTD->ISFR = 0xffffffff;
		return;
	}
	if(processIRQ(&browse))
	{
		PORTD->ISFR = 0xffffffff;
		return;
	}
//rest state (debounce=0) and a switch press will trigger systick handler after 500ms wait

// clear status flags

	PORTD->ISFR = 0xffffffff;

// -----------------------
//TODO set pin DBG_ISR_POS LOW

// -----------------------
	return;
}
