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
#define DOUBLE_BUFFER_MODE		(1)

#if defined(_PEDALI)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_IRQHandler		DMA2_Stream0_IRQHandler
	#define DMA_IT_FIFO			DMA_IT_TCIF0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		3

	extern __IO uint16_t* TPS1_DATA;
	extern __IO uint16_t* TPS2_DATA;
	extern __IO uint16_t* BRAKE_DATA;

	extern __IO uint16_t tps1_value;
	extern __IO uint16_t tps2_value;
	extern __IO uint16_t brake_value;

#elif defined(_RT_DX) || defined(_RT_SX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_IRQHandler		DMA2_Stream0_IRQHandler
	#define DMA_IT_FIFO			DMA_IT_TCIF0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		1

	extern __IO uint16_t* SUSP_DATA;

	extern __IO uint16_t susp_value;

#elif defined(_FR_DX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_IRQHandler		DMA2_Stream0_IRQHandler
	#define DMA_IT_FIFO			DMA_IT_TCIF0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		2

	extern __IO uint16_t* SUSP_DATA;
	extern __IO uint16_t* STEER_DATA;

	extern __IO uint16_t susp_value;
	extern __IO uint16_t steer_value;

#elif defined(_FR_SX)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_IRQHandler		DMA2_Stream0_IRQHandler
	#define DMA_IT_FIFO			DMA_IT_TCIF0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		3

	extern __IO uint16_t* PRESS1_DATA;
	extern __IO uint16_t* PRESS2_DATA;
	extern __IO uint16_t* SUSP_DATA;

	extern __IO uint16_t press1_value;
	extern __IO uint16_t press2_value;
	extern __IO uint16_t susp_value;

#elif defined(_COG) || defined(_TEST_UP)

	#define DMA_STREAM			DMA2_Stream0
	#define DMA_CHANNEL			DMA_Channel_0
	#define DMA_IRQHandler		DMA2_Stream0_IRQHandler
	#define DMA_IT_FIFO			DMA_IT_TCIF0
	#define DMA_STREAM_IRQ		DMA2_Stream0_IRQn

	#define ADC_SOURCE			ADC1
	#define ADC_SCAN_NUM		4

	extern __IO uint16_t* ACCX_DATA;
	extern __IO uint16_t* ACCY_DATA;
	extern __IO uint16_t* ACCZ_DATA;
	extern __IO uint16_t* GYRO_DATA;

	extern __IO uint16_t accx_value;
	extern __IO uint16_t accy_value;
	extern __IO uint16_t accz_value;
	extern __IO uint16_t gyro_value;

#elif defined(_CRUSCOTTO) || defined(_BATTERIA) || defined(_TEST_DOWN)

#else
	#error "No board specified"
#endif

#if defined(_PEDALI) || defined(_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || defined(_FR_SX) || defined(_COG)

	// remapping of buffer position based on ADC_SCAN_NUM offset
	// i.e.
	// buffer[x] --> buffer[pos(x)]
	#define pos(x)			((x) * ADC_SCAN_NUM)

#endif

/**
  * @brief  This function is used to initialize DMA
  * @param  None
  * @retval None
  */
extern void DMA_Config();

/**
  * @brief  This function is used to copy DMA buffer data (after transfer complete) to specific sensor measure buffer
  * @param  None
  * @retval None
  */
extern void copy_to_buffers();

#ifdef __cplusplus
}
#endif

#endif /* DMA_H_ */
