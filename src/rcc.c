#include "include.h"



void clock_init(void){

	//SYSCLK = 168MHz, HCLK = 168MHz, PCLK1 = 42MHz, PCLK2 = 84MHz

//	RCC_HCLKConfig(RCC_SYSCLK_Div1);
//	RCC_PCLK2Config(RCC_HCLK_Div2);
//	RCC_PCLK1Config(RCC_HCLK_Div4);
//	RCC_GetClocksFreq(&RCC_ClockFreq);//check the frequency

//	RCC_AHB1PeriphClockCmd(	RCC_AHB1Periph_DMA2		|
//							RCC_AHB1Periph_GPIOC	|
//							RCC_AHB1Periph_GPIOA	|
//							RCC_AHB1Periph_GPIOB,
//							ENABLE);
//
//	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_TIM2		|
//							RCC_APB1Periph_CAN2		,
//							ENABLE);

/*	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_ADC1		|
							RCC_APB2Periph_USART1,
							ENABLE); */
}
