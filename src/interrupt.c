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

/**
 * @author	Arella Matteo
 * @brief 	Copy data to destination buffer after DMA transfers complete, and filter value
 * @param	None
 * @retval	None
 */
void DMA_IRQHandler() {

	if (DMA_GetITStatus(DMA_STREAM, DMA_IT_FIFO) == SET) {

		// all data have been transfered by DMA so now copy to sensor's buffers
		copy_to_buffers();

		/* Clear DMA Stream Transfer Complete interrupt pending bit */
	    DMA_ClearITPendingBit(DMA_STREAM, DMA_IT_FIFO);

	    // filter acquired data
	    filter_data();
	}
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

		// ferma SysTick (disable timer exceptions & system timer)
		SysTick -> CTRL &= ~(SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

		TIM_start();
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

		TIM_ClearITPendingBit(OFFSET_TIMER, TIM_IT_Update);

		CAN_Tx();

		// enable systick (timer periodico di spedizione pacchetti)
		SysTick_Config(SystemCoreClock / SYSTIMER_PERIOD_PRESCALER);

		TIM_stop();
	}
}

/**
 * @author	Arella Matteo
 * @brief 	Transmit CAN packet periodically
 * @param	None
 * @retval	None
 */
void SysTick_Handler(void) {
	CAN_Tx();
}
