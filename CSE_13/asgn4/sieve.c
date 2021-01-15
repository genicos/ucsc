#include "sieve.h"
#include <math.h>

//Code written by Darrel Long
//
void sieve(BitVector *v) {
  bv_set_all_bits(v); // Assume all are prime
  bv_clr_bit(v, 0);
  bv_clr_bit(v, 1);
  for (uint32_t k = 2; k * 2 < bv_get_len(v); k++) { //cull all even numbers
    bv_clr_bit(v, k * 2);
  }
  for (uint32_t i = 3; i <= sqrtl(bv_get_len(v)); i++) {
    //bit set means it is prime
    if (bv_get_bit(v, i)) {
      for (uint32_t k = 0; (k + i) * i < bv_get_len(v);
           k += 2) { //increment k by two because (odd*odd + odd) is even
        bv_clr_bit(v, (k + i) * i); //multiples of primes are composite
      }
    }
  }
  return;
}
