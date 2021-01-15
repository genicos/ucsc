#include <stdio.h>
#include <inttypes.h>
#include "ll.h"

int main(){
  printf("Linked List Test \n\n");
  
  printf("Creating node A\n");

  node *A = create_node("A");
  if(!A){
    printf("Failed to create node A\n");
    return 1;
  }
  A->freq = 2;
  
  printf("Succesfully created node A, now making B, C, and D\n\n");
  
  node *B = create_node("B");
  node *C = create_node("C");
  node *D = create_node("D");
  if(!B || !C || !D){
    printf("Failed to create B or C or D\n");
    return 1;
  }
  B->freq = 1;
  C->freq = 1;


  node *head = B;
  printf("Appending D to B\n");
  
  head = append_node(head, D);
  printf("Resulting list:\n");
  print_linked_list(head);
  printf("\n");

  printf("Prepending A to list\n");

  head = prepend_node(head, A); 
  printf("Resulting list:\n");
  print_linked_list(head);
  printf("\n");

  printf("Inserting C after 1'th element in list\n");
  
  head = insert_node(head, C, 1);
  printf("Resulting list:\n");
  print_linked_list(head);
  printf("\n");
 
  
  printf("Searching for node C in list\n");
  node *found = search_word(head, "C");
  printf("Found: %s\n\n", found->word);
  
  printf("Removing B\n");
  node *removed = remove_word(&head, "B");
  printf("Removed: %s\n", removed->word);
  printf("List:\n");
  print_linked_list(head);
  printf("\n");
  
  printf("Removing A\n");
  removed = remove_word(&head, "A");
  printf("Removed: %s\n", removed->word);
  printf("List:\n");
  print_linked_list(head);
  printf("\n");
  
  printf("Removing D\n");
  removed = remove_word(&head, "D");
  printf("Removed: %s\n", removed->word);
  printf("List:\n");
  print_linked_list(head);
  printf("\n"); 
  
  
  printf("Readding A\n");
  head = add_word(head, A);
  printf("List:\n");
  print_linked_list(head);
  printf("\n");

  printf("Readding B\n");
  head = add_word(head, B);
  printf("List:\n");
  print_linked_list(head);
  printf("\n");

  printf("Readding D\n");
  head = add_word(head, D);
  printf("List:\n");
  print_linked_list(head);
  printf("\n");

  printf("Deleting linked list\n");
  delete_linked_list(head);
  return 0;
}
