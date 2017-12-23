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

#if defined(_PEDALI) || defined(_RT_DX) || defined(_RT_SX) || defined(_FR_DX) || defined(_FR_SX) || defined(_COG) || defined(_TEST_UP)
	int start = FILTER_BOUND;
	int end = BUFFER_SIZE - (FILTER_BOUND << 2);

	volatile int index = start;
	volatile long long sum = 0LL;

#endif

#if defined(_PEDALI)

	sort_off((uint16_t*) TPS1_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (; index < end; index++) {
		sum += TPS1_DATA[pos(index)];
	}

	// aggiorna nuovo valore corrente
	tps1_value = sum / (end - start);

	sort_off((uint16_t*) TPS2_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += TPS2_DATA[pos(index)];
	}

	tps2_value = sum / (end - start);

	sort_off((uint16_t*) BRAKE_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += BRAKE_DATA[pos(index)];
	}

	brake_value = sum / (end - start);

#elif defined(_RT_DX) || defined(_RT_SX)

	sort_off((uint16_t*) SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (; index < end; index++) {
		sum += SUSP_DATA[pos(index)];
	}

	// aggiorna nuovo valore corrente
	susp_value = sum / (end - start);

#elif defined(_FR_DX)

	sort_off((uint16_t*) SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (; index < end; index++) {
		sum += SUSP_DATA[pos(index)];
	}

	// aggiorna nuovo valore corrente
	susp_value = sum / (end - start);

	sort_off((uint16_t*) STEER_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += STEER_DATA[pos(index)];
	}

	steer_value = sum / (end - start);

#elif defined(_FR_SX)

	sort_off((uint16_t*) PRESS1_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += PRESS1_DATA[pos(index)];
	}

	press1_value = sum / (end - start);

	sort_off((uint16_t*) PRESS2_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += PRESS2_DATA[pos(index)];
	}

	press2_value = sum / (end - start);

	sort_off((uint16_t*) SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += SUSP_DATA[pos(index)];
	}

	susp_value = sum / (end - start);

#elif defined(_COG)

	sort_off((uint16_t*) ACCX_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += ACCX_DATA[pos(index)];
	}

	accx_value = sum / (end - start);

	sort_off((uint16_t*) ACCY_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += ACCY_DATA[pos(index)];
	}

	accy_value = sum / (end - start);

	sort_off((uint16_t*) ACCZ_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += ACCZ_DATA[pos(index)];
	}

	accz_value = sum / (end - start);

	sort_off((uint16_t*) GYRO_DATA, BUFFER_SIZE, ADC_SCAN_NUM);

	for (index = 0, sum = 0LL; index < end; index++) {
		sum += GYRO_DATA[pos(index)];
	}

	gyro_value = sum / (end - start);

#endif
}
