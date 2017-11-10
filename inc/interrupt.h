/*
 *  @file 		interrupt.h
 *  @author		Arella Matteo
 *  @date 		14 ott 2017
 *  @brief
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include "include.h"

#define ATOMIC() do {							\
		uint32_t old_primask = __get_PRIMASK(); \
		__disable_irq();						\
	} while (0)

#define END_ATOMIC() do {						\
		__set_PRIMASK(old_primask);				\
	} while (0)

void PVD_IRQHandler(void);


void ADC_IRQHandler(void);


void DMA2_Stream0_IRQHandler(void);

void CAN2_TX_IRQHandler(void);

void CAN2_RX0_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_H_ */
