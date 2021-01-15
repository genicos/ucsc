#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

#include "bst.h"
using namespace std;

int main(int argc, char **argv){
  if(argc < 3){
    throw invalid_argument("Usage: ./wordrange <INPUT FILE> <OUTPUT FILE>");
  }

  ifstream input;
  ofstream output;

  input.open(argv[1]);
  output.open(argv[2]);
  
  BST my_BST;

  string line; //
  while(getline(input, line)){
    string token;
    stringstream line_stream(line);

    getline(line_stream, token, ' ');
    
    if(token.compare("i") == 0){
      string to_insert;
      getline(line_stream, to_insert, ' ');
      
      my_BST.insert(to_insert);

    }else if(token.compare("r") == 0){
      string lbound;
      string rbound;
      getline(line_stream, lbound, ' ');
      getline(line_stream, rbound, ' '); 

      output << my_BST.range(lbound, rbound) << endl;

    }
  }
  
  my_BST.deleteBST();
  input.close();
  output.close();

  return 0;
}
