/*
 * adc.c
 *
 *  Created on: 28 Aug 2018
 *      Author: au263437
 */

#include "adc.h"

/* @file adc.c
 * @author morten@ase.au.dk
 * @date oct 17 2018
 * @param channel number 0-5, corresponding to available pins on the KL25Z board
 * @brief this function initalizes ADC0, one of the two converters on the chip
 *
 * for channel map, see ch 28.3.1
 * A0 = ADC0_SE8 - PTB0 - ADCH = 01000
 * A1 = ADC0_SE9 - PTB1 - ADCH = 01002
 * A2 = ADC0_SE12 - PTB2 - ADCH = 01100
 * A3 = ADC0_SE13 - PTB3 - ADCH = 01101
 * A4 = ADC0_SE11 - PTC2 - ADCH = 01011
 * A5 = ADC0_SE15 - PTC1 - ADCH = 01111
 * Temperature sensor - 11010
 * KL25P80M48SF0RM - chapter 28 describes the ADC, and corresponding registers
 *
 * */
void adcInit(int channel) {
	/* 1: is the channel number valid ? */

	/* 2:enable clock for port B & C */
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;
	SIM->SCGC6 |= SIM_SCGC6_ADC0(1); //Power to ADC

	/* 3: enable clock (power) to the ADC*/

	/* 4: setup the converter - ADC0 ADC0_CFG1
	 * Low power config  ADLPC 1
	 * long sample time ADLSMP 1
	 * 16 Bit SE MODE 11
	 * Bus clk input   ADICLK 00 */ //done
	ADC0->CFG1 &= ~(ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADLSMP_MASK
			| ADC_CFG1_MODE_MASK | ADC_CFG1_ADICLK_MASK);
	ADC0->CFG1 |=
			ADC_CFG1_ADLPC(
					1)|ADC_CFG1_ADLSMP(1)|ADC_CFG1_MODE(3)|ADC_CFG1_ADICLK(1)|ADC_CFG1_ADIV(1);
	/* 5: Software trigger ADC0_SC2 ADTRG 0
	 * compare func. disabled ACFE 0
	 * DMA dsabled DMAE 0
	 * Voltgae ref - VREFH and VREFL   REFSEL 00 */ //done
/*	ADC0->CFG2 &= ~(ADC_CFG2_ADACKEN_MASK | ADC_CFG2_ADHSC_MASK
			| ADC_CFG2_MUXSEL_MASK);
	ADC0->CFG2 |= ADC_CFG2_ADACKEN(
			0) | ADC_CFG2_ADHSC(0) | ADC_CFG2_MUXSEL(0);
	ADC0->SC2 &= ~(ADC_SC2_ADTRG_MASK | ADC_SC2_ACFE_MASK | ADC_SC2_REFSEL_MASK
			| ADC_SC2_DMAEN_MASK);
	ADC0->SC2 |= ADC_SC2_ADTRG(
			0) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(00);*/

	/* 6: Setup port control register to analog funcitons, correspodingly
	 * ADC_CFG2
	 * for ADC functionality, PINMUX bits 8-11 must be set to 000,
	 * MUX
	 * all the digital functions, drive strength, filters etc are disables*/ //done
	switch (channel) {
	case 0:


		PORTB->PCR[0] &= ~(PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK
				| PORT_PCR_PFE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK
				| PORT_PCR_SRE_MASK);
		PORTB->PCR[0] |=
				PORT_PCR_MUX(
						0)|PORT_PCR_DSE(0)|PORT_PCR_PFE(0)|PORT_PCR_PE(1)|PORT_PCR_PS(1)|PORT_PCR_SRE(0);

		break;
	case 1:

		PORTB->PCR[1] &= ~(PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK
				| PORT_PCR_PFE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK
				| PORT_PCR_SRE_MASK);
		PORTB->PCR[1] |=
				PORT_PCR_MUX(
						0)|PORT_PCR_DSE(0)|PORT_PCR_PFE(0)|PORT_PCR_PE(1)|PORT_PCR_PS(1)|PORT_PCR_SRE(0);
		break;
	case 2:


		PORTB->PCR[2] &= ~(PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK
				| PORT_PCR_PFE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK
				| PORT_PCR_SRE_MASK);
		PORTB->PCR[2] |=
				PORT_PCR_MUX(
						0)|PORT_PCR_DSE(0)|PORT_PCR_PFE(0)|PORT_PCR_PE(1)|PORT_PCR_PS(1)|PORT_PCR_SRE(0);
		break;
	case 3:

		PORTB->PCR[3] &= ~(PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK
				| PORT_PCR_PFE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK
				| PORT_PCR_SRE_MASK);
		PORTB->PCR[3] |=
				PORT_PCR_MUX(
						0)|PORT_PCR_DSE(0)|PORT_PCR_PFE(0)|PORT_PCR_PE(1)|PORT_PCR_PS(1)|PORT_PCR_SRE(0);
		break;
	case 4:
		PORTC->PCR[2] &= ~(PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK
				| PORT_PCR_PFE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK
				| PORT_PCR_SRE_MASK);
		PORTC->PCR[2] |=
				PORT_PCR_MUX(
						0)|PORT_PCR_DSE(0)|PORT_PCR_PFE(0)|PORT_PCR_PE(1)|PORT_PCR_PS(1)|PORT_PCR_SRE(0);
		break;
	case 5:
		PORTC->PCR[1] &= ~(PORT_PCR_MUX_MASK | PORT_PCR_DSE_MASK
				| PORT_PCR_PFE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK
				| PORT_PCR_SRE_MASK);
		PORTC->PCR[1] |=
				PORT_PCR_MUX(
						0)|PORT_PCR_DSE(0)|PORT_PCR_PFE(0)|PORT_PCR_PE(1)|PORT_PCR_PS(1)|PORT_PCR_SRE(0);
		break;
	default:
		printf("Invalid channel \n"); /* 2: is the channel valid ? */

	}

}

