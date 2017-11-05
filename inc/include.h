/*
 * 		include.h
 *
 *      Author: Valerio Dodet
 *
 */

#ifndef INCLUDE_H_
#define INCLUDE_H_

// define here which board to use
//#define _FR_DX
//#define _FR_SX
//#define _RT_DX
//#define _RT_SX
//#define _CRUSCOTTO
//#define _BATTERIA
//#define _PEDALI
//#define _TEST_DOWN
#define _TEST_UP
//#define _COG

#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "can.h"
#include "ID_CAN.h"

#include "rcc.h"
#include "inverter.h"
#include "board.h"
#include "adc.h"
#include "dma.h"

#endif /* INCLUDE_H_ */
