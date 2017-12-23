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

void CAN2_RX0_IRQHandler(void){

	CanRxMsg RxMessage;

	CAN_Receive(CAN, CAN_FIFO, &RxMessage);

	// se pacchetto di synch della VCU (unico ricevuto dopo filtraggio hardware) avvia il timer
	if(RxMessage.ExtId == VCU_TIME_SLOT)
		TIM_start();
}

/**
 * @brief 	Pack data into CAN packet and transmit it when timer occurs
 * @param	None
 * @retval	None
 */
void TIM3_IRQHandler(void){

	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) {
		ATOMIC();

		CAN_pack_data();
		CAN_Tx();

		END_ATOMIC();
	}

	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
}
