/*
 *  @file 		sort.h
 *  @author		Arella Matteo
 *  @date 		1 nov 2017
 *  @brief		Sorting module
 */

#ifndef SORT_H_
#define SORT_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include <stdint.h>

#define SORT_ORDER_INCREASING	(1)

/*
 * Sorting algorithm
 */
void sort(uint16_t* arr, unsigned n);

/*
 * Sorting algorithm with offset indexing.
 */
void sort_off(uint16_t* arr, unsigned n, unsigned offset);

#ifdef __cplusplus
}
#endif

#endif /* SORT_H_ */
