/*
 *  @file 		misc.h
 *  @author		Arella Matteo
 *  @date 		04 Jan 2018
 *  @brief		Header for misc.c module
 */

#ifndef MISC_H_
#define MISC_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include <stdint.h>

extern uint8_t map_byte(uint8_t val, uint16_t min, uint16_t max, uint8_t min_to, uint8_t max_to);

#ifdef __cplusplus
}
#endif

#endif /* MISC_H_ */

