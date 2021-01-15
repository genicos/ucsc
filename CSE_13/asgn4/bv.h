//This was written by Darrel Long
#ifndef __BV_H__
#define __BV_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

//Struct definition for a Bit Vector
//
//vector: The container of bits.
//length: The number of bits stored by this Bit Vector
typedef struct BitVector {
  uint8_t *vector;
  uint32_t length;
} BitVector;

//Creates a new BitVector of length bit_len
//
//bit_len: number of Bits stored by Bit Vector
BitVector *bv_create(uint32_t bit_len);

//Destructor for Bit Vector
//
//v: the bit vector to be destroyed
void bv_delete(BitVector *v);

//Returns the number of bits stored by bit vector
//
//v: the bit vector
uint32_t bv_get_len(BitVector *v);

//Sets the bit at index i(sets it to 1)
//
//v: the bit vector
//i: index of the bit to set
void bv_set_bit(BitVector *v, uint32_t i);

//Clears the bit at index i(clears it to 0)
//
//v: the bit vector
//i: index of the bit to clear
void bv_clr_bit(BitVector *v, uint32_t i);

//Returns the bit at index i of the bit vector
//
//v: the bit vector
//i: index of the bit to get
uint8_t bv_get_bit(BitVector *v, uint32_t i);

//Sets all bits in a bit vector
//
//v: the bit vector
void bv_set_all_bits(BitVector *v);

//Cleans all bits in a bit vector
//
//v: the bit vector
void bv_clr_all_bits(BitVector *v);
#endif
