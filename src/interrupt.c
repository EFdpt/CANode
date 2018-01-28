#include "interrupt.h"

#include "dma.h"
#include "filter.h"

/*	TODO
 * PVD interrupt monitora la tensione di alimentazione
 * per proteggere il processore proverei a spegnerlo via software
 * e per notificare questa situazione manderei un pacchetto via CAN
 * con la tensione critica che è stata rivelata e il nome della scheda*/
void PVD_IRQHandler(void){

}


/*gli interrupt di tutti gli ADC sono generici, viene alzato sempre questo interrupt
 * bisogna controllare quale flag è stato asserita per capire cosa è successo
 *TODO OVR, EOC, AWD*/
void ADC_IRQHandler(void){

	if(ADC_GetITStatus(ADC1,ADC_IT_EOC)!=RESET){
		//do something alla fine della conversione

		ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
	}
	else if(ADC_GetITStatus(ADC1,ADC_IT_AWD)!=RESET){
		//un regular channel è andato oltre le soglie

		ADC_ClearITPendingBit(ADC1,ADC_IT_AWD);
	}
	else if(ADC_GetITStatus(ADC1,ADC_IT_OVR)!=RESET){
		//l'ADC1 è andato in OVERRUN!! DMA disabilitate, tocca farle ripartire pag 400 RM0090

		ADC_ClearITPendingBit(ADC1,ADC_IT_OVR);

	}

}

//TODO
void CAN2_TX_IRQHandler(void){

}


/**
 * @author	Arella Matteo & Valerio Dodet
 * @brief 	Copy data to destination buffer after DMA transfers complete, and filter value
 * 			The pickup_value is computed immediately.
 * @param	None
 * @retval	None
 * @update 19 Jan 2018
 */
void DMA2_IRQHandler(void) {

	if (DMA_GetITStatus(DMA_STREAM, DMA_IT_FIFO) == SET) {

		// all data have been transfered by DMA so now copy to sensor's buffers
		copy_to_buffers();

		/* Clear DMA Stream Transfer Complete interrupt pending bit */
		DMA_ClearITPendingBit(DMA_STREAM, DMA_IT_FIFO);

		// filter acquired data
		filter_data();
	}

#if defined (_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || defined(_FR_SX)

	if (DMA_GetITStatus(PICKUP_DMA_STREAM, PICKUP_DMA_IT_TRANSF) == SET) {
		(pickup_buffer_pos<31) ? (pickup_buffer_pos+=1) : (pickup_buffer_pos=0);

		/* Clear DMA Stream Transfer Complete interrupt pending bit */
		DMA_ClearITPendingBit(PICKUP_DMA_STREAM, DMA_IT_TCIF3);

		// get rpm*40 value of wheel's speed
		pickup_value = (uint16_t) RPM_CONST/PICKUP_BUFFER_DATA[(pickup_buffer_pos == 0) ? 31 : (pickup_buffer_pos-1)];
	}

#endif
}

/**
 * @author	Arella Matteo
 * @brief 	Receive VCU synch packet and start transmission timer
 * @param	None
 * @retval	None
 */
void CAN2_RX0_IRQHandler(void){

	CanRxMsg RxMessage;

	CAN_Receive(CAN, CAN_FIFO, &RxMessage);

	// se pacchetto di synch della VCU (unico ricevuto dopo filtraggio hardware) avvia il timer per l'offset
	if(RxMessage.ExtId & VCU_TIME_SLOT) {

		if (RxMessage.Data[0] == DRIVE) {

			model_goto_drive();
		}

		// ferma SysTick (disable timer exceptions & system timer)
		SysTick -> CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

		TIM_start(OFFSET_TIMER);
	}
}

/**
 * @author	Arella Matteo
 * @brief 	Transmit first CAN packet and start periodic systick timer
 * @param	None
 * @retval	None
 */
void TIM3_IRQHandler(void){

	if (TIM_GetITStatus(OFFSET_TIMER, TIM_IT_Update) == SET) {

		CanTxMsg 	msg;

		TIM_ClearITPendingBit(OFFSET_TIMER, TIM_IT_Update);

		CAN_Tx(&msg);

		// enable systick (timer periodico di spedizione pacchetti)
		SysTick_Config(SystemCoreClock / SYSTIMER_PERIOD_PRESCALER);

		TIM_stop(OFFSET_TIMER);
	}
}

/**
 *  @Author Valerio Dodet
 * @brief  This function handles the interrupt request when the counter of TIM1
 * runs out of the autoreload value. This event means that the wheel doesn't move.
 * The auto reload value should be used for the actual value of the wheel rpm BUT the
 * immediately next rising edge of the TIM1_IC has to be ignored by the DMA
 * @param  None
 * @retval None
 */
//TODO in slave mode reset the update event triggers the DMA. How can we recognise the OVR? T_T
void TIM1_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		//TODO DMA start for counter=0

		/* Clear TIM1 Capture compare interrupt pending bit */
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}

/**
 * @author	Arella Matteo
 * @brief 	Transmit CAN packet periodically
 * @param	None
 * @retval	None
 */
void SysTick_Handler(void) {
	CanTxMsg 	msg;
	CAN_Tx(&msg);
}
