#include "trie.h"

#include <stdio.h>
#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {
  TrieNode *fresh = (TrieNode *)malloc(sizeof(TrieNode));
  if (!fresh) {
    return NULL;
  }

  fresh->children = (TrieNode **)calloc(ALPHABET, sizeof(TrieNode *));
  if (!fresh->children) {
    free(fresh);
    return NULL;
  }

  fresh->code = code;
  return fresh;
}

void trie_node_delete(TrieNode *n) {
  if (n) {
    free(n->children);
  }
  free(n);
}

TrieNode *trie_create(void) {
  TrieNode *root = trie_node_create(EMPTY_CODE);
  return root;
}

void trie_reset(TrieNode *root) {
  if (!root) {
    return;
  }

  for (uint16_t i = 0; i < ALPHABET; i++) {
    if (root->children[i]) {
      trie_delete(root->children[i]);
      root->children[i] = NULL;
    }
  }
}

void trie_delete(TrieNode *n) {
  if (!n) {
    return;
  }

  for (uint16_t i = 0; i < ALPHABET; i++) {
    if (n->children[i]) {
      trie_delete(n->children[i]);
      n->children[i] = NULL;
    }
  }

  trie_node_delete(n);
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  if (!n) {
    return NULL;
  }

  return n->children[sym];
}
