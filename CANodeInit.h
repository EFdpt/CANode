/*
 * CANodeInit.h
 *
 *  	@date: 29 mar 2017
 *      @author: Valerio Dodet
 *      @brief: Hardware initialization for CANode board v1.18
 *
 */

#include "stm32f4xx.h"


#ifndef CANODEINIT_H_
#define CANODEINIT_H_

/*
 * Definizione nomi schede
 *	board_table[current_board]();
 * */
typedef enum {PEDALI, CRUSCOTTO, FR_DX, FR_SX, RT_DX, RT_SX, BATTERIA, COG} tipoScheda;

/*
 * @brief: selezione delle funzioni della scheda
 * @note: questa funzione va richiamata nel main per configurare le funzioni secondarie
 *  		dei GPIO
 * @params: tipoScheda può essere una tra:
 * 			PEDALI, CRUSCOTTO, FR_DX, FR_SX, RT_DX, RT_SX, BATTERIA
 *
 * */
void Init_Board(tipoScheda posizione);

void HSESwitch();

void GPIOInit();


#endif /* CANODEINIT_H_ */
