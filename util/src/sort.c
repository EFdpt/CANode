/*
 *  @file 		sort.c
 *  @author		Arella Matteo
 *  @date 		1 nov 2017
 *  @brief		Sorting module
 */

#include "../inc/sort.h"

#define parent(i, offset)		(((i)>>1) - (offset>>1))
#define left(i, offset)			(((i)<<1) + offset)
#define right(i, offset)		(((i)<<1) + (offset<<1))

static inline int comparator(uint16_t x, uint16_t y) {
	#if SORT_ORDER_INCREASING
		return x > y;
	#else
		return x < y;
	#endif
}

static inline void swap(uint16_t* x, uint16_t* y) {
	uint16_t temp = *x;
	*x = *y;
	*y = temp;
}

static void heapify(uint16_t* arr, unsigned n, unsigned i, unsigned offset) {
	unsigned prior = i;
    unsigned l;
    unsigned r;
    while ((l = left(i, offset)) < n) {
		r = right(i, offset);
		if (comparator(arr[l], arr[prior]))
			prior = l;
		if (r < n && comparator(arr[r], arr[prior]))
			prior = r;
		if (prior == i)
			break;
		swap(arr+i, arr+prior);
		i = prior;
	}
}

static inline void build_heap(uint16_t* arr, unsigned n, unsigned offset) {
	int i;
    for (i = parent(n-1, offset); i >= 0; i-=offset)
        heapify(arr, n, i, offset);
}

void heapsort(uint16_t* arr, unsigned n, unsigned offset) {
	if (n == 0 || n == 1 || offset == 0 || (n / offset) < 2)
		return;
	int i;

	build_heap(arr, n, offset);

    for (i=n-1; i>=0; i-=offset) {
        swap(arr, arr+i);
		heapify(arr, i, 0, offset);
    }
}
