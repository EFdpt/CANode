/*
 *  @file 		dma.h
 *  @author		Arella Matteo
 *  @date 		14 set 2017
 *  @brief		Header for dma.c module
 */

#ifndef DMA_H_
#define DMA_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include "include.h"

#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA2
#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_IRQ           DMA2_Stream0_IRQn

// TIM8 triggers DMA transactions
#define DMA_TIMER				 TIM8
#define DMA_TIMER_CLOCK			 RCC_APB2Periph_TIM8
	// TODO: set specific board prescaler and periode
#define DMA_TIMER_PRESCALER 	 1
#define DMA_TIMER_PERIODE 		 50
#define DMA_TIMER_CLOCK_DIVISION TIM_CKD_DIV1

// Transfer complete interrupt mask
#define DMA_IT_TCIF              DMA_IT_TCIF0
#define DMA_STREAM_IRQHANDLER    DMA2_Stream0_IRQHandler

#define PERIPHERAL_ADDR 		 GPIOA->IDR

#define BUFFER_CAPACITY          (128)

extern uint32_t					 buffer_index;

#ifdef _PEDALI
	extern __IO uint16_t THROTTLE_1_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t THROTTLE_2_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t BRAKE_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t PLAUS_1_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t PLAUS_2_DATA[BUFFER_CAPACITY];
#elif defined _CRUSCOTTO

#elif defined _FR_DX

#elif defined _FR_SX

#elif defined _RT_DX

#elif defined _RT_SX

#elif defined _BATTERIA

#else
	#error "No board specified"
#endif

#define TIMEOUT_MAX				 (10000)

/**
  * @brief  This function is used to initialize DMA
  * @param  None
  * @retval None
  */
void DMA_Config();

#ifdef __cplusplus
}
#endif

#endif /* DMA_H_ */
