#include "bf.h"
#include "bv.h"
#include "gs.h"
#include "hash.h"
#include "ll.h"
#include "parser.h"
#include "speck.h"

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bool move_to_front;

int main(int argc, char **argv) {
  bool stat_flag = false;
  extern uint32_t seeks;
  uint32_t seek_count = 0;
  float ave_seek = 0;

  uint32_t hash_size = 10000;
  uint32_t bloom_size = 0x00100000;
  extern bool move_to_front;

  FILE *in_file = stdin;

  int c = 0;
  while ((c = getopt(argc, argv, "sh:f:mbi:")) != -1) {
    switch (c) {
    case 's':
      stat_flag = true;
      break;
    case 'h':
      hash_size = atoi(optarg);
      break;
    case 'f':
      bloom_size = atoi(optarg);
      break;
    case 'm':
      move_to_front = true;
      break;
    case 'b':
      if (!move_to_front) {
        move_to_front = true;
      } else {
        printf("-m and -b flags are incompatible\n");
        exit(0);
      }
      break;
    case 'i':
      in_file = fopen(optarg, "r");
      if (!in_file) {
        printf("File '%s' not found", optarg);
        exit(0);
      }
    default:
      break;
    }
  }

  BloomFilter *word_screen = bf_create(bloom_size);
  HashTable *word_hash = ht_create(hash_size);

  regex_t regex;
  regcomp(&regex, "[a-zA-ZÁ-ÿ0-9'-]+", REG_EXTENDED);
  char *word;

  FILE *bad;
  bad = fopen("badspeak.txt", "r");

  //Read in forbidden words from badspeak.txt
  while ((word = next_word(bad, &regex)) != NULL) {
    bf_insert(word_screen, word);

    GoodSpeak *bad_gs = gs_create(word, "");
    ht_insert(word_hash, bad_gs);
  }
  clear_words();
  fclose(bad);

  FILE *translatable;
  translatable = fopen("newspeak.txt", "r");

  //Read in translatable words from newspeak
  while ((word = next_word(translatable, &regex)) != NULL) {
    bf_insert(word_screen, word);

    char *new_word = next_word(translatable, &regex);
    GoodSpeak *new_gs = gs_create(word, new_word);
    ht_insert(word_hash, new_gs);
  }
  clear_words();
  fclose(translatable);

  bool thought_crime = false;
  bool newspeak = false;

  ListNode *forbidden_head = NULL;
  ListNode *newspeak_head = NULL;

  //Reading text to censor
  while ((word = next_word(in_file, &regex)) != NULL) {
    if (bf_probe(word_screen, word)) {

      ListNode *node = ht_lookup(word_hash, word);

      if (node) {

        GoodSpeak *gs_copy = gs_create(
            gs_oldspeak(ll_node_gs(node)), gs_newspeak(ll_node_gs(node)));
        if (strcmp(gs_newspeak(ll_node_gs(node)), "")) {

          if (!ll_lookup(&newspeak_head, word)) { //Check for repeats
            ll_insert(&newspeak_head, gs_copy);
          } else {
            gs_delete(gs_copy);
          }
          newspeak = true;
        } else {

          if (!ll_lookup(&forbidden_head, word)) { //Check for repeats
            ll_insert(&forbidden_head, gs_copy);
          } else {
            gs_delete(gs_copy);
          }
          thought_crime = true;
        }

        ave_seek = (seek_count * ave_seek + seeks) / (seek_count + 1);
        seek_count++;
      }
    }
  }

  if (stat_flag) {
    float hash_load = (float)ht_count(word_hash) / hash_size;
    float bloom_load = (float)bf_count(word_screen) / bloom_size;
    printf("Seeks: %d\n", seek_count);
    printf("Average seek_length: %f\n", ave_seek);
    printf("Hash table load: %f\n", hash_load);
    printf("Bloom filter load: %f\n", bloom_load);
  } else {
    if (thought_crime) {
      printf("Dear Comrade,\n");
      printf("\n");
      printf("You have chosen to use degenerate words that may cause hurt\n");
      printf("feelings or cause your comrades to think unpleasant thoughts.\n");
      printf("This is doubleplus bad. To correct your wrongthink and\n");
      printf("preserve community consensus we will be sending you to joycamp\n");
      printf("administered by Miniluv.\n");
      printf("\nYour errors:\n\n");
      ll_print(forbidden_head);
    }
    if (newspeak) {
      if (thought_crime) {
        printf("\nThink of these words on your vacation!\n\n");
      } else {
        printf("Dear Comrade,\n");
        printf("\n");
        printf("Submitting your text helps to preserve feelings and prevent\n");
        printf("badthink. Some of the words that you used are not goodspeak.\n");
        printf("The list shows you how to turn the oldspeak words into newspeak.\n\n");
      }
      ll_print(newspeak_head);
    }
  }

  ll_delete(forbidden_head);
  ll_delete(newspeak_head);
  fclose(in_file);
  regfree(&regex);
  ht_delete(word_hash);
  bf_delete(word_screen);

  return 0;
}
