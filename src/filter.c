/*
 *  @file 		filter.c
 *  @author		Arella Matteo
 *  @date 		6 dic 2017
 *  @brief		filter.c module
 */


#include "filter.h"
#include "util/inc/sort.h"

#define FILTER_BOUND		(2)

void filter_data() {

#if defined(_PEDALI)

	int start = FILTER_BOUND;
	int end = BUFFER_SIZE - (FILTER_BOUND << 2);

	volatile int index = start;
	volatile long sum = 0L;

	heapsort(TPS1_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (; index < end; index++) {
		sum += TPS1_DATA[pos(index)];
	}

	// aggiorna nuovo valore corrente
	tps1_value = sum / (end - start);

	heapsort(TPS2_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0L; index < end; index++) {
		sum += TPS2_DATA[pos(index)];
	}

	tps2_value = sum / (end - start);

	heapsort(BRAKE_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0L; index < end; index++) {
		sum += BRAKE_DATA[pos(index)];
	}

	brake_value = sum / (end - start);

#elif defined(_RT_DX) || defined(_RT_SX)

	int start = FILTER_BOUND;
	int end = BUFFER_SIZE - FILTER_BOUND << 2;

	volatile int index = start;
	volatile long sum = 0L;

	heapsort(SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (; index < end; index++) {
		sum += SUSP_DATA[pos(index)];
	}

	// aggiorna nuovo valore corrente
	susp_value = sum / (end - start);

#elif defined(_FR_DX)

	int start = FILTER_BOUND;
	int end = BUFFER_SIZE - FILTER_BOUND << 2;

	volatile int index = start;
	volatile long sum = 0L;

	heapsort(SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (; index < end; index++) {
		sum += SUSP_DATA[pos(index)];
	}

	// aggiorna nuovo valore corrente
	susp_value = sum / (end - start);

	heapsort(STEER_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0L; index < end; index++) {
		sum += STEER_DATA[pos(index)];
	}

	steer_value = sum / (end - start);

#elif defined(_FR_SX)

	__IO uint16_t* PRESS1_DATA = BUFFER_DATA;
	__IO uint16_t* PRESS2_DATA = BUFFER_DATA + 1;
	__IO uint16_t* SUSP_DATA = BUFFER_DATA + 2;

	__IO uint16_t press1_value = 0;
	__IO uint16_t press2_value = 0;
	__IO uint16_t susp_value = 0;

#elif defined(_COG)

	__IO uint16_t* ACCX_DATA = BUFFER_DATA;
	__IO uint16_t* ACCY_DATA = BUFFER_DATA + 1;
	__IO uint16_t* ACCZ_DATA = BUFFER_DATA + 2;
	__IO uint16_t* GYRO_DATA = BUFFER_DATA + 3;

	__IO uint16_t accx_value = 0;
	__IO uint16_t accy_value = 0;
	__IO uint16_t accz_value = 0;
	__IO uint16_t gyro_value = 0;

#endif
}
