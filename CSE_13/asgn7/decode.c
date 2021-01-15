#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <getopt.h>
#include <stdbool.h>

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
        printf("File '%s' no found\n", optarg);
        return 1;
      }
      break;
    case 'o':
      out_file = fopen(optarg, "w");
      break;
    default:
      printf("Invalid argument\n");
      printf(" Valid arguments are:\n");
      printf(" -v for statistics\n");
      printf(" -i <infile> to mark file to read from\n");
      printf(" -o <outfile> to mark file to write to\n");
      return 2;
      break;
    }
  }

  FileHeader *header = (FileHeader *)calloc(1, sizeof(FileHeader));
  read_header(fileno(in_file), header);
  if (header->magic != MAGIC) {
    printf("Magic number does not match\n");
    fclose(in_file);
    fclose(out_file);
    free(header);
    return 3;
  }
  fchmod(fileno(out_file), header->protection);
  free(header);
  

  
  WordTable *table = wt_create();

  uint8_t curr_sym = 0;

  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;

  while (read_pair(
      fileno(in_file), &curr_code, &curr_sym, bit_length(next_code))) {
    
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    
    buffer_word(fileno(out_file), table[next_code]);
    
    next_code++;
    if (next_code == MAX_CODE) {
      
      wt_reset(table);
      
      next_code = START_CODE;
    }
  }

  flush_words(fileno(out_file));

  compressed_size = ftell(in_file);
  natural_size = ftell(out_file);

  if (verbose_flag) {
    printf("\nCompressed file size: %d bytes\n", compressed_size);
    printf("Uncompressed file size: %d bytes\n", natural_size);
    printf(
        "Compression ratio: %.2f%%\n", 100.0 * compressed_size / natural_size);
  }

  wt_delete(table);
  fclose(in_file);
  fclose(out_file);

  return 0;
}
