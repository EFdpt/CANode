/*
 * can.h
 *
 *  Created on: Jan 11, 2015
 *      Author: Simone Palombi
 */

#ifndef CAN_H_
#define CAN_H_

#include "include.h"

//CAN1->Master ???
//CAN2->Slave  ???

//CAN defines
#define CAN				CAN2

//defines FILTER_NUM
#define CAN_Filt_Num		14

#define N_FILTER			1

//Controllo errori
#define TEC_REC_ERROR	1	//Sia TEC che REC maggiori di 127
#define TEC_ERROR		2	//TEC maggiore di 127
#define REC_ERROR		3	//REC maggiore di 127

void CAN_init();

//CANx can be one of the CAN defines
void CAN_Tx(uint8_t lenght, uint8_t Data[lenght], uint32_t ID, CAN_TypeDef* CANx);
void CAN2_RX0_IRQHandler(void);
void CAN_BMS_Manage_Rx(CanRxMsg RxMessage);
void CAN_Manage_Rx(CanRxMsg RxMessage);
uint8_t CAN_StatusControl(CAN_TypeDef* CANx);

//CAN_FilterNum can be one of the defines FILTER_NUM
void CAN_SetFilter(uint16_t* ID, uint8_t IDcount, uint8_t CAN_FilterNum);
void CAN_DisableFilter(uint8_t CAN_FilterNum);

#endif /* CAN_H_ */
