/**
 *
 *
 *
 **/

#ifndef ADC_H_
#define ADC_H_

#include "include.h"
#define ADCrd1ch ADC_Channel_7
#define ADCrd2ch ADC_Channel_3
#define ADCrd3ch ADC_Channel_9
#define ADCrd4ch ADC_Channel_15

#ifdef _PEDALI
#define brake ADCrd3ch
#define tps1 ADCrd1ch
#define tps2 ADCrd2ch
#endif


	void ADC_Config(void);

#endif	//ADC_H_
