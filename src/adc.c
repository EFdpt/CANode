#include "adc.h"

/*i registri per le acquisizioni sono
 * ADC_DR per i regular channel
 * ADC_CDR, due acquisizioni per i modi dual e triple
 * 4x ADC_JDRx, quattro acquisizioni per gli injected channel
 * l'associazione pin-channel è univoca, vedi gdoc "nodoCAN"
 *
 * provo ad utilizzare solo l'ADC1 su canali diversi, in modo da diminuire il consumo
 * il rischio è l'insorgenza di crosschanneling, la tensione su un canale potrebbe
 * influenzarne un altro vicino
 * ADCrd1	:	PA7	:	12CH7
 * ADCrd2	:	PA3	:	123CH3
 * ADCrd3	:	PB1	:	12CH9
 * ADCrd4	:	PC5	:	12CH15
 *
 *
 * */
void ADC_Config(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  ADC_DeInit();	//reset default config

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

#if defined(_PEDALI)

  //	ADC1 Peripheral Clock Enable
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


  /* ADC Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;	//12bit
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;				//ADC1 scandisce i canali 7 3 e 9
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//conversioni continue
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //nessun trigger edge esterno
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;	//TIM1 trigger, ma nessun trigger abilitato
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//allineamento a destra
  ADC_InitStructure.ADC_NbrOfConversion = 3;				//3 conversioni per sequenza
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 configurazione canali, ordine di scansione e sample time **************************************/
  ADC_RegularChannelConfig(ADC1, tps1, 1, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, tps2, 2, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, brake, 3, ADC_SampleTime_144Cycles);

  /*configurazione watchdog analogici*****************************************************
   * */
  ADC_AnalogWatchdogThresholdsConfig(ADC1, 4095, 0);	//FIXME high threshold and low threshold
  //ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_x);	//un solo canale controllato dal watchdog
  ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_AllRegEnable);	//modalità watchdog su tutti i canali di ADC1

  /*abilitazione Interrupt per ADC1*/
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);	//End of conversion, EOCIE=1 ogni conversione regolare
  ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);	//Overrun
  ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);	//analog Watchdog


  /*il bit EOC è asserito ad ogni conversione per canali regolari
   * ogni volta che EOC==1 viene fatto un DMA se abilitato*/
  ADC_EOCOnEachRegularChannelCmd(ADC1,ENABLE);

  /*Abilitate le richieste DMA della periferica ADC1*/
  ADC_DMACmd(ADC1, ENABLE);

  /*questa funzione dovrebbe permettere l'abilitazione continua di richieste DMA*/
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

#elif defined (_CRUSCOTTO) || defined (_TEST_DOWN)

#elif defined (_RT_DX) || defined (_RT_SX)
  //	ADC1 Peripheral Clock Enable
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


  /* ADC Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;	//12bit
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;				//ADC1 nessuna scansione
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//conversioni continue
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //nessun trigger edge esterno
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;	//TIM1 trigger, ma nessun trigger abilitato
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//allineamento a destra
  ADC_InitStructure.ADC_NbrOfConversion = 1;				//1 conversioni per sequenza
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 configurazione canali, ordine di scansione e sample time **************************************/
  ADC_RegularChannelConfig(ADC1, susp, 1, ADC_SampleTime_144Cycles);

  /*configurazione watchdog analogici*****************************************************
   * */
  ADC_AnalogWatchdogThresholdsConfig(ADC1, 4095, 0);	//FIXME high threshold and low threshold
  ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_7);	//un solo canale controllato dal watchdog
  ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_SingleRegEnable);	//modalità watchdog su un canale di ADC1

  /*abilitazione Interrupt per ADC1*/
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);	//End of conversion, EOCIE=1 ogni conversione regolare
  ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);	//Overrun
  ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);	//analog Watchdog


  /*il bit EOC è asserito ad ogni conversione per canali regolari
   * ogni volta che EOC==1 viene fatto un DMA se abilitato*/
  ADC_EOCOnEachRegularChannelCmd(ADC1,ENABLE);

  /*Abilitate le richieste DMA della periferica ADC1*/
  ADC_DMACmd(ADC1, ENABLE);

  /*questa funzione dovrebbe permettere l'abilitazione continua di richieste DMA*/
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);


