#include "merge.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t *merge_sort(uint32_t *arr, uint32_t length) {
  //stats is the statistics of the algorithms execution
  //stats[0] is the number of comparisons
  //stats[1] is number of moves
  uint32_t *stats = (uint32_t *)calloc(2, sizeof(uint32_t));
  if (!stats) {
    return NULL; //if 8 bytes failed to allocate, something is seriously wrong
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

  uint32_t *sub_stats = merge_sort(&arr[0], length / 2);
  stats[0] += sub_stats[0];
  stats[1] += sub_stats[1];
  free(sub_stats);

  sub_stats = merge_sort(&arr[length / 2], (length - 1) / 2 + 1);
  stats[0] += sub_stats[0];
  stats[1] += sub_stats[1];
  free(sub_stats);

  //creating a seperate space for the first half array
  uint32_t *halfarr = (uint32_t *)malloc(length / 2 * sizeof(uint32_t));
  if (!halfarr) {
    return NULL; // We dont have enough memory to complete the algorithm
  }

  stats[1] += length / 2;
  for (uint32_t h = 0; h < length / 2; h++) {
    halfarr[h] = arr[h];
  }

  uint32_t a = 0; //index in first half array
  uint32_t b = length / 2; //index in second half array
  uint32_t i = 0; //index in main array
  while (a < length / 2 && b < length) {

    stats[0]++;
    if (halfarr[a] <= arr[b]) {
      arr[i] = halfarr[a];
      stats[1]++;
      a++;
    } else {
      arr[i] = arr[b];
      stats[1]++;
      b++;
    }
    i++;

    //if second array hits its top, we transfer the remaining elements
    //from the first array into the main one
    if (b == length) {
      while (i < length) {
        arr[i] = halfarr[a];
        stats[1]++;
        i++;
        a++;
      }
    }
  }

  free(halfarr);
  return stats;
}
