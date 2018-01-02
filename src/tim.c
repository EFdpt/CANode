/*
 *  @file 		tim.c
 *  @author		Arella Matteo
 *  @date 		20 dic 2017
 *  @brief		tim.c module
 */

#include "tim.h"

void TIM_Config() {
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TIMER_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = TIMER_PRESCALER;

	/* Enable the TIMER global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIMER_IRQCHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIMER, TIM_IT_CC1, ENABLE);

	//TIM_Init(TIMER, &TIM_TimeBaseStructure);

	/* TIM enable counter */
	//TIM_Cmd(TIMER, ENABLE);
}

void TIMpickup_Config(){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	/*TODO
	 * configurare pin GPIOA_8, canale 1, TIM1_CCMR1: CC1S=1
	 * TIM1_CCER: CC1P=0 CC1NP=0
	 * TIM1_SMCR: SMS=100, TS=101
	 * TIM1_DIER: TIE=, TDE=
	 * configDMA
	 * configINTERRUPT
	 * TIM_PrescalerConfig(
	 *
	 * */

	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TIMER_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = TIMER_PRESCALER;

	/* Enable the TIMER global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIMER_IRQCHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIMER, TIM_IT_CC1, ENABLE);

	//TIM_Init(TIMER, &TIM_TimeBaseStructure);

	/* TIM enable counter */
	//TIM_Cmd(TIMER, ENABLE);
}

inline void TIM_start(TIM_TypeDef* timer) {
	/* TIM enable counter */
	TIM_Cmd(timer, ENABLE);
}

inline void TIM_stop(TIM_TypeDef* timer) {
	/* stop TIMER peripheral */
	TIM_Cmd(timer, DISABLE);
}
