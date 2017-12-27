/*
 *  @file 		filter.h
 *  @author		Arella Matteo
 *  @date 		6 dic 2017
 *  @brief		Header for filter.c module
 */

#ifndef FILTER_H_
#define FILTER_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include "include.h"

/**
 * @addtogroup Filter
 * @{
 */

/**
 * @addtogroup Filter_functions
 * @brief	This function is used after DMA transfers complete to filter acquired data
 * @{
 */
void filter_data();
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* FILTER_H_ */

/**
 * @}
 */
