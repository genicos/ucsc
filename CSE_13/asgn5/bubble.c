#include "bubble.h"
#include <stdlib.h>

uint32_t *bubble_sort(uint32_t *arr, uint32_t length) {
  //stats is the statistics of the algorithms execution
  //stats[0] is number of comparisons
  //stats[1] is number of moves
  uint32_t *stats = (uint32_t *)calloc(2, sizeof(uint32_t));

  if (length < 2) {
    return stats;
  }

  uint32_t top = length - 1; //top is the highest unordered index
  while (top > 0) {
    uint32_t top_copy = top;
    top = 0;
    for (uint32_t i = 0; i < top_copy; i++) {

      stats[0]++;
      if (arr[i] > arr[i + 1]) {
        uint32_t temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
        stats[1] += 3;

        top = i;
      }
    }
  }
  return stats;
}
