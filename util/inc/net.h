/*
 *  @file 		net.h
 *  @author		Arella Matteo
 *  @date 		21 dic 2017
 *  @brief		Networking module utils
 */

#ifndef NET_H_
#define NET_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include <stdint.h>

extern uint16_t serializes(uint16_t);
extern uint16_t deserializes(uint16_t);

#ifdef __cplusplus
}
#endif

#endif /* NET_H_ */
