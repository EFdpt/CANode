/*
 *  @file 		can.h
 *  @author		Arella Matteo
 *  @date 		9 nov 2017
 *  @brief		Header for can.c module
 */

#ifndef CAN_H_
#define CAN_H_

#include "include.h"

/**
 * 	packets ID
 */
#define VCU_EVENT_ID		(0x00000022)

#define FR_DX_ID			(0x00000001)
#define FR_SX_ID			(0x00000002)
#define RT_DX_ID			(0x00000004)
#define RT_SX_ID			(0x00000008)
#define CRUSCOTTO_ID		(0x00000010)
#define BATTERIA_ID			(0x00000020)
#define PEDALI_ID			(0x00000040)
#define COG_ID				(0x00000080)

void CAN_Config();

void CAN_Tx(uint8_t lenght, uint8_t data[lenght], uint32_t id);

void CAN_Manage_Rx(CanRxMsg* RxMessage);

#endif /* CAN_H_ */
