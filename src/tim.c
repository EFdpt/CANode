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

inline void TIM_start() {
	/* TIM enable counter */
	TIM_Cmd(TIMER, ENABLE);
}

inline void TIM_stop() {
	/* stop TIMER peripheral */
	TIM_Cmd(TIMER, DISABLE);
}
