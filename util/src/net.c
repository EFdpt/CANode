/*
 *  @file 		net.c
 *  @author		Arella Matteo
 *  @date 		21 dic 2017
 *  @brief		net.c module
 */

#include "net.h"

inline uint16_t serializes(uint16_t n) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	asm ("rev16 %1,%0"
	          : "=r" (n)
	          : "r" (n));
#endif
	  return n;
}
inline uint16_t deserializes(uint16_t n) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	asm ("rev16 %1,%0"
	          : "=r" (n)
	          : "r" (n));
#endif
	  return n;
}
