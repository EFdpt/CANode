/*
 *  @file 		model.c
 *  @author		Arella Matteo
 *  @date 		4 Jan 2018
 *  @brief		model.c module
 */

#include "model.h"

volatile static status_t current_status;

#if defined(_PEDALI)

	__IO uint16_t tps1_value = 0;
	__IO uint16_t tps2_value = 0;
	__IO uint16_t brake_value = 0;

	__IO uint16_t tps1_low = 0;
	__IO uint16_t tps1_up = 4095;
	__IO uint16_t tps2_low = 0;
	__IO uint16_t tps2_up = 4095;
	__IO uint16_t brake_low = 0;
	__IO uint16_t brake_up = 4095;

	__IO uint8_t tps1_percentage = 0;
	__IO uint8_t tps2_percentage = 0;
	__IO uint8_t brake_percentage = 0;

	__IO uint8_t plaus1 = 0;
	__IO uint8_t plaus2 = 0;

#elif defined(_RT_DX) || defined(_RT_SX)

	__IO uint16_t susp_value = 0;
	__IO uint16_t pickup_value = 0;

#elif defined(_FR_DX)

	__IO uint16_t susp_value = 0;
	__IO uint16_t steer_value = 0;
	__IO uint16_t pickup_value = 0;

#elif defined(_FR_SX)

	__IO uint16_t press1_value = 0;
	__IO uint16_t press2_value = 0;
	__IO uint16_t susp_value = 0;
	__IO uint16_t pickup_value = 0;

#elif defined(_COG) || defined(_TEST_UP)

	__IO uint16_t accx_value = 0;
	__IO uint16_t accy_value = 0;
	__IO uint16_t accz_value = 0;
	__IO uint16_t gyro_value = 0;

#endif

inline status_t model_get_status() {
	return current_status;
}

inline void model_goto_drive() {
	current_status = DRIVE;
}

void model_calibrate_bounds() {
#if defined(_PEDALI)

	if (tps1_value < tps1_low)
		tps1_low = tps1_value;
	else if (tps1_value > tps1_up)
		tps1_up = tps1_value;

	if (tps2_value < tps2_low)
		tps2_low = tps2_value;
	else if (tps2_value > tps2_up)
		tps2_up = tps2_value;

	if (brake_value < brake_low)
		brake_low = brake_value;
	else if (brake_value > brake_up)
		brake_up = brake_value;

#elif defined(_RT_DX) || defined(_RT_SX)

			__IO uint16_t susp_value;
			__IO uint16_t pickup_value;

#elif defined(_FR_DX)

			__IO uint16_t susp_value;
			__IO uint16_t steer_value;
			__IO uint16_t pickup_value;

#elif defined(_FR_SX)

			__IO uint16_t press1_value;
			__IO uint16_t press2_value;
			__IO uint16_t susp_value;
			__IO uint16_t pickup_value;

#elif defined(_COG) || defined(_TEST_UP)

			__IO uint16_t accx_value;
			__IO uint16_t accy_value;
			__IO uint16_t accz_value;
			__IO uint16_t gyro_value;

#endif

}

inline void model_check_plausibility() {
#if defined(_PEDALI)
	if (current_status != DRIVE)
		return;

	uint8_t distance = tps1_percentage > tps2_percentage ?
				tps1_percentage - tps2_percentage : tps2_percentage - tps1_percentage;
	if (distance > 10)
		plaus1 = 0;
	else
		plaus1 = (uint8_t) 0xFF;

	if (tps1_percentage > RunTH && brake_percentage > RunBK)
		plaus2 = 0;
	else
		plaus2 = (uint8_t) 0xFF;
#endif
}
