#ifndef __STACK_H__
#define __STACK_H__

//This header file was written by Darrel Long, and was copied
//from a specification document

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MINIMUM 26

typedef struct Stack {
  uint32_t *items; //array of items
  uint32_t top; //top element, as index to array items
  uint32_t capacity; //capacity of items array
} Stack;

//Constructor for stack
//Stacks are initialized to hold MINIMUM number of uint32_t
//
//returns: a pointer to the newly created stack
struct Stack *stack_create(void);

//Destructor for stack
//
//returns: void
void stack_delete(struct Stack *s);

//Checks if stack is empty
//
//returns: truth value of stack emptiness
bool stack_empty(struct Stack *s);

//Pushes item to the stack
//
//returns: completeness of push operation
bool stack_push(struct Stack *s, uint32_t item);

//Pops an item (an uint32_t) off the stack
//The supplied item pointer is then made to point to the popped item.
//
//returns: completeness of pop operation
bool stack_pop(struct Stack *s, uint32_t *item);

//Prints content of a stack
//
//returns: void
void stack_print(struct Stack *s);

#endif
