#include "include.h"

uint8_t 	Data[8] = {0};//data bytes da inviare sul can

void BMS_TIMinit(void){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Prescaler = 84 - 1;// mettendo così qui hai 1MHz
	TIM_TimeBaseStructure.TIM_Period = 15000 - 1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
	TIM_Cmd (TIM3, ENABLE);
}


void TIM3_IRQHandler(void){

 if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET){

	 Data[0] = 0xAA;

	 CAN_Tx(8, Data, STAR_ID, CAN);

}
 TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}

