#include "ll.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool move_to_front;

uint32_t seeks;

struct ListNode {
  GoodSpeak *gs;
  ListNode *next;
};

ListNode *ll_node_create(GoodSpeak *gs) {
  ListNode *fresh = (ListNode *)malloc(sizeof(ListNode));

  if (fresh) {
    fresh->gs = gs;
    fresh->next = NULL;
  }
  return fresh;
}

void ll_node_delete(ListNode *n) {
  if (n) {
    gs_delete(n->gs);
    free(n);
  }
}

void ll_delete(ListNode *head) {
  if (head) {

    ListNode *to_delete_next = head->next;
    ll_node_delete(head);

    while (to_delete_next) {

      head = to_delete_next;
      to_delete_next = head->next;
      ll_node_delete(head);
    }
  }
}

GoodSpeak *ll_node_gs(ListNode *n) {
  if (n) {
    return n->gs;
  }
  return NULL;
}

ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {
  ListNode *fresh = ll_node_create(gs);
  if (fresh) {

    fresh->next = *head;
    *head = fresh;
  }

  return (fresh);
}

ListNode *ll_lookup(ListNode **head, char *key) {
  extern bool move_to_front;
  seeks = 0;

  if (head && *head) {

    ListNode *prev = NULL;
    ListNode *look_up = *head;

    while (look_up) {
      seeks++;

      char *this_key = gs_oldspeak(look_up->gs);

      if (this_key && strcmp(this_key, key) == 0) {
        if (move_to_front && prev) {
          prev->next = look_up->next;
          prev = look_up;
          look_up = ll_insert(head, look_up->gs);
          free(prev);
        }
        return look_up;
      }
      prev = look_up;
      look_up = look_up->next;
    }
  }
  return NULL;
}

void ll_node_print(ListNode *n) {
  if (n && n->gs) {
    printf("%s", gs_oldspeak(n->gs));

    if (strcmp(gs_newspeak(n->gs), "")) {
      printf(" -> %s", gs_newspeak(n->gs));
    }

    printf("\n");
  }
}

void ll_print(ListNode *head) {
  while (head) {

    ll_node_print(head);
    head = head->next;
  }
}
