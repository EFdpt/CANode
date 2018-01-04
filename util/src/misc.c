/*
 *  @file 		misc.c
 *  @author		Arella Matteo
 *  @date 		4 Jan 2018
 *  @brief		misc.c module for miscellaneous functions
 */

#include "../inc/misc.h"

inline uint8_t map_byte(uint8_t val, uint16_t min, uint16_t max, uint8_t min_to, uint8_t max_to) {
	return (val - min) * (max_to - min_to) / (max - min) + min_to;
}
