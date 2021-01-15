#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>

#define OPTIONS "spn:"

char *symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//Test if n is of the form 2^k -1, where k is an integer
//
//return: test result
bool predecessor_of_power_of_two(int32_t n) {
  n += 1;
  uint8_t bitcount = 0;
  for (uint8_t i = 0; i < 32; i++) {
    uint32_t two_tothe_i = 1 << i;
    if (two_tothe_i & n) {
      bitcount++;
    }
  }
  return bitcount == 1;
}

//Returns array of digits in Big Endian of n in given base
//
//first value of returned array is the number of digits
//subsequent values are digits starting at the least significant
uint8_t *positional_notation(uint32_t n, uint8_t base) {
  if (n == 0) {
    uint8_t *digits = (uint8_t *)malloc(2);
    if (!digits) {
      return NULL;
    }
    digits[0] = 1; //0 has 1 digit
    digits[1] = 0; //that digit is 0
    return digits;
  }
  uint8_t number_of_digits = floor(log(n) / log(base)) + 1;
  uint8_t *digits = (uint8_t *)malloc(number_of_digits + 1);
  if (!digits) {
    return NULL;
  }
  digits[0] = number_of_digits;
  for (uint8_t i = 1; i < number_of_digits + 1;
       i++) { //fills digits little endian style
    digits[i] = (uint8_t)(n % base);
    n /= base;
  }

  for (uint8_t i = 0; i < number_of_digits / 2;
       i++) { //flips order, now digits are in big endian
    digits[i + 1] ^= digits[digits[0] - i]; //xor swap
    digits[digits[0] - i] ^= digits[i + 1]; //
    digits[i + 1] ^= digits[digits[0] - i]; //
  }
  return digits;
}

//Tests if array is a palindrome, where digits[0] is number of digits
//digits: array to check
//
//returns: true if digits is a palindrome
bool is_palindrome(uint8_t *digits) {
  for (uint8_t i = 0; i < digits[0] / 2; i++) {
    if (digits[i + 1] != digits[digits[0] - i]) {
      return false;
    }
  }
  return true;
}

//Sets all bits that are in Fibonacci sequence
//
//returns: void
void fibonacci(BitVector *v) {
  bv_clr_all_bits(v);
  uint32_t prev_term = 0;
  uint32_t term = 1;
  uint32_t sum; //term + prev_term

  bv_set_bit(v, prev_term);
  bv_set_bit(v, term);

  while (prev_term + term < bv_get_len(v)) {
    sum = prev_term + term;
    prev_term = term;
    term = sum;
    bv_set_bit(v, sum);
  }
}

//Sets all bits that are Lucas numbers
//
//returns: void
void lucas(BitVector *v) {
  bv_clr_all_bits(v);
  uint32_t prev_term = 2;
  uint32_t term = 1;
  uint32_t sum; //term + prev_term

  bv_set_bit(v, prev_term);
  bv_set_bit(v, term);

  while (prev_term + term < bv_get_len(v)) {
    sum = prev_term + term;
    prev_term = term;
    term = sum;
    bv_set_bit(v, sum);
  }
}
//Prints out all numbers set in a Bit Vector
//which are palindromes in a givern base
//
//returns: void
void output_palindromes_in_base(BitVector *primes, uint8_t base) {
  printf("Base %d\n", base);
  printf("---- --\n");
  for (uint32_t i = 0; i < bv_get_len(primes); i++) {
    if (bv_get_bit(primes, i)) {
      uint8_t *digits = positional_notation(i, base);
      if (is_palindrome(digits)) {
        printf("%d = ", i);
        for (uint8_t d = 0; d < digits[0]; d++) {
          printf("%c", symbols[digits[d + 1]]);
        }
        printf("\n");
      }
    }
  }
  printf("\n");
}



int main(int argc, char **argv) {

  bool special_flag = false;
  bool palindrome_flag = false;
  uint32_t N = 1000;

  int c = 0;
  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 's':
      special_flag = true;
      break;
    case 'p':
      palindrome_flag = true;
      break;
    case 'n':
      N = atoi(optarg);
      break;
    default:
      printf("Invalid argument\n");
      break;
    }
  }

  struct BitVector *primes = bv_create(N);
  sieve(primes);

  
  if (special_flag) {
    
    struct BitVector *fib = bv_create(N);
    fibonacci(fib);
    
    struct BitVector *luc = bv_create(N);
    lucas(luc);
    
    for (uint32_t i = 0; i < bv_get_len(primes); i++) {
      if (bv_get_bit(primes, i)) {
        printf("%d: prime", i);
        if (predecessor_of_power_of_two(i)) {
          printf(", mersenne");
        }
        if (bv_get_bit(luc, i)) {
          printf(", lucas");
        }
        if (bv_get_bit(fib, i)) {
          printf(", fibonacci");
        }
        printf("\n");
      }
    }
    bv_delete(luc);
    bv_delete(fib);
  }

  printf("\n");

  if (palindrome_flag) {
    output_palindromes_in_base(primes, 2);
    output_palindromes_in_base(primes, 10);
    output_palindromes_in_base(primes, 11);
    output_palindromes_in_base(primes, 14);
  }

  bv_delete(primes);
}
