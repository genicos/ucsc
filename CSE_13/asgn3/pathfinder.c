//Nicolas Ayala, nmayala@ucsc.edu

#include "stack.h"
#include <getopt.h>

#define NODES 26
#define OPTIONS "udmi:"
#define LARGEST_UINT32 0xFFFFFFFF

//Fills a NODES by NODES double array with truth values.
//if matrix[i][j] is true, then there is an edge from node i to node j
//Edges are determined in file
//
//returns: void
void fill_adjacency_matrix(
    FILE *file, bool matrix[NODES][NODES], bool directed) {

  char current_line[256];
  while (fscanf(file, "%s", current_line) != EOF
         && current_line[0] >= 'A' && current_line[0] <= 'Z'
         && current_line[1] >= 'A' && current_line[1] <= 'Z') {
    uint32_t first_node = current_line[0] - 'A';
    uint32_t second_node = current_line[1] - 'A';
    matrix[first_node][second_node] = true;
    if (!directed) {
      matrix[second_node][first_node] = true;
    }
  }
}

//Prints adjacency matrix
//
//returns: void
void print_matrix(bool matrix[NODES][NODES]) {
  printf(" ");
  for (uint8_t i = 0; i < NODES; i++) {
    printf(" %c", 'A' + i);
  }
  printf("\n");
  for (uint8_t i = 0; i < NODES; i++) {
    printf("%c", 'A' + i);
    for (uint8_t j = 0; j < NODES; j++) {
      printf(" %d", matrix[i][j]);
    }
    printf("\n");
  }
}

//Depth first search
//
//returns void
bool visited[NODES];
uint32_t shortest_path;
uint32_t number_of_paths;
void depth_first_search(
    bool matrix[NODES][NODES], Stack *path, uint32_t current_node) {
  if (current_node == 'Z' - 'A') {
    printf("Found path: ");
    stack_print(path);
    shortest_path = (shortest_path < path->top) ? shortest_path : path->top;
    number_of_paths++;
    printf("\n");
    return;
  }
  for (uint32_t i = 0; i < NODES; i++) {
    if (matrix[current_node][i] && !visited[i]) {
      stack_push(path, i + 'A');
      visited[i] = true;
      depth_first_search(matrix, path, i);
      visited[i] = false;
      stack_pop(path, NULL);
    }
  }
  return; //A lost soldier is left to die :(
}

int main(int argc, char **argv) {

  bool undirected_flag = false;
  bool directed_flag = false;
  bool print_flag = false;
  FILE *path_file = stdin;

  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 'i':
      path_file = fopen(optarg, "r");
      if (path_file == NULL) {
        perror(optarg);
        return -1;
      }
      break;
    case 'u':
      undirected_flag = true;
      break;
    case 'd':
      directed_flag = true;
      break;
    case 'm':
      print_flag = true;
      break;
    default:
      printf("Invalid argument\n");
      return -1;
    }
  }

  if (argc == 1) {
    puts("No arguments given");
    return -1;
  }
  if (undirected_flag && directed_flag) {
    puts("Flags -u and -d are incompatible");
    return -1;
  }

  bool matrix[NODES][NODES]; //Initializing a NODES by NODES bool array
  for (uint8_t i = 0; i < NODES; i++) { // all values initialized to false
    for (uint8_t j = 0; j < NODES; j++) { //
      matrix[i][j] = false; //
    }
  }

  //default is undirected, so only directed if specifically flagged
  bool directed = !undirected_flag && directed_flag;

  fill_adjacency_matrix(path_file, matrix, directed);
  fclose(path_file);
  
  if (print_flag) {
    print_matrix(matrix);
  }

  //Cleaning visited array
  for (uint8_t i = 0; i < NODES; i++) {
    visited[i] = false;
  }
  visited[0] = true; //We will always start on node A

  //Initialize shortest_path to largest value
  shortest_path = LARGEST_UINT32;
  number_of_paths = 0;

  struct Stack *path = stack_create();
  stack_push(path, 'A'); //We will begin on A

  depth_first_search(matrix, path, 0);

  if (number_of_paths > 0) {
    printf("Number of paths found: %d\n", number_of_paths);
    printf("Length of shortest path found: %d\n", shortest_path);
  } else {
    printf("No paths were found\n");
  }

  return 0;
}
