#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"

int main() {

  printf("\n=====================ENDIAN TESTS==============================\n");
  printf("The endianness of this system is: ");

  printf((is_big()) ? "big" : "little");

  uint16_t r16 = 0x1122;
  uint32_t r32 = 0x11223344;
  uint64_t r64 = 0x1122334455667788;

  printf("\nInitial values\n");
  printf("%x\n", r16);
  printf("%x\n", r32);
  printf("%lx\n", r64);

  r16 = swap16(r16);
  r32 = swap32(r32);
  r64 = swap64(r64);

  printf("\nSwapped values\n");
  printf("%x\n", r16);
  printf("%x\n", r32);
  printf("%lx\n", r64);

  printf("\n\n===========================WORD TESTS========================\n");

  uint8_t word_syms[3] = { 24, 236, 123 };
  Word *test_word = word_create(word_syms, 3);

  printf("Sedond symbol should be 236: %u\n", test_word->syms[1]);

  Word *bit_longer = word_append_sym(test_word, 59);
  printf("Appended word should be 24,236,123,59,\n");
  for (uint32_t i = 0; i < bit_longer->len; i++) {
    printf("%u, ", bit_longer->syms[i]);
  }

  WordTable *wt_test = wt_create();

  printf("\nlength of EMPTY_CODE entry in word table should be 0: %u\n",
      wt_test[EMPTY_CODE]->len);

  wt_test[EMPTY_CODE + 1] = test_word;
  wt_test[EMPTY_CODE + 2] = bit_longer;

  printf("Lengths in word table should be 0, 3, 4,\n");
  for (uint32_t i = EMPTY_CODE; i < MAX_CODE && wt_test[i]; i++) {
    printf("%u, ", wt_test[i]->len);
  }

  wt_reset(wt_test);

  printf("\nLengths in word table after reset should be 0,\n");
  for (uint32_t i = EMPTY_CODE; i < MAX_CODE && wt_test[i]; i++) {
    printf("%u, ", wt_test[i]->len);
  }

  wt_delete(wt_test);

  printf("\n\n=====================================TRIE "
         "TESTS===========================\n");
  //Tesing trie_node_create
  TrieNode *tn_test = trie_node_create(92);
  printf("\nNode code should be 92: %u\n", tn_test->code);

  //testing trie_create()
  TrieNode *root = trie_create();
  printf("root code should be %u: %u\n", EMPTY_CODE, root->code);

  //testing trie_step
  root->children[14] = tn_test;
  TrieNode *child = trie_step(root, 14);
  printf("Child code should be 92: %u\n", child->code);

  //testing tn_reset()
  trie_reset(root);
  printf("root code should be %u: %u\n", EMPTY_CODE, root->code);
  printf("Child pointer should be null: %p\n", (void *)root->children[14]);

  //testing trie_delete()
  trie_delete(root);

  printf("\n\n================================IO "
         "TESTING==============================\n");
  FILE *testpass1 = fopen("header1", "w+");
  FILE *testpass2 = fopen("header2", "w+");
  FILE *testpass3 = fopen("header3", "w+");
  FILE *testpass4 = fopen("header4", "w+");

  FileHeader *test_header = (FileHeader *)calloc(1, sizeof(FileHeader));
  test_header->magic = MAGIC;
  test_header->protection = 4;

  write_header(fileno(testpass1), test_header);
  write_header(fileno(testpass2), test_header);
  write_header(fileno(testpass3), test_header);
  write_header(fileno(testpass4), test_header);

  rewind(testpass1);
  rewind(testpass2);
  rewind(testpass3);
  rewind(testpass4);

  FILE *testfail1 = fopen("io.c", "r");
  FILE *testfail2 = fopen("Makefile", "r");
  FILE *testfail3 = fopen("trie.c", "r");
  FILE *testfail4 = fopen("word.h", "r");

  printf("The following headers should alternate\n");
  printf("between passing and failing, starting with failing\n");

  read_header(fileno(testfail1), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  read_header(fileno(testpass1), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  read_header(fileno(testfail2), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  read_header(fileno(testpass2), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  read_header(fileno(testfail3), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  read_header(fileno(testpass3), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  read_header(fileno(testfail4), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  read_header(fileno(testpass4), test_header);
  printf((test_header->magic == MAGIC) ? "Pass  " : "Fail  ");
  printf("Magic: %x, Prot: %u\n", test_header->magic, test_header->protection);

  free(test_header);

  fclose(testpass1);
  fclose(testpass2);
  fclose(testpass3);
  fclose(testpass4);
  fclose(testfail1);
  fclose(testfail2);
  fclose(testfail3);
  fclose(testfail4);

  printf("\n");

  printf("There should be 58 lines of NA# following\n");
  //buffer_pair, flush_pair and read_sym test
  FILE *pairsout = fopen("pairsout", "w+");

  for (uint32_t i = 0; i < 58 * 32; i++) {
    buffer_pair(fileno(pairsout), 0x0E, 0x14,
        4); //4E4  4 4E 1 23 becomes 4E 41 23 = "NA#"
    buffer_pair(fileno(pairsout), 0x04, 0x23, 4); //123

    if (i % 32 == 31) {

      buffer_pair(fileno(pairsout), 'A' + i / 32, '\n', 8); //newline
    }
  }

  flush_pairs(fileno(pairsout));

  rewind(pairsout);

  uint8_t sym = 0;

  while (read_sym(fileno(pairsout), &sym)) {
    printf("%c", sym);
  }

  fclose(pairsout);

  reset_buffers();

  //buffer_word, flush_word, and read_pair test
  FILE *wordsout = fopen("wordsout", "w+");

  uint8_t somesyms[3] = { 'H', 'A', 'M' };
  Word *w = word_create(somesyms, 3);

  for (uint32_t i = 0; i < 4000; i++) {
    buffer_word(fileno(wordsout), w);
  }
  flush_words(fileno(wordsout));
  word_delete(w);

  rewind(wordsout);

  uint16_t code = 0;
  sym = 0;

  printf("\nThere should be many \"Yes\" and no \"fail\": \n\n");

  //HAM is 48 41 4D, so pairs should be 8,14  4,4D
  uint32_t count = 0;
  while (read_pair(fileno(wordsout), &code, &sym, 4)) {
    if (count % 2 == 0 && code == 8 && sym == 0x14) {
      printf("Yes");
    } else if (count % 2 == 1 && code == 4 && sym == 0x4D) {
      printf("Yes");
    } else {
      printf("fail");
    }

    count++;
  }

  printf("\n\n Count should be 8000: %d\n\n", count);

  fclose(wordsout);
  return 0;
}
