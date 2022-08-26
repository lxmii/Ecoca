#include "pwm.h"
#define GREEN 2U  //FTM0_CH2
#define RED	0U   //FTM0_CH0
#define BLUE 5U	//FTM0_CH5
#define BUZZER 1U //FTM0_CH1 PTD1 o/p

/**
 *@brief function to set duty cycle
 *@param period integer representing duty cycle in %
 *pins should be given in an array max 6 pins allowed, end the array with -1
 *
 */

void initPWM(int pwmnr, int *pins, unsigned short period) {
	switch (pwmnr) {

	case 0:
		SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //TPM0 lies on port D

		/* FTM0 is mux func 4 */

		for (int i = 0; i < 6; ++i) {
			if (pins[i] == -1) {
				break;
			}
			PORTD->PCR[pins[i]] = (4 << 8);
		}
		SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1)|SIM_SOPT2_PLLFLLSEL_MASK; //MCGFLLCLK or MCGPLLCLK/2 16th bit chooses MCGPLLCLK/2
		TPM0->MOD = 7500-1;//Gives 20ms
		TPM0->CONF = (3 << 6);

		/* Now setup PWM channel 1 - connected to PD1* bit *3 & 5 hi */
		for (int i = 0; i < 6; ++i) {
			if (pins[i] == -1) {
				break;
			}
			TPM0->CONTROLS[pins[i]].CnSC =TPM_CnSC_ELSB(1)|TPM_CnSC_ELSA(0)|TPM_CnSC_MSB(1)|TPM_CnSC_MSA(0);
			TPM0->CONTROLS[pins[i]].CnV = 0; //0 % dc
		}
		/*50% DC*/

		TPM0->SC |= TPM_SC_CMOD(1U)|TPM_SC_PS(0);
		break;

	case 1:
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //Lies on port B
		SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
		for (int i = 0; i < 6; ++i) {
			if (pins[i] == -1) {
				break;
			}
			PORTB->PCR[pins[i]] = (3 << 8);
		}

		SIM->SOPT2 |= SIM_SOPT2_TPMSRC(5); //48Mhz

		TPM1->MOD =period-1;//Gives 20ms
		TPM1->CONF = (3 << 6);

		for (int i = 0; i < 6; ++i) {
			if (pins[i] == -1) {
				break;
			}
			TPM1->CONTROLS[pins[i]].CnSC =TPM_CnSC_ELSB(1)|TPM_CnSC_ELSA(0)|TPM_CnSC_MSB(1)|TPM_CnSC_MSA(0);
			TPM1->CONTROLS[pins[i]].CnV = period*10/100; //10 % dc
		}
		/*50% DC*/

		TPM1->SC |= TPM_SC_CMOD(1U)|TPM_SC_PS(7);//Prescaler makes 48Mhz/128 to 960kHz pwm
		break;

	}

}
//duty cycle in percentage
void setDutycycle(int port, unsigned short *dc, int *pins) {
	unsigned short mod;
	/* read modulus / period register*/
	switch (port) {

	case 0:
		mod = TPM0->MOD;
		for (int i = 0; i < 6; ++i) {
			if (pins[i] == -1) {
				break;
			}
			TPM0->CONTROLS[pins[i]].CnV = TPM_CnV_VAL(dc[i]);
		}
		break;
	case 1:
		mod = TPM1->MOD;
		for (int i = 0; i < 6; ++i) {
			if (pins[i] == -1) {
				break;
			}
			TPM1->CONTROLS[pins[i]].CnV = TPM_CnV_VAL(dc[i]);
		}
		break;

	}

}
