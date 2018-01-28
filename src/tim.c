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
	TIM_TimeBaseStructure.TIM_Period = TIMER_PERIOD - 1;          //set the period FIXME sicuuuro?
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


/*
 * @author	Valerio Dodet
 * @brief 	Config TIM1 in Slave Reset mode with DMA transfer at every rising edge on the pin18 of the molex
 * @param	None
 * @retval	None
 *
 * */
void TIMpickup_Config(){
#if defined (_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || defined(_FR_SX)

	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};
	TIM_ICInitTypeDef TIM_ICInitStruct;

	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_DeInit(TIM1);


	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter=0;

	//Enable DMA transfer of counter register
	TIM_DMAConfig(TIM1,TIM_DMABase_CNT,TIM_DMABurstLength_1Transfer);

	//Enable DMA transfer on Update event every rising edge on trigger input
	TIM_DMACmd(TIM1,TIM_DMA_Update, ENABLE);

	 /* @defgroup TIM1_BASE_STRUCTURE
	  * @{
	  * @brief counterMode_Up,
	 * */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TIM1_PERIOD16b; //this should be ignored because of the default disabled Auto-Reload
	TIM_TimeBaseStructure.TIM_Prescaler = TIM1_PRESCALER;

	/*
	 * @}
	 * */

//	/* Enable the TIMER global Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;	//timer1 capture compare interrupt channel
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	/* TIM Interrupts enable */
//	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_ICInit(TIM1, &TIM_ICInitStruct);

//	TIM1_SMCR: SMS=100, TS=101
	TIM_SelectSlaveMode(TIM1,TIM_SlaveMode_Reset);
	TIM_SelectInputTrigger(TIM1,TIM_TS_TI1FP1);

	/* TIM enable counter */
	TIM_Cmd(TIM1, ENABLE);
#endif
}

inline void TIM_start(TIM_TypeDef* timer) {
	/* TIM enable counter */
	TIM_Cmd(timer, ENABLE);
}

inline void TIM_stop(TIM_TypeDef* timer) {
	/* stop TIMER peripheral */
	TIM_Cmd(timer, DISABLE);
}
