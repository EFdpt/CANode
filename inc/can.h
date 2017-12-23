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
#define VCU_TIME_SLOT		(0x15)
#define FR_DX_ID			(0x50)
#define FR_SX_ID			(0x30)
#define RT_DX_ID			(0x60)
#define RT_SX_ID			(0x40)
#define CRUSCOTTO_ID		(0x25)
#define BATTERIA_ID			(0x35)
#define PEDALI_ID			(0x10)
#define COG_ID				(0x70)

#define CAN					CAN2
#define CAN_FIFO			CAN_FIFO0

#if defined(_PEDALI)

	#define CAN_ID			PEDALI_ID

#elif defined(_RT_DX)

	#define CAN_ID 			RT_DX_ID

#elif defined(_RT_SX)

	#define CAN_ID			RT_SX_ID

#elif defined(_FR_DX)

	#define CAN_ID			FR_DX_ID

#elif defined(_FR_SX)

	#define CAN_ID			FR_SX_ID

#elif defined(_COG) || defined(_TEST_UP)

	#define CAN_ID			COG_ID

#elif defined(_CRUSCOTTO)

	#define CAN_ID			CRUSCOTTO_ID

#elif defined(_BATTERIA)

	#define CAN_ID			BATTERIA_ID

#endif

extern CanTxMsg tx_msg;
extern CanRxMsg rx_msg;

void CAN_Config();

void CAN_pack_data();

void CAN_Tx();

#endif /* CAN_H_ */
