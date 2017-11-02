#include "include.h"

CanTxMsg TxMessage;
uint16_t i=0;

extern uint16_t bus_state, IPackMsr, SoCMsr, TTabAvg, TTabHigh;
extern uint32_t potVCU;

/**/
void CAN_init()
{
	NVIC_InitTypeDef  NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef	CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/*devono essere abilitate CAN1 e CAN2 poiché CAN2 è slave
	 * */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2 | RCC_APB1Periph_CAN1, ENABLE);

	//RX
	GPIO_InitStructure.GPIO_Pin = CAN_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(CAN_GPIO, &GPIO_InitStructure);

	//TX
	GPIO_InitStructure.GPIO_Pin = CAN_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(CAN_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ASCan;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(CAN_GPIO, &GPIO_InitStructure);

	GPIO_PinAFConfig(CAN_GPIO, GPIO_PinSource5, GPIO_AF_CAN2);
	GPIO_PinAFConfig(CAN_GPIO, GPIO_PinSource6, GPIO_AF_CAN2);

	//inizializzazione default
	CAN_DeInit(CAN);
	CAN_StructInit(&CAN_InitStructure);

	//inizializzazione vera
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = ENABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = ENABLE;	//abilitazione ritrasmissione NON automatica
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1 = CAN_BS1_14tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_6tq;
	CAN_InitStructure.CAN_Prescaler = 2;//1Mb/s
	CAN_Init(CAN, &CAN_InitStructure);
	/*
	 * CAN BaudRate = 1/NominalBitTime
	 * NominalBitTime =  1*tq + tBS1 + tBS2, where tq = prescaler * tPCLK (tPCLK = APB1 clock)
	 *  */

#ifdef _TEST_UP
		CAN_FilterInitStructure.CAN_FilterNumber = 9; //14
		CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
		CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit; //32
		CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
		CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; //0000
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
		CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x00ff; //0000
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
		CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
		CAN_FilterInit(&CAN_FilterInitStructure);

		CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);

		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

		NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);


#elif defined (_CRUSCOTTO) || defined (_FR_DX) || defined (_FR_SX) || defined (_RT_DX )|| defined(_RT_SX) || defined(_BATTERIA) || defined(_TEST_DOWN)


#endif


}

void CAN_Tx(uint8_t length, uint8_t Data[length], uint32_t ID, CAN_TypeDef* CANx){

	TxMessage.StdId = ID;
	TxMessage.ExtId = 0x01;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = length;
	for (i=0; i < length; i++)
		TxMessage.Data[i]=(uint8_t) Data[i];

	CAN_Transmit(CANx, &TxMessage);
}


void CAN2_RX0_IRQHandler(void){

	CanRxMsg RxMessage;

	CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);


	if(RxMessage.StdId == May12)
	{
		potVCU = RxMessage.Data[0];
		potVCU<<=8;
		potVCU |= RxMessage.Data[1];
		potVCU<<=8;
		potVCU |= RxMessage.Data[2];
		potVCU<<=8;
		potVCU |= RxMessage.Data[3];
		potVCU<<=8;
		if (potVCU > 0xff0a)
			GPIO_init(GPIOB,LSfet, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_UP);
		else
			GPIO_init(GPIOB,LSfet, GPIO_Mode_IN, GPIO_OType_PP, GPIO_Speed_2MHz, GPIO_PuPd_DOWN);



		//		switch (bus_state){
		//		//disabilita timer per l'invio di pacchetti
		//		case 0:
		//			if(bus_state) TIM_Cmd (TIM2, DISABLE);
		//			break;
		//
		//			//abilita il timer per l'invio di pacchetti
		//		case 1:
		//			if (!bus_state)	TIM_Cmd (TIM2, ENABLE);
		//			break;
		//		}
	}
	else CAN_Manage_Rx(RxMessage);
}

void CAN_Manage_Rx(CanRxMsg RxMessage)
{

	//	else if(RxMessage.StdId == BMS_TTAB_ID)
	//	{
	//		TTabAvg  = (RxMessage.Data[1] << 8) | RxMessage.Data[0];
	//		TTabHigh = (RxMessage.Data[3] << 8) | RxMessage.Data[2];
	//	}


}


void CAN_BMS_Manage_Rx(CanRxMsg RxMessage)
{
	//	if(RxMessage.StdId == BMS_PACK_ID)
	//	{
	//		bus_state = (RxMessage.Data[1] << 8) | RxMessage.Data[0];
	//		IPackMsr = (RxMessage.Data[3] << 8) | RxMessage.Data[2];
	//		SoCMsr 	 = (RxMessage.Data[5] << 8) | RxMessage.Data[4];
	//	}
	//	else if(RxMessage.StdId == BMS_TTAB_ID)
	//	{
	//		TTabAvg  = (RxMessage.Data[1] << 8) | RxMessage.Data[0];
	//		TTabHigh = (RxMessage.Data[3] << 8) | RxMessage.Data[2];
	//	}
	//

}

uint8_t CAN_StatusControl(CAN_TypeDef* CANx)
{
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


