#include "bv.h"
#include <stdio.h>

BitVector *bv_create(uint32_t bit_len) {
  BitVector *fresh = (BitVector *)malloc(sizeof(struct BitVector));
  if (!fresh) {
    return NULL;
  }
  fresh->length = bit_len;
  uint32_t bytes = bit_len / 8;
  if (bit_len % 8 != 0) {
    bytes++;
  }
  fresh->vector = (uint8_t *)malloc(bytes);
  if (!fresh->vector) {
    return NULL;
  }
  return fresh;
}

void bv_delete(BitVector *v) {
  if (v) {
    if (v->vector) {
      free(v->vector);
    }
    free(v);
  }
}

uint32_t bv_get_len(BitVector *v) {
  if (v) {
    return v->length;
  }
  return 0;
}

void bv_set_bit(BitVector *v, uint32_t i) {
  if (v && v->vector && i < v->length) {
    v->vector[i / 8] |= 1 << (i % 8);
  }
}

void bv_clr_bit(BitVector *v, uint32_t i) {
  if (v && v->vector && i < v->length) {
    v->vector[i / 8] &= ~(1 << (i % 8));
  }
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  if (v && v->vector && i < v->length) {
    uint8_t bit = v->vector[i / 8] >> (i % 8);
    return bit % 2;
  }
  return 2;
}

void bv_set_all_bits(BitVector *v) {
  if (v && v->vector && v->length > 0) {
    uint32_t bytes = ((v->length - 1) >> 3) + 1;
    for (uint32_t i = 0; i < bytes; i++) {
      v->vector[i] = 0xFF;
    }
  }
}

void bv_clr_all_bits(BitVector *v) {
  if (v && v->vector && v->length > 0) {
    uint32_t bytes = ((v->length - 1) >> 3) + 1;
    for (uint32_t i = 0; i < bytes; i++) {
      v->vector[i] = 0x00;
    }
  }
}
