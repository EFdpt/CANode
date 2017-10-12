/**
 *
 * @author: Valerio Dodet
 * @brief: declare functions to initialize the board
 *
 * */

#ifndef BOARD_H_
#define	BOARD_H_

#include "include.h"

/*definizione dei pin utilizzati sul microproc*/
//Power management
#define en5			GPIO_Pin_15	//GPIOB
#define LSfet		en5
#define en21		GPIO_Pin_0	//GPIOB
#define en23		GPIO_Pin_6	//GPIOA
#define en22		GPIO_Pin_4	//GPIOC
#define EnADC12		GPIO_Pin_10	//GPIOB
#define EnADC34		GPIO_Pin_11	//GPIOB


// Analog sensors
#define ADCrd1		GPIO_Pin_7	//GPIOA
#define ADCrd2		GPIO_Pin_3	//GPIOA
#define ADCrd3		GPIO_Pin_1	//GPIOB
#define ADCrd4		GPIO_Pin_5	//GPIOC
#define sens12V		GPIO_Pin_2	//GPIOA
#define tempRD		GPIO_Pin_0	//GPIOA

#define DAC1        GPIO_Pin_4
#define DAC2        GPIO_Pin_5
#define DAC_GPIO	GPIOA

//comunications and digitals
#define	CAN_RX		GPIO_Pin_5
#define	CAN_TX		GPIO_Pin_6
#define ASCan		GPIO_Pin_13
#define CAN_GPIO	GPIOB

#define SCK3		GPIO_Pin_10
#define	MOSI3		GPIO_Pin_12
#define	MISO3		GPIO_Pin_11
#define	SPI_GPIO	GPIOC

#define	I2C1sda		GPIO_Pin_9
#define	I2C1scl		GPIO_Pin_8
#define	I2C1_GPIO	GPIOB

#define	USART1tx	GPIO_Pin_9
#define	USART1rx	GPIO_Pin_10
#define	USART1cts	GPIO_Pin_11
#define	USART1rts	GPIO_Pin_12
#define	USART1_GPIO	GPIOA

#define	ENRS		GPIO_Pin_6
#define	HDPLX		GPIO_Pin_7
#define	RSelect		GPIO_Pin_8
#define	SpeedRS		GPIO_Pin_9
#define RS_GPIO		GPIOC

#define ENMux		GPIO_Pin_7	//GPIOB
#define Mux0		GPIO_Pin_2	//GPIOD
#define Mux1		GPIO_Pin_4	//GPIOB

#define	MCO1		GPIO_Pin_8	//GPIOA
#define dg11		GPIO_Pin_0	//GPIOC
#define dg21		GPIO_Pin_2	//GPIOC
#define dg31		GPIO_Pin_12	//GPIOB
#define dg41		GPIO_Pin_14	//GPIOB


#ifdef _PEDALI

#define throttle_1		ADCrd1
#define throttle_2		ADCrd2
#define brakePot		ADCrd3

#elif defined _FR_DX

#define pickup			SCK3
#define sospFrDx 		ADCrd1
#define SteerAng		ADCrd2
#define	sospSupply		en21
#define	pickupSupply	en22
#define SteerAngSupply	en23

#elif defined _CRUSCOTTO

#define pot1			ADCrd1
#define pot2			ADCrd2

#endif

/* con i define si riesce a ridurre
 * il codice compilato a quello dedicato alla scheda scelta
 * */
//typedef enum {PEDALI, CRUSCOTTO, FR_DX, FR_SX, RT_DX, RT_SX, BATTERIA, COG} tipoScheda;

/*
 * @brief: selezione delle funzioni della scheda
 * @note: questa funzione va richiamata nel main per configurare le funzioni secondarie
 *  		dei GPIO
 * @params: tipoScheda pu� essere una tra:
 * PEDALI, CRUSCOTTO, FR_DX, FR_SX, RT_DX, RT_SX, BATTERIA
 *
 * */
void Init_Board();

void GPIO_init(GPIO_TypeDef* GPIOx, uint32_t Pin, GPIOMode_TypeDef Mode, GPIOOType_TypeDef OType, GPIOSpeed_TypeDef Speed, GPIOPuPd_TypeDef PuPd);

#endif /* BOARD_H_ */
