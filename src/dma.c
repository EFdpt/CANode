/*
 *
 *
 */


#include "dma.h"

// statically allocate DMA structure and init it to zero
DMA_InitTypeDef DMA_InitStructure = {0};

/**
  * @brief  TODO
  * @param  None
  * @retval None
  */
void DMA_init() {

	// enable DMA clock
	RCC_AHB1PeriphClockCmd(DMA_STREAM_CLOCK, ENABLE);

	/* Reset DMA Stream registers */
	// DMA_DeInit(DMA_STREAM);

	DMA_InitStructure.DMA_BufferSize;
	DMA_InitStructure.DMA_Channel;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_FIFOMode;
	DMA_InitStructure.DMA_FIFOThreshold;
	DMA_InitStructure.DMA_Memory0BaseAddr;
	DMA_InitStructure.DMA_MemoryBurst;
	DMA_InitStructure.DMA_MemoryDataSize;
	DMA_InitStructure.DMA_MemoryInc;
	DMA_InitStructure.DMA_Mode;
	DMA_InitStructure.DMA_PeripheralBaseAddr = &GPIOA->IDR; // TODO: refer to specific board peripherical address
	DMA_InitStructure.DMA_PeripheralBurst;
	DMA_InitStructure.DMA_PeripheralDataSize;
	DMA_InitStructure.DMA_PeripheralInc;
	DMA_InitStructure.DMA_Priority;

	DMA_Init(DMA_STREAM, &DMA_InitStructure);
	DMA_Cmd(DMA_STREAM, ENABLE);

	// wait until DMA Stream has been effectively enabled
	while (DMA_GetCmdStatus(DMA_STREAM) != ENABLE) { }
}
