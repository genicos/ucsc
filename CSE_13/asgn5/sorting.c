#include "binary.h"
#include "bubble.h"
#include "merge.h"
#include "quick.h"
#include "shell.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void test_sorting_algorithm(uint32_t *array,
    uint32_t *algorithm(uint32_t *, uint32_t), uint32_t elements,
    uint32_t print_count) {

  uint32_t *arr_copy = (uint32_t *)malloc(elements * sizeof(uint32_t));
  if (!arr_copy) {
    return; //Not enough memory
  }
  for (uint32_t h = 0; h < elements; h++) {
    arr_copy[h] = array[h];
  }

  uint32_t *statistics = algorithm(arr_copy, elements);

  printf("%d elements %d moves %d comparisons", elements, statistics[1],
      statistics[0]);

  for (uint32_t h = 0; h < print_count; h++) {
    if (h % 7 == 0) {
      printf("\n");
    }
    printf("%13d", arr_copy[h]);
  }
  printf("\n");

  free(arr_copy);
  free(statistics);
}

int main(int argc, char **argv) {

  bool bubble_flag = false;
  bool shell_flag = false;
  bool quick_flag = false;
  bool insertion_flag = false;
  bool merge_flag = false;

  uint32_t elements = 100;
  uint32_t print_count = 100;
  uint32_t seed = 8222022;

  int c = 0;
  while ((c = getopt(argc, argv, "Absqimp:r:n:")) != -1) {
    switch (c) {
    case 'A':
      bubble_flag = true;
      shell_flag = true;
      quick_flag = true;
      insertion_flag = true;
      merge_flag = true;
      break;
    case 'b':
      bubble_flag = true;
      break;
    case 's':
      shell_flag = true;
      break;
    case 'q':
      quick_flag = true;
      break;
    case 'i':
      insertion_flag = true;
      break;
    case 'm':
      merge_flag = true;
      break;
    case 'n':
      elements = atoi(optarg);
      break;
    case 'p':
      print_count = atoi(optarg);
      break;
    case 'r':
      seed = atoi(optarg);
      break;
    }
  }
  if (!(bubble_flag || shell_flag || quick_flag || insertion_flag
          || merge_flag)) {
    printf("Must specify at least one flag\n\n");
    printf("    -b will run bubble sort\n");
    printf("    -s will run shell sort\n");
    printf("    -q will run quicksort\n");
    printf("    -i will run binary insertion sort\n");
    printf("    -m will run merge sort\n");
    printf("    -A will run all sorts\n");
    exit(0);
  }

  if (elements < print_count) {
    print_count = elements;
  }

  srand(seed);
  uint32_t *arr = (uint32_t *)malloc(elements * sizeof(uint32_t));
  if (!arr) {
    return -1; //Not enough memory
  }
  for (uint32_t i = 0; i < elements; i++) {
    arr[i] = rand() & 0x3FFFFFFF;
  }

  if (bubble_flag) {
    printf("Bubble sort\n");
    test_sorting_algorithm(arr, &bubble_sort, elements, print_count);
    printf("\n");
  }
  if (shell_flag) {
    printf("Shell sort\n");
    test_sorting_algorithm(arr, &shell_sort, elements, print_count);
    printf("\n");
  }

  if (quick_flag) {
    printf("Quick sort\n");
    test_sorting_algorithm(arr, &quick_sort, elements, print_count);
    printf("\n");
  }

  if (insertion_flag) {
    printf("Binary insertion sort\n");
    test_sorting_algorithm(arr, &insertion_sort, elements, print_count);
    printf("\n");
  }

  if (merge_flag) {
    printf("Merge sort\n");
    test_sorting_algorithm(arr, &merge_sort, elements, print_count);
    printf("\n");
  }

  free(arr);
}
