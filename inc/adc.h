/**
 *
 *
 *
 **/

#ifndef ADC_H_
#define ADC_H_

#include "include.h"
#define ADCrd1ch ADC_Channel_7	//PA7 molex11
#define ADCrd2ch ADC_Channel_3	//PA3 molex13
#define ADCrd3ch ADC_Channel_9	//PB1 molex2
#define ADCrd4ch ADC_Channel_15	//PC5 molex3

#if defined(_PEDALI)
#define brake ADCrd3ch
#define tps1 ADCrd1ch
#define tps2 ADCrd2ch

#elif defined(_RT_DX) || defined(_RT_SX)
#define susp ADCrd1ch

#elif defined(_FR_DX)
#define susp ADCrd1ch
#define steer ADCrd2ch

#elif defined(_FR_SX)
#define susp ADCrd1ch
#define press1 ADCrd2ch
#define press2 ADCrd3ch

#elif defined(_COG) || defined(_TEST_UP)
#define accx ADCrd1ch
#define accy ADCrd2ch
#define accz ADCrd3ch
#define gyro ADCrd4ch

#endif


void ADC_Config(void);

#endif	//ADC_H_
