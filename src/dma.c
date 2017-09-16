/*
 *  @file 		dma.c
 *  @author		Arella Matteo
 *  @date 		14 set 2017
 *  @brief		dma.c module
 */

#include "dma.h"

uint16_t DMA_DATA[BUFFER_SIZE];

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
	// statically allocate DMA structure and init it to zero
	DMA_InitTypeDef DMA_InitStructure = {0};
	__IO uint32_t	timeout = TIMEOUT_MAX;

	// enable DMA clock for selected stream
	RCC_AHB1PeriphClockCmd(DMA_STREAM_CLOCK, ENABLE);

	DMA_InitStructure.DMA_Channel = DMA_CHANNEL;

	// size of buffer in memory in which transfer data
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;

	// pointer to buffer in memory
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) DMA_DATA;

	// pointer to source peripheral
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &PERIPHERAL_ADDR;

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

	DMA_Init(DMA_STREAM, &DMA_InitStructure);
	DMA_Cmd(DMA_STREAM, ENABLE);

	// wait until DMA Stream has been effectively enabled
	while ((DMA_GetCmdStatus(DMA_STREAM) != ENABLE) && (timeout-- > 0)) { }

	/* check if a timeout condition occurred */
	if (!timeout) {
	    /* manage the error: to simplify the code enter an infinite loop */
	    for (;;) { }
	}
}
