#include "adc.h"

//TODO ADC_Config
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
 * */
void ADC_Config(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;


  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

#ifdef _PEDALI

  ADC_DeInit();	//reset default config

  //	ADC1 Peripheral Clock Enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);


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
  ADC_RegularChannelConfig(ADC1, ADCrd1ch, 1, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, ADCrd2ch, 2, ADC_SampleTime_144Cycles);
  ADC_RegularChannelConfig(ADC1, ADCrd3ch, 3, ADC_SampleTime_144Cycles);

  /*il bit EOC è asserito ad ogni conversione per canali regolari
   * ogni volta che EOC==1 viene fatto un DMA se abilitato*/
  ADC_EOCOnEachRegularChannelCmd(ADC1,ENABLE);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

#elif _CRUSCOTTO
  ADC_DeInit();	//reset default config

#elif _FR_DX || defined _FR_SX || defined _RT_DX || defined _RT_SX
  ADC_DeInit();	//reset default config

  #endif

}
