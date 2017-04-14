/*
 * CANodeInit.c
 *
 *      Author: hermes
 */
#include "CANodeInit.h"

/* questa funzione viene invocata per configurare le funzionalità della
 * scheda in base al parametro posizione NON VIRGOLETTATO che deve essere
 * uno tra: PEDALI, CRUSCOTTO, FR_DX, FR_SX, RT_DX, RT_SX, BATTERIA, COG
 *
 * configura il PWR control,
 *
 * configura il RCC per abilitare i clock delle periferiche utilizzate, diverse
 * per ogni scheda
 *
 * */
void Init_Board(tipoScheda posizione){

	/*
	 * il GPIOA8 viene configurato per uscire il HSE/4 = 6MHz
	 * 24:26 110 MCO1PRE
	 * 22:21 10 HSE out
	 * */
	RCC->CFGR |= 0x19<<22;

	/*PLS = 2.9V, PVD enabled, HSEON,
	 * This event can generate an interrupt to the EXTI line16 if enabled through the EXTI registers.
	 * The PVD output interrupt can be generated when VDD drops below the PVD threshold and/or when VDD
	 * rises above the PVD threshold depending on EXTI line16 rising/falling edge configuration */
	PWR->CR |= 0x100F0;


	switch (posizione){

	/* FIXME controllare che siano abilitate le giuste periferiche sulla scheda
	 * 		controllare abilitazione Interrupt per:
	 * 			PVD
	 */
	case PEDALI:
		//abilita il clock sui GPIO A/B/C/D
		RCC->AHB1ENR |= 0xF;
		//abilita il clock su PWR, CAN2, WWDG
		RCC->APB1ENR |= 0x28001 << 11;
		//abilita il clock su ADC1/2/3, TIM1
		RCC->AHB2ENR |= 0x701;

		//

		break;
	case CRUSCOTTO:
		//TODO cruscotto Init

		break;
	case FR_DX:
		//TODO fr_dx Init

		break;
	case FR_SX:
		//TODO fr_sx Init

		break;
	case RT_DX:
		//TODO rt_dx Init

		break;
	case RT_SX:
		//TODO rt_sx Init

		break;
	case BATTERIA:
		//TODO batteria Init

		break;
	case COG:
		//TODO CoG Init

		break;
	default:

		break;
	}
}

/*per utilizzare il cristallo a 24 MHz sulla scheda invocare questa funzione*/
void HSESwitch(){
	RCC->CFGR |= 0x1;
}

/* configurazione GPIO: velocità clock, alternate function, IN/OUT, pullUp-pullDown,
 * 						0-1 per abilitazione periferiche
 * questa funzione la metterei in CANodeInit*/
void GPIOInit(){
	//A
	GPIOA->AFR[1] |= 0x77770;
	/*configura USART1*/

	GPIOA->MODER |= 0x02AACFF3;
	GPIOA->MODER &= 0xFEABDFFF;
	/* configura USART, ADC1 e 2, en23, sens12V, tempRD, DAC1 e 2, MCO1*/

	//#error "calcolare GPIOA->OTYPER "
	//GPIOA->OTYPER |=
	/*reset state=push-pull. per gli enable utilizzerei una configurazione open-drain + pull-up ma chiedo conferme*/

	GPIOA->OSPEEDR |= 0x016B4540;
	GPIOA->OSPEEDR &= 0xFD6B454C;
	/*low speed: en23, sens12V, TempRD
	 * medium speed: ADCrd 1 e 2, USART cts rts, DAC 1 e 2
	 * high speed: USART rx tx, MCO1
	 */

	GPIOA->PUPDR |= 0x80A2;
	GPIOA->PUPDR &= 0xFFFFBFAE;
	/* pull down: ADCrd 1 e 2, sens12V, TempRD */

	GPIOA->BSRRL |= 1 << 6;
	/* asserimento en23 */

	//B
	GPIOB->AFR[1] |= 0x09900044;
	/*configura CAN2, I²C 1*/

	GPIOB->MODER |= 0x445A690C;
	/* configura CAN, ASCcan, I2C, MuxEn, Mux1, en5, en21, EnADC12, EnADC34, ADCrd3, dg31, dg41 */

	//GPIOB->OTYPER ;//reset state push-pull

	//#error "calcolare GPIOB->OSPEEDR" - calcolato
	GPIOB->OSPEEDR |= 0x52804;
	/*low speed: ASCcan, MuxEn, Mux1, en5, en21, EnADC12, EnADC34, dg31, dg41
	 * medium speed: ADCrd3, I2C sda scl,
	 * high speed: CAN2 tx rx
	 */

	GPIOB->PUPDR |= 1 << 4;
	/* pull down: ADCrd 3 */

	GPIOB->BSRRL |= 0x8C81;
	/* Set: en21, MuxEn, EnADC12 e 34, en5
	 */

	//C
	GPIOC->AFR[1] |= 0x66000;
	/*configura MISO3, MOSI3 ma non SCK3*/

	//A=1010 → 1000=8
	GPIOC->MODER |= 0x02855D00;
	/* configura SPI, SpeedRS, RSelect, HDPLX, EnRs, en22, ADCrd4, dg11, dg21
	 * SCK3 come IN e non AF */


	//GPIOC->OTYPER reset state push-pull

	//#error "calcolare GPIOC_OSPEEDR" - calcolato
	GPIOC->OSPEEDR |= 0x5004 << 8;
	/*low speed: SpeedRS, RSelect, HDPLX, EnRs, en22, dg11, dg21
	 * medium speed: ADCrd4
	 * high speed: SPI
	 */

	GPIOC->PUPDR |= 1 << 5;
	/* pull down: ADCrd 4 */

	GPIOC->BSRRL |= 0x3D << 4;
	/* Set: EnRs, en22
	 * RS232, fullDuplex, no FAST up to 1Mbps
	 */

	//D
	GPIOD->MODER |= 1 << 4;
	/* configura Mux0 */

	//GPIOD->OTYPER reset state push-pull

	//#error "calcolare GPIOD->OSPEEDR"
	//GPIOD->OSPEEDR |= 0x0;
	/*low speed: Mux0
	 */

	//GPIOD->PUPDR |=
	/**/

	//#error "calcolare GPIOD->BSRR"
	//GPIOD->BSRRL |=
	/* Set: Mux0
	 * vedere config Mux
	 */
}
