//Nicolas Ayala, nmayala@ucsc
//
//Code was heavily inspired by Darrel Long's slides
#include "stack.h"

struct Stack *stack_create(void) {
  Stack *fresh = (struct Stack *)malloc(sizeof(struct Stack));
  if (!fresh) {
    return NULL;
  }
  fresh->items = (uint32_t *)malloc(MINIMUM * sizeof(uint32_t));
  if (!fresh->items) {
    return NULL;
  }
  fresh->capacity = MINIMUM;
  fresh->top = 0;
  return fresh;
}

void stack_delete(struct Stack *s) {
  if (s) {
    free(s->items);
    free(s);
  }
}

bool stack_empty(struct Stack *s) {
  if (!s) {
    return -1;
  }
  return s->top == 0;
}

bool stack_push(struct Stack *s, uint32_t item) {
  if (s) {
    if (s->top == s->capacity) {
      s->capacity *= 2;
      s->items = (uint32_t *)realloc(s->items, s->capacity * sizeof(uint32_t));
    }
    if (s->items) {
      s->items[s->top] = item;
    }
    s->top += 1;
    return true;
  }
  return false;
}

bool stack_pop(struct Stack *s, uint32_t *item) {
  if (s && !stack_empty(s)) {
    s->top -= 1;
    if (item) {
      *item = s->items[s->top];
    }
    return true;
  }
  return false;
}

void stack_print(struct Stack *s) {
  if (s) {
    for (uint32_t i = 0; i < s->top; i++) {
      if (i != s->top - 1) {
        printf("%c -> ", s->items[i]);
      } else {
        printf("%c", s->items[i]);
      }
    }
  }
}
