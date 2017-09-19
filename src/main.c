#include "include.h"

uint16_t bus_state =1, IPackMsr = 0, SoCMsr = 0, TTabAvg = 0, TTabHigh = 0;
uint8_t  data[4]= {0};
uint32_t Aread=0, potVCU=0;

uint8_t prim=0, sec =0, ter=0, quar=0;

int main(void)
{

	SystemInit();

	Init_Board();
	BMS_TIMinit();

	NVIC_SetPriority(SysTick_IRQn, 1);
	if(SysTick_Config((RCC_ClockFreq.SYSCLK_Frequency) / 50));//f = 50Hz -> T = 20ms

	while(1)
	{
	}

}


void SysTick_Handler(void){

	/* Start ADC Software Conversion */
	//	  ADC_SoftwareStartConv(ADC1);

	//	Aread = ADC1->DR;
	//	data[3]=(uint8_t)ADC1->DR;
	//	data[2]=(uint8_t)(ADC1->DR >> 8);
	//	data[1]=(uint8_t)(ADC1->DR >> 16);
	//	data[0]=(uint8_t)(ADC1->DR >> 24);



//	if (GPIOC->IDR & (uint32_t)SCK3)	//se non � premuto
//		//	CAN_Tx(4, data, STAR_ID, CAN);
//		GPIOA->BSRRH |= en23;
//	else				//il tasto � premuto
//		GPIOA->BSRRL |= en23;

		//	data[0] = (uint8_t)TTabAvg;
		//	data[1] = (uint8_t)(TTabAvg >> 8);
		//	data[2] = (uint8_t)TTabHigh;
		//	data[3] = (uint8_t)(TTabHigh >> 8);
		//
		//	CAN_Tx(4, data, 0x122, CAN_HV);
}
