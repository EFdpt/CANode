#include "include.h"


/**
 *  @mainpage FastChargeSAE CANode firmware
 *
 *	Il firmware per ogni nodo è selezionabile in fase di precompilazione del
 *	codice dalle direttive presenti in @ref CANode_selection.
 *
 *
 *  @section Pedaliera
 *  Il firmware per il nodo PEDALIERA effettua due azioni principali:
 *  	- Acquisizione sensori
 *  	- Trasmissione valori
 *
 *  	@subsection Acquisizione
 *			Viene configurato l'ADC in modo continuo per acquisire i valori
 *			del tps1, tps2 e del brake. Ogni volta che l'ADC termina una conversione,
 *			il DMA viene triggerato per trasferire il dato in un buffer in memoria.
 *			Non appena il buffer viene riempito i dati memorizzati nel buffer vengono
 *			filtrati e vengono aggiornati i valori correnti di ciascuna variabile.
 *
 *		@subsection Trasmissione
 *			La VCU spedisce periodicamente dei messaggi CAN di temporizzazione.
 *			Il canale di comunicazione viene quindi multiplato a divisione di tempo, dove ogni nodo
 *			possiede uno slot trasmissivo.
 *			Non appena il nodo PEDALIERA riceve un pacchetto dalla VCU fa partire un timer
 *			di offset.
 *			Allo scadere del timer di offset, il nodo PEDALIERA comincia a trasmettere ad intervalli
 *			di \#SYSTIMER_PERIOD_PRESCALER in modo periodico.
 *			Ciascuna trasmissione prevede le seguenti fasi:
 *			  - pacchettizzazione dei valori acquisiti in un frame CAN
 *			  - spedizione del frame
 *
 *
 */
int main(void) {

	SystemInit();

	Init_Board();

	while(1) {
	}
}
