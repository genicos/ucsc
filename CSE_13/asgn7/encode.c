#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "bit.h"
#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"

int main(int argc, char **argv) {
  bool verbose_flag = false;
  FILE *in_file = stdin;
  FILE *out_file = stdout;

  uint32_t compressed_size = 0;
  uint32_t natural_size = 0;

  int c = 0;
  while ((c = getopt(argc, argv, "vi:o:")) != -1) {
    switch (c) {
    case 'v':
      verbose_flag = true;
      break;
    case 'i':
      in_file = fopen(optarg, "r");
      if (!in_file) {
        printf("File '%s' not found\n", optarg);
        return 1;
      }
      break;
    case 'o':
      out_file = fopen(optarg, "w");
      break;
    default:
      printf("Invalid argument\n");
      printf(" Valid arguments are:\n");
      printf(" -v  for statistics\n");
      printf(" -i <infile> to mark file to read from\n");
      printf(" -o <outfile> to mark file to write to\n");
      return 2;
      break;
    }
  }

  FileHeader *header = (FileHeader *)calloc(1, sizeof(FileHeader));
  if (!header) {
    printf("Failed to create Header\n");
    return 3;
  }

  header->magic = MAGIC;

  struct stat *out_file_info = (struct stat *)calloc(1, sizeof(struct stat));
  if (!out_file_info) {
    printf("Failed to get file permissions\n");
    return 4;
  }

  fstat(fileno(out_file), out_file_info);

  header->protection = out_file_info->st_mode;

  write_header(fileno(out_file), header);

  free(header);
  free(out_file_info);

  TrieNode *root = trie_create();

  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;

  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;

  uint16_t next_code = START_CODE;

  while (read_sym(fileno(in_file), &curr_sym)) {

    TrieNode *next_node = trie_step(curr_node, curr_sym);

    if (next_node) {
      prev_node = curr_node;
      curr_node = next_node;
    } else {
      if (!curr_node) {
        return 5;
      }
      buffer_pair(
          fileno(out_file), curr_node->code, curr_sym, bit_length(next_code));
      curr_node->children[curr_sym] = trie_node_create(next_code);

      curr_node = root;
      next_code++;
    }

    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
  }

  natural_size = ftell(in_file);

  if (curr_node != root) {
    buffer_pair(
        fileno(out_file), prev_node->code, prev_sym, bit_length(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }

  buffer_pair(fileno(out_file), STOP_CODE, 0, bit_length(next_code));
  flush_pairs(fileno(out_file));

  fseek(out_file, 0L, SEEK_END);
  compressed_size = ftell(out_file);

  if (verbose_flag) {
    printf("\nCompressed file size: %d bytes\n", compressed_size);
    printf("Uncompressed file size: %d bytes\n", natural_size);
    printf(
        "Compression ratio: %.2f%%\n", 100.0 * compressed_size / natural_size);
  }

  trie_delete(root);

  fclose(in_file);
  fclose(out_file);

  return 0;
}
