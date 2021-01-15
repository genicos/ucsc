#include "shell.h"
#include <stdlib.h>

uint32_t *shell_sort(uint32_t *arr, uint32_t length) {
  //stats is the statistics of the algorithms execution
  //stats[0] is number of comparisons
  //stats[1] is number of moves
  uint32_t *stats = (uint32_t *)calloc(2, sizeof(uint32_t));
  if (!stats) {
    return NULL; //if 8 bytes failed to allocate, something is really wrong
  }
  if (length < 2) {
    return stats;
  }
  if (length == 2) {
    stats[0]++;
    if (arr[0] > arr[1]) {
      uint32_t temp = arr[0];
      arr[0] = arr[1];
      arr[1] = temp;
      stats[1] += 3;
    }
    return stats;
  }

  //Uses the Gonnet & Baeza-Yates gap sequence
  for (uint32_t gap = (5 * length) / 11; gap > 0;
       gap = (gap == 2) ? 1 : (5 * gap) / 11) {

    //every equivalence class of congruence modulo gap is an h-list
    for (uint32_t r = 0; r < gap; r++) {

      //top is lower bound on second highest unordered index in this h-list
      uint32_t top = length - gap;

      while (top > 0) {

        uint32_t top_copy = top;
        top = 0;
        for (uint32_t i = r; i < top_copy; i += gap) {

          stats[0]++;
          if (arr[i] > arr[i + gap]) {
            uint32_t temp = arr[i];
            arr[i] = arr[i + gap];
            arr[i + gap] = temp;
            stats[1] += 3;

            top = i;
          }
        }
      }
    }
  }

  return stats;
}
