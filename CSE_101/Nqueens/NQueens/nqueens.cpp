#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include "chess.h"

using namespace std;
/*
class Queen{
  public: 
    int col;
    int row;
    Queen(){}
    Queen(int a, int b){
      col = a;
      row = b;
    }
};


//Determines if a pair of queens is safe
// a pair of queens are safe if they may not immediately attack eatchother
bool is_pair_of_queens_safe(Queen A, Queen B);

//Determines if a set of queens is safe
// a set of queens is safe if every pair of queens within the set is safe
bool are_queens_safe(int count, Queen *queens);


bool solve_board(int size, int given, vector<Queen> queens);
*/


int main(int argc, char** argv){
  
  if (argc < 3){
    throw std::invalid_argument("Usage: ./nqueens <INPUT FILE> <OUTPUT FILE>");
  }
  
  ifstream input;
  ofstream output;
  
  input.open(argv[1]);
  output.open(argv[2]);

  string instance; //each line in input will be placed here
  while(getline(input, instance)){
    string token;
    stringstream instance_stream(instance);
    
    getline(instance_stream, token, ' '); //extracting first token from line
    int size = stoi(token);
    
    vector<Queen> queens(size);
    
    int given = 0; //how many queens are given to us

    
    while(getline(instance_stream, token, ' ')){ //storing given queens
      queens[given].col = stoi(token);
      
      getline(instance_stream, token, ' ');
      queens[given].row = stoi(token);
      
      given++;
    }
   

    //We are ready to attempt to solve the board
    
    vector<Queen> solution = solve_board(size,given,queens);

    if(solution.size() > 0){
      
      sort(solution.begin(), solution.end(), Queen::order);
      
      for(int i = 0; i < size; i++){
        output << solution[i].col << " " << solution[i].row << " ";
      }

      output << endl; 
    }else{
      output  << "No solution\n";
    }
    
  }
  
  input.close();
  output.close();
  return 0;
}

/*
bool solve_board(int size, int given, vector<Queen> queens){
  
  return false;
}


bool is_pair_of_queens_safe(Queen A, Queen B){
  
  int row_dist = abs(A.row - B.row);
  int col_dist = abs(A.col - B.col);
  
  return (row_dist * col_dist != 0) && (row_dist != col_dist);
}

bool are_queens_safe(int count, Queen *queens){
   
  for(int i = 0; i < count - 1; i++){
    for(int j = i + 1; j < count; j++){
      
      if( !is_pair_of_queens_safe(queens[i], queens[j]))
        return false;
      
    }
  }
  
  return true;
}
*/
