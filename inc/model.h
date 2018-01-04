/*
 *  @file 		model.h
 *  @author		Arella Matteo
 *  @date 		4 Jan 2018
 *  @brief		Header for model.c module
 */

#ifndef MODEL_H_
#define MODEL_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include "include.h"

typedef enum status_s {
	STAND,
	HVON,
	DRIVE,
	NOTDRIVE
} status_t;

extern status_t model_get_status();

extern void model_goto_drive();

extern void model_calibrate_bounds();

#if defined(_PEDALI)

	extern __IO uint16_t tps1_value;
	extern __IO uint16_t tps2_value;
	extern __IO uint16_t brake_value;

	extern __IO uint16_t tps1_low;
	extern __IO uint16_t tps1_up;
	extern __IO uint16_t tps2_low;
	extern __IO uint16_t tps2_up;
	extern __IO uint16_t brake_low;
	extern __IO uint16_t brake_up;

	extern __IO uint8_t plaus1;
	extern __IO uint8_t plaus2;

#elif defined(_RT_DX) || defined(_RT_SX)

	extern __IO uint16_t susp_value;
	extern __IO uint16_t pickup_value;

#elif defined(_FR_DX)

	extern __IO uint16_t susp_value;
	extern __IO uint16_t steer_value;
	extern __IO uint16_t pickup_value;

#elif defined(_FR_SX)

	extern __IO uint16_t press1_value;
	extern __IO uint16_t press2_value;
	extern __IO uint16_t susp_value;
	extern __IO uint16_t pickup_value;

#elif defined(_COG) || defined(_TEST_UP)

	extern __IO uint16_t accx_value;
	extern __IO uint16_t accy_value;
	extern __IO uint16_t accz_value;
	extern __IO uint16_t gyro_value;

#elif defined(_CRUSCOTTO) || defined(_BATTERIA) || defined(_TEST_DOWN)

#else
	#error "No board specified"
#endif

#ifdef __cplusplus
}
#endif

#endif /* MODEL_H_ */
