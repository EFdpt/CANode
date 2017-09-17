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

#define DMA_STREAM_CLOCK         RCC_AHB1Periph_DMA1
#define DMA_STREAM               DMA1_Stream0
#define DMA_CHANNEL              DMA_Channel_0
#define DMA_STREAM_IRQ           DMA1_Stream0_IRQn
#define DMA_IT_TCIF              DMA_IT_TCIF0
#define DMA_STREAM_IRQHANDLER    DMA1_Stream0_IRQHandler

#define PERIPHERAL_ADDR 		 GPIOA->IDR

#define BUFFER_SIZE              (128)

extern uint16_t DMA_DATA[BUFFER_SIZE];

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
