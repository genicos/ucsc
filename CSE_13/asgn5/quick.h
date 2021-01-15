#ifndef __QUICK_H__
#define __QUICK_H__

#include <stdint.h>

//Quicksort implementation
//  After the function has run, the array of size length
//  pointed to by arr will be sorted
//
//returns: a pointer to the first of two contiguos uint32_t
//  the first of which is the number of comparisons
//  the second of which is the number of moves
uint32_t *quick_sort(uint32_t *arr, uint32_t length);

#endif
