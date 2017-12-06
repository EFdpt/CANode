/*
 *  @file 		dma.c
 *  @author		Arella Matteo
 *  @date 		14 set 2017
 *  @brief		dma.c module
 */

#include "dma.h"

#define TIMEOUT_MAX				 (10000)

// initialize an internal buffer for all channels
#if defined(_PEDALI) || defined(_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || defined(_FR_SX) || defined(_COG) || defined(_TEST_UP)

	#define BUFFER_CAPACITY		(BUFFER_SIZE * ADC_SCAN_NUM)

	__IO uint16_t BUFFER_DATA[BUFFER_CAPACITY] = {0};

#endif

// set data pointers to different offsets from internal buffer's base address
#if defined(_PEDALI)

	__IO uint16_t* TPS1_DATA = BUFFER_DATA;
	__IO uint16_t* TPS2_DATA = BUFFER_DATA + 1;
	__IO uint16_t* BRAKE_DATA = BUFFER_DATA + 2;

	__IO uint16_t tps1_value = 0;
	__IO uint16_t tps2_value = 0;
	__IO uint16_t brake_value = 0;

#elif defined(_RT_DX) || defined(_RT_SX)

	__IO uint16_t* SUSP_DATA = BUFFER_DATA;

	__IO uint16_t susp_value = 0;

#elif defined(_FR_DX)

	__IO uint16_t* SUSP_DATA = BUFFER_DATA;
	__IO uint16_t* STEER_DATA = BUFFER_DATA + 1;

	__IO uint16_t susp_value = 0;
	__IO uint16_t steer_value = 0;

#elif defined(_FR_SX)

	__IO uint16_t* PRESS1_DATA = BUFFER_DATA;
	__IO uint16_t* PRESS2_DATA = BUFFER_DATA + 1;
	__IO uint16_t* SUSP_DATA = BUFFER_DATA + 2;

	__IO uint16_t press1_value = 0;
	__IO uint16_t press2_value = 0;
	__IO uint16_t susp_value = 0;

#elif defined(_COG)

	__IO uint16_t* ACCX_DATA = BUFFER_DATA;
	__IO uint16_t* ACCY_DATA = BUFFER_DATA + 1;
	__IO uint16_t* ACCZ_DATA = BUFFER_DATA + 2;
	__IO uint16_t* GYRO_DATA = BUFFER_DATA + 3;

	__IO uint16_t accx_value = 0;
	__IO uint16_t accy_value = 0;
	__IO uint16_t accz_value = 0;
	__IO uint16_t gyro_value = 0;

#endif


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
void DMA_Config() {

#if defined(_PEDALI) || defined(_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || \
	defined(_FR_SX) || defined(_COG) || defined(_TEST_UP)

	// allocate DMA structure and init it to zero
	DMA_InitTypeDef 	DMA_InitStructure = {0};

	NVIC_InitTypeDef 	NVIC_InitStructure = {0};

	__IO uint32_t		timeout = TIMEOUT_MAX;

	// enable DMA clock for selected stream
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMA_InitStructure.DMA_Channel = DMA_CHANNEL;

	// size of buffer in memory in which transfer data
	DMA_InitStructure.DMA_BufferSize = BUFFER_CAPACITY;

	// pointer to buffer in memory
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) BUFFER_DATA;

	// pointer to source peripheral
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC_SOURCE -> DR;

	// one data transfer per each transaction
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	// only 16bit of ADCx->DR are relevant (upper 16bits are reserved)
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

	DMA_Init(DMA_STREAM, &DMA_InitStructure);

	/* enable DMA Transfer Complete interrupt */
	DMA_ITConfig(DMA_STREAM, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA_STREAM, ENABLE);

	// enable the DMA Stream IRQ Channel */
	NVIC_InitStructure.NVIC_IRQChannel = DMA_STREAM_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// wait until DMA Stream has been effectively enabled
	while ((DMA_GetCmdStatus(DMA_STREAM) != ENABLE) && (timeout-- > 0)) { }

	/* check if a timeout condition occurred */
	if (!timeout) {
	    for (;;) { }
	}
#endif
}
