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

#define DATA_NUM		        (64)

#ifdef _PEDALI

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		3

	#define	BUFFER_SIZE			DATA_NUM * ADC_SCAN_NUM

	extern __IO uint16_t BUFFER_DATA[BUFFER_SIZE];

#elif defined(_RT_DX) || defined(_RT_SX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		1

	#define	BUFFER_SIZE			DATA_NUM * ADC_SCAN_NUM

	extern __IO uint16_t BUFFER_DATA[BUFFER_SIZE];

#elif defined(_FR_DX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		2

	#define	BUFFER_SIZE			DATA_NUM * ADC_SCAN_NUM

	extern __IO uint16_t BUFFER_DATA[BUFFER_SIZE];

#elif defined(_FR_SX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		3

	#define	BUFFER_SIZE			DATA_NUM * ADC_SCAN_NUM

	extern __IO uint16_t BUFFER_DATA[BUFFER_SIZE];

#elif defined(_COG)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		4

	#define	BUFFER_SIZE			DATA_NUM * ADC_SCAN_NUM

	extern __IO uint16_t BUFFER_DATA[BUFFER_SIZE];

#elif defined(_CRUSCOTTO) || defined(_BATTERIA)

#else
	#error "No board specified"
#endif

/**
  * @brief  This function is used to initialize DMA
  * @param  None
  * @retval None
  */
extern void DMA_Config();

#ifdef __cplusplus
}
#endif

#endif /* DMA_H_ */
