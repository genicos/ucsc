#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "ll.h"

#define LONGEST_WORD 256

int main(int argc, char **argv){
  
  if(argc < 2){
    printf("Insufficient arguments\n");
    return 2;
  }
  
  FILE *twains_words = fopen("twain-cleaned.txt", "r");
  if(!twains_words){
    printf("Missing critical file: twain-cleaned.txt\n");
    return 1;
  }
  
  
  FILE  *input = fopen(argv[1], "r");
  if(!input){
    printf("Cannot find file %s\n", argv[0]);
    fclose(twains_words);
    return 1;
  }
  
  FILE *output = fopen(argv[2], "w");
  
  
  node *list_heads[26] = {0};  //Preparing a linked list for every letter
  //int list_lengths[26];  //
  
  char word_buffer[LONGEST_WORD] = {0}; //Assuming that the longest word is less than LONGEST_WORD chars
  
  while(fgets(word_buffer, LONGEST_WORD, twains_words)){
    
    if(word_buffer[0] < 'a' || word_buffer[0] > 'z'){
      continue;
    }
    
    word_buffer[strlen(word_buffer) - 1] = '\0';       //replacing newline with \0

    node *head = list_heads[word_buffer[0] - 'a'];
    
    node *word = remove_word(&head, word_buffer);
    if(!word){
      word = create_node(word_buffer);
      if(!word){
        return 3;
      }
    }
    
    word->freq++;
    
    head = add_word(head, word);
    
    list_heads[word_buffer[0] - 'a'] = head;
  }
  
  
  //Read input file
  while(fgets(word_buffer, LONGEST_WORD, input)){
    char letter;
    unsigned int rank;
    sscanf(word_buffer, "%c %u", &letter, &rank);
    
    node *request = return_node(list_heads[letter - 'a'], rank);
    if(request){
      fprintf(output,"%s %d\n", request->word, request->freq);
    }else{
      fprintf(output,"-\n");
    }
  }
















  
  for(int i = 0; i < 26; i++){
    delete_linked_list(list_heads[i]);
  }
  fclose(twains_words);
  fclose(input);
  fclose(output);
}
