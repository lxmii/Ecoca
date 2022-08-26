/*
 * controller.c
 *
 *  Created on: 19 Nov 2019
 *      Author: lxmi
 */

#ifndef CONTROLLER_C_
#define CONTROLLER_C_
#include "commonheader.h"
#include <math.h>
#include "init.h"
#include "LCD_4bit.h"

// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer
// but is more 'smooth'
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
unsigned short dc;
unsigned short value;
float prop;
float integral;
short avg;
unsigned short period1 = 375000 * (0.020);
int pins1[2] = { HEATER, -1 };

void initTempIP(void)

{
	adcInit(TMPS);

}
void initHeaterPWM() //FTM1_CH1-->Port=1, channel=1--> Pin= 1, ALT= 3
{
	initPWM(1, pins1, period1);

}
void ctrlR(void) {

	value = adcRead(TMPS);

	double R_t;
	R_t= (65535.00 /value);
	R_t=R_t-1;
	R_t*=R_ADC;
	float steinhart, error;
	steinhart = R_t / THERMISTORNOMINAL;     // (R/Ro)
	steinhart = log(steinhart);                  // ln(R/Ro)
	steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
	steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
	steinhart = 1.0 / steinhart;                 // Invert
	steinhart -= 273.15;                         // convert to C

	error = SP - steinhart;
	float temp;
	/*if (error > 0) {

	 prop = (1 / 5) * error;
	 if (integral += error > 2) {
	 integral = 0; //preventing integral wind up
	 }
	 temp = prop + integral * 0.1;

	 } else {
	 temp = 0;
	 }*/
	//Clear_LCD();

//	Set_Cursor(0U, 0U);

	if(State_ecoca==run)
	{	Set_Cursor(11U, 0U);
		char tm[20];
		memset(tm, 0, 20 * sizeof(char));
		sprintf(tm, "T%d", (int)steinhart);
		Print_LCD(tm);
		//printf("%d\n",(int)steinhart);
	}



	switch (SP) {
	case (100):
		temp = 19;
		break;
	case (60):
		temp = 2;
		break;
	case (80):
		temp = 2;
		break;
	case (SP_ROOM_T):
		temp = -1;
		break;
		//printf("%d\n", dc);
	}
	dc = temp * 15000 / 43 + 9000 / 43;
	setDutycycle(1, &dc, pins1);

}

#endif /* CONTROLLER_C_ */
/*
 *
 * 	//adc_low should give 6 adc_high should give 15

 unsigned short sp, onPer, d_onPer;//6mS duty cycle

 onPer= value*15805479649280/90070618157875213+ 40531711781710438465/90070618157875213;//Converts adcin value to on period in Ms

 d_onPer= (sp-onPer);
 //dc= (d_onPer+sp)*15000/43+9000/43;//converts onPer in mS to PWM mod value
 //printf("%d\n", dc);
 dc= (onPer)*15000/43+9000/43;//converts onPer in mS to PWM mod value
 setDutycycle(1, &dc, pins1);
 */