#elif defined (_FR_DX)
  //	ADC1 Peripheral Clock Enable
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


  /* ADC Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;	//12bit
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;				//ADC1 scandisce i canali 7 3
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//conversioni continue
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //nessun trigger edge esterno
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;	//TIM1 trigger, ma nessun trigger abilitato
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//allineamento a destra
  ADC_InitStructure.ADC_NbrOfConversion = 2;				//2 conversioni per sequenza
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 configurazione canali, ordine di scansione e sample time **************************************/
  ADC_RegularChannelConfig(ADC1, susp, 1, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, steer, 2, ADC_SampleTime_144Cycles);

  /*configurazione watchdog analogici*****************************************************
   * */
  ADC_AnalogWatchdogThresholdsConfig(ADC1, 4095, 0);	//FIXME high threshold and low threshold
  //ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_x);	//un solo canale controllato dal watchdog
  ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_AllRegEnable);	//modalità watchdog su tutti i canali di ADC1

  /*abilitazione Interrupt per ADC1*/
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);	//End of conversion, EOCIE=1 ogni conversione regolare
  ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);	//Overrun
  ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);	//analog Watchdog


  /*il bit EOC è asserito ad ogni conversione per canali regolari
   * ogni volta che EOC==1 viene fatto un DMA se abilitato*/
  ADC_EOCOnEachRegularChannelCmd(ADC1,ENABLE);

  /*Abilitate le richieste DMA della periferica ADC1*/
  ADC_DMACmd(ADC1, ENABLE);

  /*questa funzione dovrebbe permettere l'abilitazione continua di richieste DMA*/
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);


#elif defined (_FR_SX)

  //	ADC1 Peripheral Clock Enable
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


  /* ADC Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;	//12bit
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;				//ADC1 scandisce i canali 7 3 e 9
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//conversioni continue
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //nessun trigger edge esterno
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;	//TIM1 trigger, ma nessun trigger abilitato
  ADC_InitStructure.ADC_NbrOfConversion = 3;				//3 conversioni per sequenza
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//allineamento a destra
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 configurazione canali, ordine di scansione e sample time **************************************/
  ADC_RegularChannelConfig(ADC1, press1, 1, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, press2, 2, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, susp, 3, ADC_SampleTime_144Cycles);

  /*configurazione watchdog analogici*****************************************************
   * */
  ADC_AnalogWatchdogThresholdsConfig(ADC1, 4095, 0);	//FIXME high threshold and low threshold
  //ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_x);	//un solo canale controllato dal watchdog
  ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_AllRegEnable);	//modalità watchdog su tutti i canali di ADC1

  /*abilitazione Interrupt per ADC1*/
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);	//End of conversion, EOCIE=1 ogni conversione regolare
  ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);	//Overrun
  ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);	//analog Watchdog


  /*il bit EOC è asserito ad ogni conversione per canali regolari
   * ogni volta che EOC==1 viene fatto un DMA se abilitato*/
  ADC_EOCOnEachRegularChannelCmd(ADC1,ENABLE);

  /*Abilitate le richieste DMA della periferica ADC1*/
  ADC_DMACmd(ADC1, ENABLE);

  /*questa funzione dovrebbe permettere l'abilitazione continua di richieste DMA*/
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

#elif defined (_COG) || defined(_TEST_UP)

  //	ADC1 Peripheral Clock Enable
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


  /* ADC Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;	//12bit
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;				//ADC1 scandisce i canali 7 3 9 e 15
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		//conversioni continue
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //nessun trigger edge esterno
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;	//TIM1 trigger, ma nessun trigger abilitato
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//allineamento a destra
  ADC_InitStructure.ADC_NbrOfConversion = 4;				//4 conversioni per sequenza
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 configurazione canali, ordine di scansione e sample time **************************************/
  ADC_RegularChannelConfig(ADC1, accx, 1, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, accy, 2, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, accz, 3, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, gyro, 4, ADC_SampleTime_144Cycles);

  /*configurazione watchdog analogici*****************************************************
   * */
  ADC_AnalogWatchdogThresholdsConfig(ADC1, 4095, 0);	//FIXME high threshold and low threshold
  //ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_x);	//un solo canale controllato dal watchdog
  ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_AllRegEnable);	//modalità watchdog su tutti i canali di ADC1

  /*abilitazione Interrupt per ADC1*/
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);	//End of conversion, EOCIE=1 ogni conversione regolare
  ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);	//Overrun
  ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);	//analog Watchdog


  /*il bit EOC è asserito ad ogni conversione per canali regolari
   * ogni volta che EOC==1 viene fatto un DMA se abilitato*/
  ADC_EOCOnEachRegularChannelCmd(ADC1,ENABLE);

  /*Abilitate le richieste DMA della periferica ADC1*/
  ADC_DMACmd(ADC1, ENABLE);

  /*questa funzione dovrebbe permettere l'abilitazione continua di richieste DMA*/
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

#else
	#error "Nessuna scheda definita"

  #endif

}
