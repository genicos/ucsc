#ifndef __IO_H__
#define __IO_H__

#include "word.h"
#include <inttypes.h>
#include <stdbool.h>

#define MAGIC 0x8badbeef

//FileHeader
//
//magic:      Magic number indicating file was compressed by this program
//protection: protection/permission of the original file
//
typedef struct FileHeader {
  uint32_t magic;
  uint16_t protection;
} FileHeader;

//Reads FileHeader from the first sizeof(FileHeader) bytes of file
//
void read_header(int infile, FileHeader *header);

//Writes FileHeader to the first sizeof(FileHeader) bytes of file
//
void write_header(int outfile, FileHeader *header);

//Reads a symbol from the infile
//
//returns true if there was a symbol left to read
//
bool read_sym(int infile, uint8_t *sym);

//Outputs a pair to the outfile
//
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen);

//Writes out remaining pairs
//
void flush_pairs(int outfile);

//Reads in a pair
//
//returns true if there was a pair to read
//
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen);

//Writes out a word
//
void buffer_word(int outfile, Word *w);

//Flushes out remaining words
//
void flush_words(int outfile);

void reset_buffers(void);

#endif
