#include <inttypes.h>
//Implementation of the Linked List ADT

typedef struct node node;

struct node{
  node* next;
  char *word;
  int freq;
};

node *create_node(char *word);

void  delete_node(node *A);

//deletes every node in the linked list with head node 'head'.
void  delete_linked_list(node *head);


//prepends the node 'A' to the linked list
//returns pointer to head node of newly formed linked list.
node *prepend_node(node *head, node *A);

//appends the node 'A' to the linked list
//returns pointer to head node of newly formed linked list.
node *append_node(node *head, node *A);

//inserts the node 'A' into the linked list
// directly after the i'th list element,
// making node 'A' the (i+1)'th list element.
//returns pointer to head node of newly formed linked list.
node *insert_node(node *head, node *A, unsigned int i);

//returns pointer to the i'th element of the linked list
node *return_node(node *head, unsigned int i);


//searches for a node whose word is 'key' in the linked list
//returns pointer to node with key, or null if it cannot be found
node *search_word(node *head, char *key);

//searches for a node whose word is 'key' in the linked list, and then removes
//returns pointer to node with key, or null if it cannot be found
//updates *head so that it points to head of new list. 
node *remove_word(node **head, char *key);

//Adds a word into a list which is ordered by decreasing frequency
// if frequency is equal then they are ordered by increasing lexographical order
// inserts word into first encountered position that keeps the frequency ordered
//returns pointer to head node of newly formed linked list.
node *add_word(node *head, node *word);


//prints the word and frequency of every element
// of the linked list with head 'head'
void print_linked_list(node *head);

