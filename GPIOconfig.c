/*
 * GPIOconfig.c
 *
 *  Created on: 10 apr 2017
 *      Author: Valerio Dodet
 *
 *      @details: Mux enabled on RS
 *
 */
#include "main.h"
#include "stm32f4xx.h"

void GPIOInit(){
	//A
	GPIOA->AFR[1] |= 0x77770;
	/*configura USART1*/

	GPIOA->MODER |= 0x02A8CFF3;
	GPIOA->MODER &= 0xFEABDFFF;
	/* configura USART, ADC1 e 2, en23, sens12V, tempRD, DAC1 e 2 */

	//#error "calcolare GPIOA->OTYPER "
	//GPIOA->OTYPER |=
	/*reset state=push-pull. per gli enable utilizzerei una configurazione open-drain + pull-up ma chiedo conferme*/

	GPIOA->OSPEEDR |= 0x01684540;
	GPIOA->OSPEEDR &= 0xFD6B454C;
	/*low speed: en23, sens12V, TempRD
	 * medium speed: ADCrd 1 e 2, USART cts rts, DAC 1 e 2
	 * high speed: USART rx tx,
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

	//#error "calcolare GPIOB->OSPEEDR"
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
	GPIOC->AFR[1] |= 0x66600;
	/*configura SPI 3*/

	GPIOC->MODER |= 0x02A55D00;
	/* configura SPI, SpeedRS, RSelect, HDPLX, EnRs, en22, ADCrd4, dg11, dg21 */

	//GPIOC->OTYPER reset state push-pull

	//#error "calcolare GPIOC_OSPEEDR"
	GPIOC->OSPEEDR |= 0x5004 << 8;
	/*low speed: SpeedRS, RSelect, HDPLX, EnRs, en22, dg11, dg21
	 * medium speed: ADCrd4
	 * high speed: SPI
	 */

	GPIOC->PUPDR |= 1 << 5;
	/* pull down: ADCrd 4 */

	GPIOC->BSRRL |= 0x3D << 4;
	/* Set: SpeedRS, RSelect, HDPLX, EnRs, en22
	 * vedere config RS
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

