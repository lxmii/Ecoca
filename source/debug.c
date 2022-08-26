/*
 * debug.c
 *
 *  Created on: 23 Apr 2019
 *      Author: lxmi
 */

#ifndef DEBUG_C_
#define DEBUG_C_
#include "debug.h"
void initDebug(void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[DBG] |= PORT_PCR_MUX(01U);
	/* Setting Switch to be an output, forcing corresponding bit to be 0 */
	PTD->PDDR |= (GPIO_PDDR_PDD(MASK(DBG)));
	PTD->PCOR|=GPIO_PCOR_PTCO(MASK(DBG));

}
void toggleDebug(void) //Toggles voltage level at // PTD6
{
	//PTD->PCOR|=GPIO_PCOR_PTCO((MASK(DBG)));
	PTD->PTOR|=GPIO_PTOR_PTTO(MASK(DBG));
	}
void clearDebug(void)
{

	PTD->PCOR|=GPIO_PCOR_PTCO(MASK(DBG));
	}

void setDebug(void) //Toggles voltage level at // PTD6
{
	//PTD->PCOR|=GPIO_PCOR_PTCO((MASK(DBG)));
	PTD->PSOR|=GPIO_PSOR_PTSO (MASK(DBG));
	}
#endif /* DEBUG_C_ */
