#include "hash.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>

struct HashTable {
  uint32_t length;
  ListNode **table;
};

HashTable *ht_create(uint32_t length) {
  HashTable *fresh = (HashTable *)malloc(sizeof(struct HashTable));
  if (fresh) {
    fresh->table = (ListNode **)calloc(length, sizeof(ListNode *));
    fresh->length = length;
  }
  return fresh;
}

void ht_delete(HashTable *h) {
  if (h && h->table) {
    for (uint32_t i = 0; i < h->length; i++) {
      if (h->table[i]) {
        ll_delete(h->table[i]);
      }
    }
    free(h->table);
  }
  free(h);
}

ListNode *ht_lookup(HashTable *h, char *key) {

  if (h) {

    uint64_t salt[2] = { 0, 0 };
    uint32_t index = hash(salt, key) % h->length;

    if (h->table[index]) {

      ListNode **head = &h->table[index];
      ListNode *node = ll_lookup(head, key);
      h->table[index] = *head;

      return node;
    }
  }
  return NULL;
}

void ht_insert(HashTable *h, GoodSpeak *gs) {
  if (h && gs) {
    uint64_t salt[2] = { 0, 0 };
    uint32_t index = hash(salt, gs_oldspeak(gs)) % h->length;

    if (h->table[index]) {

      ListNode **head = &h->table[index];
      ll_insert(head, gs);
      h->table[index] = *head;
      return;

    } else {

      ListNode *node = ll_node_create(gs);

      if (node) {
        h->table[index] = node;
      }
    }
  }
}

uint32_t ht_count(HashTable *h) {
  uint32_t count = 0;
  if (h) {
    for (uint32_t i = 0; i < h->length; i++) {
      if (h->table[i]) {
        count++;
      }
    }
  }
  return count;
}

void ht_print(HashTable *h) {
  if (h) {
    for (uint32_t i = 0; i < h->length; i++) {
      if (h->table[i]) {
        ll_print(h->table[i]);
      }
    }
  }
}
