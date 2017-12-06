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
#define VCU_STATE_ID		(0x20)
#define TIME_SLOT			(0x15)
#define FR_DX_ID			(0x50)
#define FR_SX_ID			(0x30)
#define RT_DX_ID			(0x60)
#define RT_SX_ID			(0x40)
#define CRUSCOTTO_ID		(0x25)
#define BATTERIA_ID			(0x35)
#define PEDALI_ID			(0x10)
#define COG_ID				(0x70)

void CAN_Config();

void CAN_Tx(uint8_t lenght, uint8_t data[lenght], uint32_t id);

void CAN_Manage_Rx(CanRxMsg* RxMessage);

#endif /* CAN_H_ */
