#include "io.h"
#include "endian.h"
#include <unistd.h>

#include <stdio.h>

#define BLOCK 4096

void read_header(int infile, FileHeader *header) {
  read(infile, header, sizeof(FileHeader));

  if (is_big()) {
    header->magic = swap32(header->magic);
    header->protection = swap16(header->protection);
  }
}

void write_header(int outfile, FileHeader *header) {
  if (is_big()) {
    header->magic = swap32(header->magic);
    header->protection = swap16(header->protection);
  }

  write(outfile, header, sizeof(FileHeader));
}

uint8_t pair_buffer[BLOCK];
uint16_t pair_bit_index = 0; //next bit to use
uint16_t pair_end = 0; //first unwritten byte

uint8_t char_buffer[BLOCK];
uint16_t char_byte_index = 0; //next byte to use
uint16_t char_end = 0; //first unwritten byte

bool read_sym(int infile, uint8_t *sym) {

  if (char_byte_index >= char_end) {
    char_end = read(infile, char_buffer, BLOCK);
    char_byte_index = 0;
  }

  if (char_end == 0) {
    return false;
  }

  *sym = char_buffer[char_byte_index];
  char_byte_index++;

  return true;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {

  uint32_t pair = code + (sym << bitlen); //pair to write

  for (uint8_t i = 0; i < bitlen + 8; i++) {

    uint16_t bit
        = (pair_bit_index + i) % (BLOCK * 8); //bit in buffer to write to
    pair_buffer[bit / 8] &= ~(1 << bit % 8); //clearing bit
    pair_buffer[bit / 8] += ((pair >> i) % 2) << (bit % 8); //adding bit

    if (pair_bit_index + i == BLOCK * 8 - 1) { //if full, write out buffer
      write(outfile, pair_buffer, BLOCK);
    }
  }

  pair_bit_index += bitlen + 8;
  pair_bit_index %= BLOCK * 8;
}

void flush_pairs(int outfile) {
  if (pair_bit_index == 0) {
    return;
  }

  uint16_t bytes = (pair_bit_index) / 8 + 1;
  if (pair_bit_index % 8 == 0) {
    bytes--;
  }

  write(outfile, pair_buffer, bytes);
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  uint32_t pair = 0;

  for (uint8_t i = 0; i < bitlen + 8; i++) {

    if (pair_bit_index + i == pair_end * 8) {
      pair_end = read(infile, pair_buffer, BLOCK);
      if (pair_end == 0) {
        return false;
      }
    }

    uint16_t bit = (pair_bit_index + i) % (BLOCK * 8);
    pair += ((pair_buffer[bit / 8] >> (bit % 8)) % 2) << i;
  }

  pair_bit_index += bitlen + 8;
  pair_bit_index %= BLOCK * 8;
  
  if (pair_bit_index == 0){
    pair_end = read(infile, pair_buffer, BLOCK);
    if (pair_end == 0){
      return false;
    }
  }

  *code = (uint16_t)(pair & ~(~0 << bitlen));
  *sym = (uint8_t)(pair >> bitlen);

  if (*code == STOP_CODE) {
    return false;
  }

  return true;
}

void buffer_word(int outfile, Word *w) {
  
  for (uint32_t i = 0; i < w->len; i++) {
    char_buffer[(i + char_byte_index) % BLOCK] = w->syms[i];
    
    if (i + char_byte_index == BLOCK - 1) { //if just filled, write out
      write(outfile, char_buffer, BLOCK);
    }
  }
  char_byte_index += w->len;
  char_byte_index %= BLOCK;
}

void flush_words(int outfile) {
  if (char_byte_index == 0) {
    return;
  }
  
  write(outfile, char_buffer, char_byte_index);
}

void reset_buffers(void) {
  pair_bit_index = 0;
  pair_end = 0;
  char_byte_index = 0;
  char_end = 0;
}
