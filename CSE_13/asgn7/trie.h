#ifndef __TRIE_H__
#define __TRIE_H__

#include "code.h"

#define ALPHABET 256

typedef struct TrieNode TrieNode;

//Struct definition of TrieNode
//
//children: each TrieNode has ALPHABET number of children
//code:     Unique code for the TrieNode
//
struct TrieNode {
  TrieNode **children;
  uint16_t code;
};

//Constructor
//
//code:     code of the new TrieNode
//returns:  pointer to new TrieNode
TrieNode *trie_node_create(uint16_t code);

//Destructor
//
void trie_node_delete(TrieNode *n);

//Initializes a Trie: a root TrieNode with the code EMPTY_CODE
//
//returns: a pointer to the root
TrieNode *trie_create(void);

//Resets a Trie to just the root TrieNode
//
//root:    Root of trie to reset
//
void trie_reset(TrieNode *root);

//Deletes a Trie starting at the root
//
//n: Root of trie to delete
//
void trie_delete(TrieNode *n);

//Returns a pointer to the child TrieNode representing the symbol sym.
//
//n:       TrieNode to step from
//sym:     Symbol to check for
//returns: Pointer to the child stepped to
//
TrieNode *trie_step(TrieNode *n, uint8_t sym);

#endif
