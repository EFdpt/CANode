/*
 *  @file 		tim.h
 *  @author		Arella Matteo & Valerio Dodet
 *  @date 		19 Jan 2018
 *  @brief		Header for tim.c module
 */

#ifndef TIM_H_
#define TIM_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include "include.h"

#define TIMER					TIM1	//FIXME TIM1 da utilizzare SOLO per ruote foniche, consiglio di utilizzare sempre la definizione TIM1, TIM2 etc..
#define OFFSET_TIMER			TIM3
#define OFFSET_TIMER_CLOCK		RCC_APB1Periph_TIM3
#define TIMER_IRQCHANNEL		TIM3_IRQn
#define TIMER_PERIOD			1000				// 1ms

	/*
	 * @defgroup TIM
	 * @{
	 * @brief TIM1_PRESCALER for wheels pickup, at 840Hz (max speed)
	 * and prescaler value= 2000, the TIM1_CNT value should be 50.
	 * CK_CNT = 42KHz
	 * */
#if defined(_RT_DX)|| defined(_RT_SX)|| defined (_FR_DX)|| defined(_FR_SX)
	#define TIM1_PRESCALER			((uint16_t) 2000)
#endif
	/*@}
	 * */


#if defined(_PEDALI)

	#define OFFSET_TIMER_PRESCALER			((uint16_t) 1000) // 1ms offset
	#define SYSTIMER_PERIOD_PRESCALER		((uint16_t) 5000) // 5ms period

#elif defined(_RT_DX)

	#define OFFSET_TIMER_PRESCALER			((uint16_t) 5000) // 5ms offset
	#define SYSTIMER_PERIOD_PRESCALER		((uint16_t) 10000) // 10ms period

#elif defined(_RT_SX)

	#define OFFSET_TIMER_PRESCALER			((uint16_t) 3000) // 3ms offset
	#define SYSTIMER_PERIOD_PRESCALER		((uint16_t) 10000) // 10ms period

#elif defined(_FR_DX)

	#define OFFSET_TIMER_PRESCALER			((uint16_t) 4000) // 4ms offset
	#define SYSTIMER_PERIOD_PRESCALER		((uint16_t) 10000) // 10ms period

#elif defined(_FR_SX)

	#define OFFSET_TIMER_PRESCALER			((uint16_t) 2000) // 2ms offset
	#define SYSTIMER_PERIOD_PRESCALER		((uint16_t) 10000) // 10ms period

#elif defined(_COG) || defined(_TEST_UP)

	#define OFFSET_TIMER_PRESCALER			((uint16_t) 7000) // 7ms offset
	#define SYSTIMER_PERIOD_PRESCALER		((uint16_t) 10000) // 10ms period

#endif

extern void Offset_Config();

extern void TIM_start(TIM_TypeDef*);

extern void TIM_stop(TIM_TypeDef*);

extern void TIMpickup_Config();



#ifdef __cplusplus
}
#endif

#endif /* TIM_H_ */
