/*
 *  @file 		tim.h
 *  @author		Arella Matteo
 *  @date 		20 dic 2017
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
#define TIMER_PRESCALER 		((uint16_t) ((SystemCoreClock / 2) / 6000000) - 1)
#define TIMER_PERIOD 			0

extern void TIM_Config();

extern void TIM_start();

#ifdef __cplusplus
}
#endif

#endif /* TIM_H_ */
