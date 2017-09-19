/*
 *  @file 		dma.c
 *  @author		Arella Matteo
 *  @date 		14 set 2017
 *  @brief		dma.c module
 */

#include "dma.h"

#ifdef _PEDALI
	__IO uint16_t THROTTLE_1_DATA[BUFFER_CAPACITY];
	__IO uint16_t THROTTLE_2_DATA[BUFFER_CAPACITY];
	__IO uint16_t BRAKE_DATA[BUFFER_CAPACITY];
	__IO uint16_t PLAUS_1_DATA[BUFFER_CAPACITY];
	__IO uint16_t PLAUS_2_DATA[BUFFER_CAPACITY];
#elif defined _CRUSCOTTO

#elif defined _FR_DX

#elif defined _FR_SX

#elif defined _RT_DX

#elif defined _RT_SX

#elif defined _BATTERIA

#else
	#error "No board specified"
#endif

static inline void _DMA_Config(DMA_Stream_TypeDef* DMA_Stream,
						uint32_t DMA_Stream_Clock,
						uint32_t DMA_Channel,
						uint32_t peripheral_src, uint32_t memory_dest,
						uint32_t buffer_size, uint8_t DMA_Stream_IRQ);

static inline void DMA_Timer_Config(uint32_t DMA_Timer_Clock,
						TIM_TypeDef* DMA_Timer,
						uint32_t period, uint16_t prescaler,
						uint16_t clock_division);

void DMA_Config() {

#ifdef _PEDALI

	// switch freno
	_DMA_Config(DMA_STREAM, DMA_STREAM_CLOCK,
					DMA_CHANNEL,
					(uint32_t) &GPIOA->IDR, (uint32_t) BRAKE_DATA,
					BUFFER_CAPACITY, DMA_STREAM_IRQ);
	DMA_Timer_Config(RCC_APB2Periph_TIM8, TIM8, DMA_TIMER_PERIODE,
					DMA_TIMER_PRESCALER, DMA_TIMER_CLOCK_DIVISION);

	// acceleratore 1
//	_DMA_Config();

	// acceleratore 2
//	_DMA_Config();

	// pressione freno anteriore
//	_DMA_Config();

	// pressione freno posteriore
//	_DMA_Config();

#elif defined _CRUSCOTTO

#elif defined _FR_DX

#elif defined _FR_SX

#elif defined _RT_DX

#elif defined _RT_SX

#elif defined _BATTERIA

#else
	#error "No board specified"
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
	    for (;;) { }
	}
}

static inline void DMA_Timer_Config(uint32_t DMA_Timer_Clock,
									TIM_TypeDef* DMA_Timer,
									uint32_t period, uint16_t prescaler,
									uint16_t clock_division) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure = {0};

	// clock enable
	RCC_APB2PeriphClockCmd(DMA_Timer_Clock, ENABLE);

	// timer init
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = clock_division;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(DMA_Timer, &TIM_TimeBaseStructure);

	TIM_ITConfig(DMA_Timer, TIM_IT_Update, ENABLE);
	TIM_DMAConfig(DMA_Timer, 0, TIM_DMABurstLength_1Transfer);
	TIM_DMACmd(DMA_Timer, TIM_DMA_Update | TIM_DMA_Trigger | TIM_DMA_COM, ENABLE);
	TIM_SelectOutputTrigger(DMA_Timer, TIM_TRGOSource_Update);
	TIM_Cmd(DMA_Timer, ENABLE);
}

#if 0
void TIM5_IRQHandler(void) {
 if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
 {
    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

    /*code related to app */
 }
}

void DMA_STREAM_IRQHANDLER() {
	if (DMA_GetITStatus(DMA_STREAM, DMA_IT_TCIF))
		DMA_ClearITPendingBit(DMA_STREAM, DMA_IT_TCIF);
}
#endif
