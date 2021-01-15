#ifndef __BINARY_H__
#define __BINARY_H__

#include <stdint.h>

//Binary insertion sort implementation
//  after the function has run, the array of size length
//  pointed to by arr will be sorted
//
// returns: a pointer to the first of two contiguos uint32_t
//   the first of which is the number of comparisons
//   the second of which is the number of moves
uint32_t *insertion_sort(uint32_t *arr, uint32_t length);

#endif
