#include "bf.h"
#include "speck.h"
#include <stdlib.h>

struct BloomFilter {
  uint64_t primary[2];
  uint64_t secondary[2];
  uint64_t tertiary[2];
  BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));

  if (bf) {
    bf->primary[0] = 0xFC28CA6885711CF7;
    bf->primary[1] = 0x2841AF568222F773;
    bf->secondary[0] = 0x85AE998311115AE3;
    bf->secondary[1] = 0xB6FAC2AE33A40089;
    bf->tertiary[0] = 0xD37B01DF0AE8F8D0;
    bf->tertiary[1] = 0x911D454886CA7CF7;

    bf->filter = bv_create(size);

    return bf;
  }
  return (BloomFilter *)NULL;
}

void bf_delete(BloomFilter *b) {
  if (b) {
    bv_delete(b->filter);
    free(b);
  }
}

uint32_t bf_length(BloomFilter *b) {
  if (b && b->filter) {
    return bv_length(b->filter);
  }
  return 0;
}

void bf_insert(BloomFilter *b, char *key) {
  if (b && b->filter) {
    bv_set_bit(b->filter, hash(b->primary, key) % bf_length(b));
    bv_set_bit(b->filter, hash(b->secondary, key) % bf_length(b));
    bv_set_bit(b->filter, hash(b->tertiary, key) % bf_length(b));
  }
}

bool bf_probe(BloomFilter *b, char *key) {
  if (b) {
    if (bv_get_bit(b->filter, hash(b->primary, key) % bf_length(b))
        && bv_get_bit(b->filter, hash(b->secondary, key) % bf_length(b))
        && bv_get_bit(b->filter, hash(b->tertiary, key) % bf_length(b))) {
      return true;
    }
  }
  return false;
}

uint32_t bf_count(BloomFilter *b) {
  uint32_t count = 0;
  if (b && b->filter) {
    for (uint32_t i = 0; i < bf_length(b); i++) {
      if (bv_get_bit(b->filter, i)) {
        count++;
      }
    }
  }
  return count;
}
