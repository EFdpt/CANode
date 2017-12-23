/*
 *  @file 		filter.c
 *  @author		Arella Matteo
 *  @date 		6 dic 2017
 *  @brief		filter.c module
 */


#include "filter.h"
#include "util/inc/sort.h"

#define FILTER_BOUND			(2)

#define USE_LOOP_UNROLLING		(1)
#define LOOP_UNROLLING_SIZE		(4)

static inline uint16_t filter_buffer(uint16_t* buffer, int size) {

	int start = FILTER_BOUND;
	int end = size - (FILTER_BOUND << 2);
	int divisor = end - start;
	if (divisor <= 0)
		divisor = 1;

	volatile int index = start;

#if USE_LOOP_UNROLLING
	volatile long long sum1 = 0LL;
	volatile long long sum2 = 0LL;
	volatile long long sum3 = 0LL;
	volatile long long sum4 = 0LL;

	for (; index + LOOP_UNROLLING_SIZE < end; index += LOOP_UNROLLING_SIZE) {
		sum1 += buffer[pos(index)];
		sum2 += buffer[pos(index + 1)];
		sum3 += buffer[pos(index + 2)];
		sum4 += buffer[pos(index + 3)];
	}

	for (; index < end; index++)
		sum1 += buffer[pos(index)];

	return (sum1 + sum2 + sum3 + sum4) / divisor;
#else
	volatile long long sum = 0LL;

	for (; index < end; index++) {
		sum += buffer[pos(index)];
	}
	return sum / divisor;
#endif
}

void filter_data() {

#if defined(_PEDALI)

	sort_off((uint16_t*) TPS1_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	tps1_value = filter_buffer((uint16_t*) TPS1_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) TPS2_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	tps2_value = filter_buffer((uint16_t*) TPS2_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) BRAKE_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	brake_value = filter_buffer((uint16_t*) BRAKE_DATA, BUFFER_SIZE);

#elif defined(_RT_DX) || defined(_RT_SX)

	sort_off((uint16_t*) SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	susp_value = filter_buffer((uint16_t*) SUSP_DATA, BUFFER_SIZE);

#elif defined(_FR_DX)

	sort_off((uint16_t*) SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	susp_value = filter_buffer((uint16_t*) SUSP_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) STEER_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	steer_value = filter_buffer((uint16_t*) STEER_DATA, BUFFER_SIZE);

#elif defined(_FR_SX)

	sort_off((uint16_t*) PRESS1_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	press1_value = filter_buffer((uint16_t*) PRESS1_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) PRESS2_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	press2_value = filter_buffer((uint16_t*) PRESS2_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) SUSP_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	susp_value = filter_buffer((uint16_t*) SUSP_DATA, BUFFER_SIZE);

#elif defined(_COG)

	sort_off((uint16_t*) ACCX_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	accx_value = filter_buffer((uint16_t*) ACCX_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) ACCY_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	accy_value = filter_buffer((uint16_t*) ACCY_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) ACCZ_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	accz_value = filter_buffer((uint16_t*) ACCZ_DATA, BUFFER_SIZE);

	sort_off((uint16_t*) GYRO_DATA, BUFFER_SIZE, ADC_SCAN_NUM);
	gyro_value = filter_buffer((uint16_t*) GYRO_DATA, BUFFER_SIZE);

#endif
}
