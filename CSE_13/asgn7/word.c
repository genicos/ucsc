#include "word.h"

#include <stdio.h>
#include <stdlib.h>

Word *word_create(uint8_t *syms, uint32_t len) {
  Word *fresh = (Word *)malloc(sizeof(Word));
  if (!fresh) {
    return NULL;
  }

  fresh->syms = (uint8_t *)calloc(len, 1);
  if (!fresh->syms) {
    free(fresh);
    return NULL;
  }

  for (uint32_t i = 0; i < len; i++) {
    fresh->syms[i] = syms[i];
  }

  fresh->len = len;
  return fresh;
}

Word *word_append_sym(Word *w, uint8_t sym) {
  if (!w) {
    return NULL;
  }

  Word *fresh = (Word *)malloc(sizeof(Word));
  if (!fresh) {
    return NULL;
  }

  fresh->syms = (uint8_t *)malloc(w->len + 1);
  if (!fresh->syms) {
    return NULL;
  }

  fresh->len = w->len + 1;

  for (uint32_t i = 0; i < w->len; i++) {
    fresh->syms[i] = w->syms[i];
  }

  fresh->syms[w->len] = sym;

  return fresh;
}

void word_delete(Word *w) {
  if (w) {
    free(w->syms);
  }
  free(w);
}

WordTable *wt_create(void) {
  WordTable *fresh = calloc(MAX_CODE, sizeof(Word *));
  if (!fresh) {
    return NULL;
  }

  Word *empty = word_create(NULL, 0);
  if (!empty) {
    return NULL;
  }

  fresh[EMPTY_CODE] = empty;
  return fresh;
}

void wt_reset(WordTable *wt) {
  if (!wt) {
    return;
  }

  for (uint16_t i = EMPTY_CODE + 1; i < MAX_CODE && wt[i]; i++) {
    word_delete(wt[i]);
    wt[i] = NULL;
  }
}

void wt_delete(WordTable *wt) {
  if (!wt) {
    return;
  }

  for (uint16_t i = EMPTY_CODE; i < MAX_CODE && wt[i]; i++) {
    word_delete(wt[i]);
    wt[i] = NULL;
  }
  free(wt);
}
