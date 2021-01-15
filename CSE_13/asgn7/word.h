#ifndef __WORD_H__
#define __WORD_H__

#include "code.h"
#include <inttypes.h>

//Struct defitintion of Word.
//
//syms: Array of symbols making up word
//len:  length of syms array
//
typedef struct Word {
  uint8_t *syms;
  uint32_t len;
} Word;

//Define an array of Words as a WordTable
typedef Word *WordTable;

//Contructor for a word.
//
//syms:   Array of symbols a word represents
//len:    length
//returns:Pointer to new Word
//
Word *word_create(uint8_t *syms, uint32_t len);

//Appends a symbol to a word
//
//w:       Word to append symbol to
//sym:     Symbol to append
//returns: resultant Word
//
Word *word_append_sym(Word *w, uint8_t sym);

//Destructor for a Word
//
//w:   Word to free
//
void word_delete(Word *w);

//Creates a new WordTable, an array of Words
//Has a predefined size of MAX_CODE - 1
//A WordTable is initialized with a single Word at index EMPTY_CODE
//This Word represents to empty word
//
//returns: new WordTable
//
WordTable *wt_create(void);

//Resets a WordTable to having just the empty Word.
//
//wt:   WordTable to reset
//
void wt_reset(WordTable *wt);

//Deletes and entire WordTable
//
//wt: WordTable to free
//
void wt_delete(WordTable *wt);

#endif