/*
 * @author morten@ase.au.dk
 * @date oct 17 2018
 * @param channel number 0-5, corresponding to available pins on the KL25Z board
 * @brief this function reads from on of multiplexed channels on ADC0
 *
 * Read from ADC pins, each channel is selected by writing the ADCH bits in the SC
 * A0 = ADC0_SE8 - PTB0 - ADCH = 01000 8
 * A1 = ADC0_SE9 - PTB1 - ADCH = 01001 9
 * A2 = ADC0_SE12 - PTB2 - ADCH = 01100 12
 * A3 = ADC0_SE13 - PTB3 - ADCH = 01101 7
 * A4 = ADC0_SE11 - PTC2 - ADCH = 01011  11
 * A5 = ADC0_SE15 - PTC1 - ADCH = 01111 15
 */
unsigned short adcRead(int channel) {
	/* 1: a result variable */
	unsigned short res;

	/* 2: is the channel valid ? */

	/* 3: start the selected channel, lookup in channel map, to enable to correct ADC channel
	 * result is stored in result register R[0]
	 *  Bit 7 COCO 0 Read-only flag which is set when a conversion completes.// done
	 *  Bit 6 AIEN 0 Conversion complete interrupt disabled. done
	 *  Bit 5 DIFF 0 Single-ended conversion selected. done
	 *  Bit 4:0 ADCH 'channel' selected as ADC input channel done
	 *
	 * */
	ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;
	switch (channel) {
	case 0:

		ADC0->SC1[0] |= ADC_SC1_ADCH(8U) ;
		break;
	case 1:

		ADC0->SC1[0] |= ADC_SC1_ADCH(9U);

		break;
	case 2:

		ADC0->SC1[0] |= ADC_SC1_ADCH(01100U);
		break;
	case 3:

		ADC0->SC1[0] |= ADC_SC1_ADCH(01101U);

		break;
	case 4:

		ADC0->SC1[0] |= ADC_SC1_ADCH(01011);
		break;
	case 5:

		ADC0->SC1[0] |= ADC_SC1_ADCH(01111U);

		break;
	default:
		printf("Invalid channel \n"); /* 2: is the channel valid ? */

	}
	ADC0->SC1[0] &= ~(ADC_SC1_DIFF_MASK | ADC_SC1_AIEN_MASK);
	ADC0->SC1[0] |= ADC_SC1_DIFF(0);
	ADC0->SC1[0] |= ADC_SC1_AIEN(0);

	while (1) {

		while (!(ADC0->SC1[0] && ADC_SC1_COCO_MASK)) {
		}
		res = (unsigned short) ADC0->R[0];
		return res;/* 5: return result, just the entire 32 bit register, casted as unsigned short, since unused bits 16:31 are cleeared by HW */

	}

}

