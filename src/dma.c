/*
 *  @file 		dma.c
 *  @author		Arella Matteo
 *  @date 		14 set 2017
 *  @brief		dma.c module
 */

#include "dma.h"

uint16_t DMA_DATA[BUFFER_SIZE];

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

	DMA_InitStructure.DMA_Channel = DMA_CHANNEL;
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) DMA_DATA;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &PERIPHERAL_ADDR;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; // direct mode
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;

	DMA_Init(DMA_STREAM, &DMA_InitStructure);
	DMA_Cmd(DMA_STREAM, ENABLE);

	// wait until DMA Stream has been effectively enabled
	while (DMA_GetCmdStatus(DMA_STREAM) != ENABLE) { }
}
