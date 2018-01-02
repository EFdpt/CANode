/*
 *  @file 		tim.c
 *  @author		Arella Matteo
 *  @date 		20 dic 2017
 *  @brief		tim.c module
 */

#include "tim.h"

void Offset_Config() {

#if defined(_PEDALI) || defined(_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || defined(_FR_SX) || defined(_COG) || defined(_TEST_UP) || defined(_CRUSCOTTO) || defined(_BATTERIA)

	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};

	/* TIMER clock enable */
	RCC_APB1PeriphClockCmd(OFFSET_TIMER_CLOCK, ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler = OFFSET_TIMER_PRESCALER - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      //can be TIM_CounterMode_Up or TIM_CounterMode_Down
	TIM_TimeBaseStructure.TIM_Period = TIMER_PERIOD - 1;          //set the period
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;      //counter runs in repetition

	TIM_TimeBaseInit(OFFSET_TIMER, &TIM_TimeBaseStructure);         //initialize the timer

	/* TIM IT enable */
	TIM_ITConfig(OFFSET_TIMER, TIM_IT_Update, ENABLE);

	/* Enable the TIMER global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIMER_IRQCHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

#endif
}

inline void TIM_start() {
	/* TIM enable counter */
	TIM_Cmd(OFFSET_TIMER, ENABLE);
}

inline void TIM_stop() {
	/* stop TIMER peripheral */
	TIM_Cmd(OFFSET_TIMER, DISABLE);
}
