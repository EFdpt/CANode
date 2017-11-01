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

#define BUFFER_SIZE		        (64)

#ifdef _PEDALI

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		3

	extern __IO uint16_t* TPS1_DATA;
	extern __IO uint16_t* TPS2_DATA;
	extern __IO uint16_t* BRAKE_DATA;

#elif defined(_RT_DX) || defined(_RT_SX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		1

	extern __IO uint16_t* SUSP_DATA;

#elif defined(_FR_DX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		2

	extern __IO uint16_t* SUSP_DATA;
	extern __IO uint16_t* STEER_DATA;

#elif defined(_FR_SX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		3

	extern __IO uint16_t* PRESS1_DATA;
	extern __IO uint16_t* PRESS2_DATA;
	extern __IO uint16_t* SUSP_DATA;

#elif defined(_COG)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		4

	extern __IO uint16_t* ACCX_DATA;
	extern __IO uint16_t* ACCY_DATA;
	extern __IO uint16_t* ACCZ_DATA;
	extern __IO uint16_t* GYRO_DATA;

#elif defined(_CRUSCOTTO) || defined(_BATTERIA)

#else
	#error "No board specified"
#endif

#ifdef _PEDALI || defined(_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || \
			defined(_FR_SX) || defined(_COG)

	// remapping of buffer position based on ADC_SCAN_NUM offset
	// i.e.
	// buffer[x] --> buffer[pos(x)]
	#define pos(x)			(x * ADC_SCAN_NUM)

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
