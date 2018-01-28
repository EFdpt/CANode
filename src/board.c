/**
 *	board.c
 * @author: Valerio Dodet
 * @brief: this file contains functions to configure and initialize the GPIO
 * to match the hardware board configuration
 *
 * */

#include "board.h"

GPIO_InitTypeDef  GPIO_InitStructure;
RCC_ClocksTypeDef RCC_ClockFreq;

void GPIO_init(GPIO_TypeDef* GPIOx, uint32_t Pin, GPIOMode_TypeDef Mode, GPIOOType_TypeDef OType, GPIOSpeed_TypeDef Speed, GPIOPuPd_TypeDef PuPd){
	GPIO_InitStructure.GPIO_Pin = Pin;
	GPIO_InitStructure.GPIO_Mode = Mode;
	GPIO_InitStructure.GPIO_OType = OType;
	GPIO_InitStructure.GPIO_Speed = Speed;
	GPIO_InitStructure.GPIO_PuPd =PuPd;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/* questa funzione viene invocata per configurare le funzionalit� della
 * scheda in base al parametro posizione NON VIRGOLETTATO che deve essere
 * uno tra: PEDALI, CRUSCOTTO, FR_DX, FR_SX, RT_DX, RT_SX, BATTERIA, COG
 *
 * configura il PWR control,
 *
 * configura il RCC per abilitare i clock delle periferiche utilizzate, diverse
 * per ogni scheda
 *
 * */
void Init_Board(){



	//	/*
	//	 * il GPIOA8 viene configurato per uscire il HSE/4 = 6MHz
	//	 * 24:26 110 MCO1PRE
	//	 * 22:21 10 HSE out
	//	 * */
	//	RCC->CFGR |= 0x19<<22;

	//	/*PLS = 2.9V, PVD enabled, HSEON,
	//	 * This event can generate an interrupt to the EXTI line16 if enabled through the EXTI registers.
	//	 * The PVD output interrupt can be generated when VDD drops below the PVD threshold and/or when VDD
	//	 * rises above the PVD threshold depending on EXTI line16 rising/falling edge configuration */
	//	PWR->CR |= 0x100F0;

	/*clock init*/
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div2);
	RCC_PCLK1Config(RCC_HCLK_Div4);
	RCC_GetClocksFreq(&RCC_ClockFreq);//check the frequency

	/* GPIOA/B/C/D Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(
			RCC_AHB1Periph_GPIOA |
			RCC_AHB1Periph_GPIOB |
			RCC_AHB1Periph_GPIOC |
			RCC_AHB1Periph_GPIOD,
			ENABLE);

//	switch (posizione){

	/* FIXME controllare che siano abilitate le giuste periferiche sulla scheda
	 * 		controllare abilitazione Interrupt per:
	 * 			PVD
	 * 			CAN2_Rx
	 */


//	case PEDALI:
#ifdef _PEDALI


		GPIO_init(GPIOA, MCO1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);


		GPIO_init(GPIOA, en23, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		GPIO_init(GPIOA, ADCrd1 | ADCrd2 | tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*pin NON utilizzati configurati INPUT pullDOWN*/
		GPIO_init(GPIOA, USART1cts | USART1rts | USART1rx | USART1tx, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, I2C1scl | I2C1sda | Mux1 | ENMux | LSfet, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* i fet di abilitazione dell'uscita5V-21, dellOpAmp12 e 34
		 * sono pilotati con un PullUp
		 * */
		GPIO_init(GPIOB, en21 | EnADC12 | EnADC34 , GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);


		GPIO_init(GPIOB, ADCrd3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOB,dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/*
		 * dg11 e dg21 sono collegati all'OpAmp differenziale, NON AGGIUNGERE RESISTENZE PULL UP/DOWN*/
		GPIO_init(GPIOC, dg11 | dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, ENRS | HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);


		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);




#elif defined (_TEST_DOWN)
/*test di consumi bassi tutte le periferiche sono spente e gli integrati sulla scheda
 * disabilitati
 * */

		GPIO_init(GPIOA, MCO1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		GPIO_init(GPIOA, en23, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		GPIO_init(GPIOA, ADCrd1 | ADCrd2 | tempRD, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*pin NON utilizzati configurati INPUT pullDOWN*/
		GPIO_init(GPIOA, USART1cts | USART1rts | USART1rx | USART1tx, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, I2C1scl | I2C1sda | Mux1 | ENMux | LSfet, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* i fet di abilitazione degli OpAmp12 e 34 sono pilotati con un PullUp,
		 * DOWN per accendere l'integrato, UP per disabilitare l'OpAmp
		 * */
		GPIO_init(GPIOB, EnADC12 | EnADC34 , GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);


		GPIO_init(GPIOB, en21 | ADCrd3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*
		 * dg31 e dg41 sono collegati all'OpAmp differenziale, NON AGGIUNGERE RESISTENZE PULL UP/DOWN*/
		GPIO_init(GPIOB,dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*
		 * dg11 e dg21 sono collegati all'OpAmp differenziale, NON AGGIUNGERE RESISTENZE PULL UP/DOWN*/
		GPIO_init(GPIOC, dg11 | dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, ENRS | HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);


		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#elif defined (_TEST_UP)

		/*
		 * SteerAngSupply  ON*/
		GPIO_init(GPIOA, en23, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);


		GPIO_init(GPIOA, ADCrd1 | ADCrd2 |tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*il pin 18 del molex dovrebbe uscire il clock del proc fa un pin nella mmh*/
		GPIO_init(GPIOA, MCO1, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB,  I2C1scl | I2C1sda | Mux1 | EnADC34, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* i fet di abilitazione dell'uscita5V-21 e dellOpAmp12
		 * sono pilotati con un PullUp
		 * */
		GPIO_init(GPIOB, LSfet | en21 | EnADC12| ENMux , GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/**/
		GPIO_init(GPIOB, dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/**/
		GPIO_init(GPIOB, ADCrd3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz,GPIO_PuPd_NOPULL);

		/**/
		GPIO_init(GPIOC, dg11 | dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOC, ADCrd4, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp per disabilitare l'uscita, un pullDOWN per abilitarla
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		GPIO_init(GPIOC, ENRS, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/**/
		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#elif defined (_CRUSCOTTO)

		//TODO cruscotto Init
		/* 1x AIR button - D
		 * 1x RTD button - D
		 * 2x potenziometri - A
		 * 1x LED RTD
		 * 1x LED AIR
		 * 1x LED regeneration*/

		//	ADC1/2 Peripheral Clock Enable
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |
				RCC_APB2Periph_ADC2,
				ENABLE);

		/*
		 * signal IN */
		GPIO_init(GPIOA, MCO1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*
		 * RTD led*/
		GPIO_init( GPIOA, en23, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/*potenziometri */
		GPIO_init(GPIOA, ADCrd1 | ADCrd2 |tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, I2C1scl | I2C1sda | Mux1 | ENMux | EnADC34 | ADCrd3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*configurazione LSfet*/
		GPIO_init(GPIOB, LSfet, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/* i fet di abilitazione dell'uscita5V-21 e dellOpAmp12
		 * sono pilotati con un PullUp
		 * */
		GPIO_init(GPIOB, EnADC12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*AIR LED*/
		GPIO_init(GPIOB, en21 , GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/*dg31 Forward IN, dg41 RESET inverter IN sono cablati, non esistono su CAN
		 * configurati IN senza pull down per la rete dell'OpAMP*/
		GPIO_init(GPIOB, dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/**/
		GPIO_init(GPIOC, dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOC, dg11 , GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOC, ADCrd4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*
		 * Buttons voltage supply
		 * */
		GPIO_init(GPIOC, SCK3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, ENRS | HDPLX | RSelect | SpeedRS | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/**/
		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#elif defined (_FR_DX)
		//TODO fr_dx ADC Init

		//	ADC1/2 Peripheral Clock Enable
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |
				RCC_APB2Periph_ADC2,
				ENABLE);

		/*
		 * SteerAngSupply  */
		GPIO_init(GPIOA, en23, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);


		GPIO_init(GPIOA, ADCrd1 | ADCrd2 |tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOA, MCO1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, LSfet | I2C1scl | I2C1sda | Mux1 | ENMux | EnADC34 | ADCrd3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* i fet di abilitazione dell'uscita5V-21 e dellOpAmp12
		 * sono pilotati con un PullUp
		 * */
		GPIO_init(GPIOB, en21 | EnADC12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/**/
		GPIO_init(GPIOB, dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/**/
		GPIO_init(GPIOC, dg11 | dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOC, ADCrd4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, ENRS | HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/**/
		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#elif defined (_FR_SX)
		//TODO fr_sx Init

		//	ADC1/2 Peripheral Clock Enable
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |
				RCC_APB2Periph_ADC2	|
				RCC_APB2Periph_ADC3,
				ENABLE);

		/*
		 * SteerAngSupply  */
		GPIO_init(GPIOA, en23, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);


		GPIO_init(GPIOA, ADCrd1 | ADCrd2 |tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOA, MCO1, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		GPIO_init(GPIOB, ADCrd3, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, LSfet | I2C1scl | I2C1sda | Mux1 | ENMux, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* i fet di abilitazione dell'uscita5V-21 e dellOpAmp12
		 * sono pilotati con un PullUp
		 * */
		GPIO_init(GPIOB, en21 | EnADC12 | EnADC34, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/**/
		GPIO_init(GPIOB, dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/**/
		GPIO_init(GPIOC, dg11 | dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOC, ADCrd4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, ENRS | HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/**/
		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#elif defined (_RT_DX)
		//TODO rt_dx Init
		//	ADC1/2 Peripheral Clock Enable
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |
				RCC_APB2Periph_ADC2,
				ENABLE);

		GPIO_init(GPIOA, ADCrd1 |tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOA, MCO1 | en23 | ADCrd2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, LSfet | I2C1scl | I2C1sda | Mux1 | ENMux | EnADC34 | ADCrd3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* i fet di abilitazione dell'uscita5V-21 e dellOpAmp12
		 * sono pilotati con un PullUp
		 * */
		GPIO_init(GPIOB, en21 | EnADC12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/**/
		GPIO_init(GPIOB, dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/**/
		GPIO_init(GPIOC, dg11 | dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOC, ADCrd4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, ENRS | HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/**/
		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#elif defined (_RT_SX)
		//TODO rt_sx Init
		//	ADC1/2 Peripheral Clock Enable
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 |
				RCC_APB2Periph_ADC2,
				ENABLE);

		GPIO_init(GPIOA, ADCrd1 |tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOA, MCO1 | en23 | ADCrd2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, LSfet | I2C1scl | I2C1sda | Mux1 | ENMux | EnADC34 | ADCrd3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* i fet di abilitazione dell'uscita5V-21 e dellOpAmp12
		 * sono pilotati con un PullUp
		 * */
		GPIO_init(GPIOB, en21 | EnADC12, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/**/
		GPIO_init(GPIOB, dg31 | dg41, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		/**/
		GPIO_init(GPIOC, dg11 | dg21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_NOPULL);

		GPIO_init(GPIOC, ADCrd4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/* il fet di abilitazione dell'uscita5V-22
		 * è pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, en22, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC, ENRS | HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/**/
		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#elif defined (_BATTERIA)
		//TODO batteria Init

		GPIO_init(GPIOA, tempRD, GPIO_Mode_AN, GPIO_OType_PP, GPIO_Speed_100MHz, GPIO_PuPd_NOPULL);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOA, MCO1 | en23 | ADCrd1 |ADCrd2 | DAC1 | DAC2, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOB, dg31 | dg41 |  Mux1 | ENMux | EnADC34 | EnADC12| ADCrd3| en21, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/*FIXME
		 * pwm out o in?*/
		GPIO_init(GPIOB, LSfet, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_50MHz, GPIO_PuPd_NOPULL);

		/* il fet di abilitazione dell'uscita5V-22
		 * � pilotato con un PullUp
		 * */
		GPIO_init(GPIOC, dg11, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);

		/*i pin non utilizzati vengono configurati come digital IN e pullDOWN*/
		GPIO_init(GPIOC,ADCrd4 | en22 | dg21 | ENRS | HDPLX | RSelect | SpeedRS | SCK3 | MOSI3 | MISO3, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

		/**/
		GPIO_init(GPIOD, Mux0, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);

#else
	#error "No board specified"
#endif

	CAN_Config();
	ADC_Config();
	DMA_Config();
	Offset_Config();
}

