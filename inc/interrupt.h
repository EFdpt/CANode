/*
 *  @file 		interrupt.h
 *  @author		Arella Matteo
 *  @date 		14 ott 2017
 *  @brief
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#ifdef __cplusplus
<<<<<<< HEAD
	extern "C" {
=======
extern "C" {
>>>>>>> develop
#endif

#include "include.h"

<<<<<<< HEAD
#define ATOMIC() do {							\
		uint32_t old_primask = __get_PRIMASK(); \
		__disable_irq();						\
	} while (0)

#define END_ATOMIC() do {						\
		__set_PRIMASK(old_primask);				\
	} while (0)
=======
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#define ATOMIC() 								\
		uint32_t old_primask = __get_PRIMASK(); \
		__disable_irq()


#define END_ATOMIC() do {						\
		__set_PRIMASK(old_primask);				\
} while (0)
>>>>>>> develop

void PVD_IRQHandler(void);


void ADC_IRQHandler(void);


void DMA2_Stream0_IRQHandler(void);

void CAN2_TX_IRQHandler(void);

void CAN2_RX0_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_H_ */
