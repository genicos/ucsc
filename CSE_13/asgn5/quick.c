#include "quick.h"

#include <stdio.h>
#include <stdlib.h>

uint32_t *quick_sort(uint32_t *arr, uint32_t length) {
  //stats is the statistics of the algorithms execution
  //stats[0] is number of comparisons
  //stats[1] is number of moves
  uint32_t *stats = (uint32_t *)calloc(2, sizeof(uint32_t));
  if (!stats) {
    return NULL; //we have failed to allocate 8 bytes, something is wrong
  }

  if (length < 2) {
    return stats;
  }

  uint32_t left = 0;
  uint32_t right = length - 1;

  uint32_t *new = (uint32_t *)malloc(length * sizeof(uint32_t));
  if (!new) {
    return NULL; //not enough memory to complete algorithm
  }

  //filling new array is arr partitioned by a pivot of arr[0]
  for (uint32_t i = 1; i < length; i++) {
    stats[0]++;
    if (arr[i] < arr[0]) {

      new[left] = arr[i];
      stats[1]++;
      left++;
    } else {

      new[right] = arr[i];
      stats[1]++;
      right--;
    }
  }
  new[left] = arr[0];
  stats[1]++;

  //copying new to arr
  stats[1] += length;
  for (uint32_t h = 0; h < length; h++) {
    arr[h] = new[h];
  }
  free(new);

  //calling quick sort on both unsorted sublists
  if (left > 1) {
    uint32_t *sub_stats = quick_sort(&arr[0], left);
    stats[0] += sub_stats[0];
    stats[1] += sub_stats[1];
    free(sub_stats);
  }
  if (right < length - 2) {
    uint32_t *sub_stats = quick_sort(&arr[right + 1], length - (right + 1));
    stats[0] += sub_stats[0];
    stats[1] += sub_stats[1];
    free(sub_stats);
  }

  return stats;
}
