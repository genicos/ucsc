#ifndef __BIT_H__
#define __BIT_H__

#include <inttypes.h>

uint8_t bit_length(uint16_t x) {
  for (uint8_t i = 15; i > 0; i--) {
    if ((x >> i) % 2 == 1) {
      return i + 1;
    }
  }
  return 1;
}

#endif
