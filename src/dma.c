/*
 *  @file 		dma.c
 *  @author		Arella Matteo
 *  @date 		14 set 2017
 *  @brief		dma.c module
 */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include "dma.h"

#define TIMEOUT_MAX				 (10000)

#ifdef _PEDALI

	__IO uint16_t THROTTLE_1_DATA[BUFFER_CAPACITY];
	__IO uint16_t THROTTLE_2_DATA[BUFFER_CAPACITY];
	__IO uint16_t FRONT_BRAKE_DATA[BUFFER_CAPACITY];
	__IO uint16_t POSTERIOR_BRAKE_DATA[BUFFER_CAPACITY];

#elif defined _CRUSCOTTO

	__IO uint16_t POTENTIOMETER_1_DATA[BUFFER_CAPACITY];
	__IO uint16_t POTENTIOMETER_2_DATA[BUFFER_CAPACITY];

#elif defined _FR_DX || defined _FR_SX || defined _RT_DX || defined _RT_SX

	__IO uint16_t SUSPENSIONS_DATA[BUFFER_CAPACITY];
	__IO uint16_t PHONIC_DATA[BUFFER_CAPACITY];

#endif

static inline void _DMA_Config(DMA_Stream_TypeDef* DMA_Stream,
						uint32_t DMA_Stream_Clock,
						uint32_t DMA_Channel,
						uint32_t peripheral_src, uint32_t memory_dest,
						uint32_t buffer_size, uint8_t DMA_Stream_IRQ);

//FIXME ho messo tutte la acquisizioni sull'ADC1 ma su diversi channel. vedi adc.h e adc.c
void DMA_Config() {

#ifdef _PEDALI

	// freno anteriore (ADC3 -> DMA2_Stream1, DMA_Channel_2)
	_DMA_Config(DMA2_Stream1, RCC_AHB1Periph_DMA2, DMA_Channel_2,
				(uint32_t) &GPIOB->IDR, (uint32_t) FRONT_BRAKE_DATA,
				BUFFER_CAPACITY, DMA2_Stream1_IRQn);

	// acceleratore 1 (ADC1 -> DMA2_Stream0, DMA_Channel_0)
	_DMA_Config(DMA2_Stream0, RCC_AHB1Periph_DMA2, DMA_Channel_0,
					(uint32_t) &GPIOA->IDR, (uint32_t) THROTTLE_1_DATA,
					BUFFER_CAPACITY, DMA2_Stream0_IRQn);

	// acceleratore 2 (ADC2 -> DMA2_Stream2, DMA_Channel_1)
	_DMA_Config(DMA2_Stream2, RCC_AHB1Periph_DMA2, DMA_Channel_1,
						(uint32_t) &GPIOA->IDR, (uint32_t) THROTTLE_2_DATA, // STESSA SORGENTE ???
						BUFFER_CAPACITY, DMA2_Stream2_IRQn);

	// TODO: freno posteriore (incongruenze pinout & rete CAN)

#elif defined _CRUSCOTTO

	// 1st potentiometer (ADC1 -> DMA2_Stream0, DMA_Channel_0)
	_DMA_Config(DMA2_Stream0, RCC_AHB1Periph_DMA2, DMA_Channel_0,
								(uint32_t) &GPIOA->IDR, (uint32_t) POTENTIOMETER_1_DATA,
								BUFFER_CAPACITY, DMA2_Stream0_IRQn);

	// 2nd potentiometer (ADC2 -> DMA2_Stream2, DMA_Channel_1)
	_DMA_Config(DMA2_Stream2, RCC_AHB1Periph_DMA2, DMA_Channel_1,
									(uint32_t) &GPIOA->IDR, (uint32_t) POTENTIOMETER_2_DATA,
									BUFFER_CAPACITY, DMA2_Stream2_IRQn);

#elif defined _FR_DX || defined _FR_SX || defined _RT_DX || defined _RT_SX

	// suspensions
	_DMA_Config(DMA2_Stream0, RCC_AHB1Periph_DMA2, DMA_Channel_0,
								(uint32_t) &GPIOA->IDR, (uint32_t) SUSPENSION_DATA,
								BUFFER_CAPACITY, DMA2_Stream0_IRQn);

	// phonic wheels
	_DMA_Config(DMA2_Stream0, RCC_AHB1Periph_DMA2, DMA_Channel_0,
								(uint32_t) &GPIOA->IDR, (uint32_t) PHONIC_DATA,
								BUFFER_CAPACITY, DMA2_Stream0_IRQn);

#endif
}

/**
  * @brief  This function configure DMA for transferring data from peripheral
  * 	to in memory buffer (DMA_DIR_PeripheralToMemory).
  * 	Buffered stream is used in direct mode (DMA_FIFOMode_Disable) so after
  * 	every data transfer from peripheral to FIFO, corresponding data is
  * 	immediately stored in destination.
  * 	To avoid saturating the FIFO, the corresponding stream is configured
  * 	with a high priority (DMA_Priority_High).
  * 	Memory and peripheral bursts are specified to be single burst, so in a
  * 	single non interruptible transaction only one single data is transferred.
  *		Circular mode is selected (DMA_Mode_Circular) to handle circular buffer
  *		and continuous data flows.
  * @param  None
  * @retval None
  */
static inline void _DMA_Config(DMA_Stream_TypeDef* DMA_Stream, uint32_t DMA_Stream_Clock,
				uint32_t DMA_Channel,
				uint32_t peripheral_src, uint32_t memory_dest,
				uint32_t buffer_size, uint8_t DMA_Stream_IRQ) {

	// allocate DMA structure and init it to zero
	DMA_InitTypeDef 	DMA_InitStructure = {0};

	NVIC_InitTypeDef 	NVIC_InitStructure = {0};

	__IO uint32_t		timeout = TIMEOUT_MAX;

	// enable DMA clock for selected stream
	RCC_AHB1PeriphClockCmd(DMA_Stream_Clock, ENABLE);

	DMA_InitStructure.DMA_Channel = DMA_Channel;

	// size of buffer in memory in which transfer data
	DMA_InitStructure.DMA_BufferSize = buffer_size;

	// pointer to buffer in memory
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) memory_dest;

	// pointer to source peripheral
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) peripheral_src;

	// one data transfer per each transaction
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	// only 16bit of GPIOx->IDR are relevant (upper 16bits are reserved)
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;

	// enable pointer increment after each transfer;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

	// disable pointer increment for peripheral (i.e. const value)
	// due to the fact that the peripheral source is accessed through
	// a single register
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// circular buffer behavior
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;

	DMA_InitStructure.DMA_Priority = DMA_Priority_High;

	// transfer direction: peripheral to memory
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

	// select direct mode
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;

	// due to direct mode configuration, this value is ignored
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;

	DMA_Init(DMA_Stream, &DMA_InitStructure);

	/* enable DMA Transfer Complete interrupt */
	DMA_ITConfig(DMA_Stream, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA_Stream, ENABLE);

	// enable the DMA Stream IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA_Stream_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// wait until DMA Stream has been effectively enabled
	while ((DMA_GetCmdStatus(DMA_Stream) != ENABLE) && (timeout-- > 0)) { }

	/* check if a timeout condition occurred */
	if (!timeout) {
	    /* manage the error: to simplify the code enter an infinite loop */
	    // for (;;) { }
		fprintf(stderr, "DMA Stream wasn't enabled: %s\n", strerror(errno));
	    exit(1);
	}
}
