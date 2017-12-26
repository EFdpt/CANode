/*
 *  @file 		can.c
 *  @author		Arella Matteo
 *  @date 		9 nov 2017
 *  @brief		can.c module
 */

#include "can.h"
#include "dma.h"
#include "util/inc/net.h"

CanTxMsg tx_msg = {0};
CanRxMsg rx_msg = {0};

void CAN_Config() {

#if defined(_PEDALI) || defined(_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || \
	defined(_FR_SX) || defined(_COG) || defined(_TEST_UP)

	NVIC_InitTypeDef  NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef	CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	tx_msg.ExtId = CAN_ID;
	tx_msg.IDE = CAN_Id_Extended;
	tx_msg.RTR = CAN_RTR_DATA;

	/* Using CAN2 but for the fact CAN2 is slave CAN1 clock must be enabled too */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2 | RCC_APB1Periph_CAN1, ENABLE);

	/* Configure GPIO Pins for CAN2 */

	/* RX - PB5 */
	GPIO_InitStructure.GPIO_Pin = CAN_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(CAN_GPIO, &GPIO_InitStructure);

	/* TX - PB6 */
	GPIO_InitStructure.GPIO_Pin = CAN_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(CAN_GPIO, &GPIO_InitStructure);

	GPIO_PinAFConfig(CAN_GPIO, GPIO_PinSource5, GPIO_AF_CAN2);
	GPIO_PinAFConfig(CAN_GPIO, GPIO_PinSource6, GPIO_AF_CAN2);

	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = ENABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = ENABLE;	//abilitazione ritrasmissione NON automatica
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_OperatingMode_Normal;

	// TODO: fin qui tutto bene

	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_14tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_6tq;
	CAN_InitStructure.CAN_Prescaler = 2;//1Mb/s
	CAN_Init(CAN2, &CAN_InitStructure);

	//SYSCLK = 168MHz, HCLK = 168MHz, PCLK1 = 42MHz, PCLK2 = 84MHz

	/*
	 * CAN BaudRate = 1/NominalBitTime
	 * NominalBitTime =  1*tq + tBS1 + tBS2, where tq = prescaler * tPCLK (tPCLK = APB1 clock)
	 *  */

	/*
	 * Filter bank = 0, filter number = 2 -> 32bit mask
	*/
	CAN_FilterInitStructure.CAN_FilterNumber = 2; // o 9 se 16bit

	/**
	 * CAN_FM1R -> FBMx = 0
	 */
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;

	/**
	 * id mask a 32bit
	 */
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //32

	// TODO
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; //0000
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = (uint16_t) VCU_TIME_SLOT; //0000

	// end TODO

	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

}

static void CAN_pack_data() {
#if defined(_PEDALI)

	tx_msg.DLC = 6;
	*((uint16_t*) tx_msg.Data) = serializes(tps1_value);
	((uint16_t*) tx_msg.Data)[1] = serializes(tps2_value);
	((uint16_t*) tx_msg.Data)[2] = serializes(brake_data);

#elif defined(_RT_DX) || defined(_RT_SX)

	tx_msg.DLC = 2;
	*((uint16_t*) tx_msg.Data) = serializes(susp_value);

#elif defined(_FR_DX)

	tx_msg.DLC = 4;
	*((uint16_t*) tx_msg.Data) = serializes(susp_value);
	((uint16_t*) tx_msg.Data)[1] = serializes(steer_value);

#elif defined(_FR_SX)

	tx_msg.DLC = 6;
	*((uint16_t*) tx_msg.Data) = serializes(press1_value);
	((uint16_t*) tx_msg.Data)[1] = serializes(press2_value);
	((uint16_t*) tx_msg.Data)[2] = serializes(susp_value);


#elif defined(_COG) || defined(_TEST_UP)

	tx_msg.DLC = 8;
	*((uint16_t*) tx_msg.Data) = serializes(accx_value);
	((uint16_t*) tx_msg.Data)[1] = serializes(accy_value);
	((uint16_t*) tx_msg.Data)[2] = serializes(accz_value);
	((uint16_t*) tx_msg.Data)[3] = serializes(gyro_value);

#endif
}

inline void CAN_Tx() {
	CAN_pack_data();
	CAN_Transmit(CAN, &tx_msg);
}

uint8_t CAN_StatusControl(CAN_TypeDef* CANx) {
#if 0
	uint8_t CAN_LastErrorCode = CAN_GetLastErrorCode(CANx);
	uint8_t CAN_TEC = CAN_GetLSBTransmitErrorCounter(CANx);
	uint8_t CAN_REC = CAN_GetReceiveErrorCounter(CANx);

	if(CAN_LastErrorCode!=CAN_ErrorCode_NoErr)
		return CAN_LastErrorCode;

	if ((CAN_TEC >= 127) && (CAN_REC >= 127))
		return TEC_REC_ERROR;
	if(CAN_TEC >= 127)
		return TEC_ERROR;
	if(CAN_REC >= 127)
		return REC_ERROR;

	CAN_ClearFlag(CANx, CAN_FLAG_EWG);

	return CAN_ErrorCode_NoErr;
#endif
	return 0;
}

void CAN_DisableFilter(uint8_t CAN_FilterNum)
{
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	CAN_FilterInitStructure.CAN_FilterNumber = CAN_FilterNum;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = DISABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);
}


void CAN_SetFilter(uint16_t* ID, uint8_t IDcount, uint8_t CAN_FilterNum)
{
	uint8_t i;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	for (i = 0; i * 4 < IDcount; i++) {
		CAN_FilterInitStructure.CAN_FilterNumber = i+CAN_FilterNum;
		CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
		CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit;
		if ((IDcount - (i * 4)) > 0)
			CAN_FilterInitStructure.CAN_FilterIdHigh = ID[i * 4 + 0] << 5;
		if ((IDcount - (i * 4) - 1) > 0)
			CAN_FilterInitStructure.CAN_FilterIdLow = ID[i * 4 + 1] << 5;
		if ((IDcount - (i * 4) - 2) > 0)
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ID[i * 4 + 2] << 5;
		if ((IDcount - (i * 4) - 3) > 0)
			CAN_FilterInitStructure.CAN_FilterMaskIdLow = ID[i * 4 + 3] << 5;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
		CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);
	}
}


