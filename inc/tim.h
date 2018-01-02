/*
 *  @file 		tim.h
 *  @author		Arella Matteo & Valerio Dodet
 *  @date 		02 Jan 2018
 *  @brief		Header for tim.c module
 */

#ifndef TIM_H_
#define TIM_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include "include.h"

#define TIMER					TIM3
#define TIMER_IRQCHANNEL		TIM3_IRQn

#if defined(_PEDALI)
	#define TIMER_PRESCALER 		((uint16_t) 199)
#elif defined(_RT_DX)

	#define TIMER_PRESCALER			((uint16_t) 99)
	

#elif defined(_RT_SX)

#define CAN_ID			RT_SX_ID

#elif defined(_FR_DX)

	#define TIMER_PRESCALER					((uint16_t) 99) // 100 - 1
	#define TIMER_PERIOD_PRESCALER			((uint16_t) 10000)

#elif defined(_FR_SX)

#define CAN_ID			FR_SX_ID

#elif defined(_COG) || defined(_TEST_UP)

#define CAN_ID			COG_ID

#elif defined(_CRUSCOTTO)

#define CAN_ID			CRUSCOTTO_ID

#elif defined(_BATTERIA)

#define CAN_ID			BATTERIA_ID

#endif

#define TIMER_PERIOD 			0

extern void TIM_Config();

extern void TIM_start(TIM_TypeDef*);

extern void TIM_stop(TIM_TypeDef*);

extern void TIMpickup_Config();



#ifdef __cplusplus
}
#endif

#endif /* TIM_H_ */
