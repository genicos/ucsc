#include "ll.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

node *create_node(char *word){
  node *n = (node *)calloc(1, sizeof(node));
  if(!n){
    return NULL;
  }
  
  int length = 0;
  while(word[length]){              //finding length of word
    length++;
  }
  length++;                         //allowing space for null terminator

  n->word = (char *)malloc(length); //creating space to copy word
  if(!n->word){
    return NULL;
  }

  for(int i = 0; i < length; i++){  //copying
    n->word[i] = word[i];
  }

  return n;
}

void delete_node(node *n){
  if(n){
    free(n->word);
  }
  free(n);
}

void delete_linked_list(node *head){
  if(!head){
    return;
  }

  node *next = head->next;
  
  delete_node(head);
  delete_linked_list(next);
}


node *prepend_node(node *head, node *A){
  if(!A){
    return NULL;
  }

  A->next = head;
  return A;
}

node *append_node(node *head, node *A){
  if(!A){
    return NULL;
  }
  if(!head){
    return A;
  }

  if(!head->next){
    head->next = A;
  }else{
    append_node(head->next, A);
  }

  return head;
}

node *insert_node(node *head, node *A, unsigned int i){
  if(!A){
    return NULL;
  }
  if(!head){
    return A;
  }
  
  if(i == 0 || !head->next){
    A->next = head->next;
    head->next = A;
  }else{
    insert_node(head->next, A, i - 1);
  }

  return head;
}

node *return_node(node *head, unsigned int i){
  if(!head){
    return NULL;
  }

  if(i == 0){
    return head;
  }

  return return_node(head->next, i - 1);
}

node *search_word(node *head, char *key){
  if(!head){
    return NULL;
  }
  
  if(strcmp(head->word, key) == 0){
    return head;
  }else{
    return search_word(head->next, key);
  }
}


node *remove_word(node **head, char *key){
  if(!*head){
    return NULL;
  }
  node *prev = *head;
  if(strcmp(prev->word, key) == 0){ //If the head matches, return pointer and update it
    *head = prev->next;
    return prev;
  }

  node *curr = prev->next;
  
  while(curr){
    if(strcmp(curr->word, key) == 0){
      prev->next = curr->next;
      return curr;
    }
    
    curr = curr->next;
    prev = prev->next;
  }
  
  return NULL;
}

node *add_word(node *head, node *word){
  if(!head){
    return word;
  }
  if(!word){
    return head;
  }
  
  node *prev = head;
  if(prev->freq < word->freq || (prev->freq == word->freq && strcmp(prev->word, word->word) > 0)){
    word->next = prev;
    return word;
  }

  node *curr = prev->next;
  while(curr){
    if(curr->freq < word->freq || (curr->freq == word->freq && strcmp(curr->word, word->word) > 0)){
      prev->next = word;
      word->next = curr;
      return head;
    }

    curr = curr->next;
    prev = prev->next;
  }
  
  prev->next = word;
  
  return head;
}

void print_linked_list(node *head){
  if(!head){
    return;
  }
  
  printf("%s, %d\n", head->word, head->freq);
  
  print_linked_list(head->next);
}
