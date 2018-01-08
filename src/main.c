#include "include.h"

int main(void) {

	SystemInit();

	Init_Board();

	RCC_ClocksTypeDef clock;

	while(1) {

		RCC_GetClocksFreq(&clock);

	}
}
