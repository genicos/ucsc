#include "binary.h"

#include <stdlib.h>

uint32_t *insertion_sort(uint32_t *arr, uint32_t length) {
  //stats is the statistics of the algorithms execution
  //stats[0] is the number of comparisons
  //stats[1] is the number of moves
  uint32_t *stats = (uint32_t *)calloc(2, sizeof(uint32_t));
  if (length < 2) {
    return stats;
  }

  for (uint32_t i = 1; i < length; i++) {

    uint32_t left = 0;
    uint32_t right = i;

    //binary search
    while (left < right) {
      uint32_t mid = (left + right) / 2;

      stats[0]++;
      if (arr[i] >= arr[mid]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    //left is now the index where arr[i] should be put
    for (uint32_t j = i; j > left; j--) {
      uint32_t temp = arr[j];
      arr[j] = arr[j - 1];
      arr[j - 1] = temp;
      stats[1] += 3;
    }
  }

  return stats;
}
