/*
 *  @file 		model.c
 *  @author		Arella Matteo
 *  @date 		4 Jan 2018
 *  @brief		model.c module
 */

#include "model.h"

static status_t current_status;

#if defined(_PEDALI)

	__IO uint16_t tps1_value;
	__IO uint16_t tps2_value;
	__IO uint16_t brake_value;

	__IO uint16_t tps1_low;
	__IO uint16_t tps1_up;
	__IO uint16_t tps2_low;
	__IO uint16_t tps2_up;
	__IO uint16_t brake_low;
	__IO uint16_t brake_up;

	__IO uint8_t plaus1;
	__IO uint8_t plaus2;

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
