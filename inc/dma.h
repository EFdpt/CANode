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

#if 0
#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA2
#define DMA_STREAM               DMA2_Stream0
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_IRQ           DMA2_Stream0_IRQn

// Transfer complete interrupt mask
#define DMA_IT_TCIF              DMA_IT_TCIF0
#define DMA_STREAM_IRQHANDLER    DMA2_Stream0_IRQHandler
#endif

#define BUFFER_CAPACITY          (128)

#ifdef _PEDALI

	extern __IO uint16_t THROTTLE_1_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t THROTTLE_2_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t FRONT_BRAKE_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t POSTERIOR_BRAKE_DATA[BUFFER_CAPACITY];

#elif defined _CRUSCOTTO

	extern __IO uint16_t POTENTIOMETER_1_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t POTENTIOMETER_2_DATA[BUFFER_CAPACITY];

#elif defined _FR_DX || defined _FR_SX || defined _RT_DX || defined _RT_SX

	extern __IO	uint16_t SUSPENSIONS_DATA[BUFFER_CAPACITY];
	extern __IO uint16_t PHONIC_DATA[BUFFER_CAPACITY];

#elif defined _BATTERIA

#else
	#error "No board specified"
#endif

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
