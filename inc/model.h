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

extern void model_check_plausibility();

/*@defgroup MAGIC_NUMBERS
 *@{
 *@brief To calculate RPM from TIM1_CNT at CK_CNT=42MHz the formula is
 *       1/(32*(TIM1_CNT/(CK_CNT*60))). In order to send the data in 16bit of
 *       a CAN frame we have to represent it in uint16_t format.
 *       When the wheel (of 20" rolling radius) is about at 5Km/h it has a rpm
 *       value higher then 50 that explicit in Hz of pickup sensor is higher then 25.
 *       So the TIM1_CNT at 5Km/h on every risingEdge count up to 1500.
 *       if CK_CNT = 42MHz
 *       	1 / (32 * (TIM1_CNT / (CK_CNT * 60))) = 78750 / TIM1_CNT
 *@attention
 *			to represent better resolution this number is multiplied by 40
 *       	78750 * 40 / TIM1_CNT = 3150000 / TIM1_CNT
 *       	with the multiplying by 40 a speed greater then 150Km/h will be represent as 63000[rpm*40]
 *       	to obtain real rpm value DIVIDE the calculated pickup_value by 40
 **/
#if defined (_RT_DX) || defined(_RT_SX)|| defined (_FR_DX)|| defined(_FR_SX)
#define RPM_CONST	3150000	//78750 * 40
#endif
/*@}*/

#if defined(_PEDALI)

	#define RunTH 			25
	#define RunBK			10

	extern __IO uint16_t tps1_value;
	extern __IO uint16_t tps2_value;
	extern __IO uint16_t brake_value;

	extern __IO uint16_t tps1_low;
	extern __IO uint16_t tps1_up;
	extern __IO uint16_t tps2_low;
	extern __IO uint16_t tps2_up;
	extern __IO uint16_t brake_low;
	extern __IO uint16_t brake_up;

	extern __IO uint8_t tps1_percentage;
	extern __IO uint8_t tps2_percentage;
	extern __IO uint8_t brake_percentage;

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
