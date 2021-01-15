#include "chess.h"
#include <cmath>
#include <stack>
#include <iostream>
#include <stdio.h>

using namespace std;

Board::Board(int s){
  size = s;
  
  col_available.reserve(size);
  row_available.reserve(size);
  
  for(int i = 0; i < size; i++){
    col_available.push_back(true);
    row_available.push_back(true);  
  }
}

Board::Board(const Board &b){
  col_available = vector<bool>(b.col_available);
  row_available = vector<bool>(b.row_available);
  size = b.size;
  queens = vector<Queen>(b.queens);
  queen_count = b.queen_count;
}

bool Board::add_queen(Queen q){
  
  if(queen_count >= size){
    return false;
  }
  
  if(q.col > size || q.col < 0 || q.row > size || q.row < 0){
    return false;
  }
  
  if(!col_available[q.col - 1] || !row_available[q.row - 1]){
    return false;
  }
  
  queens.push_back(q);
  queen_count++;

  if(!are_queens_safe(queen_count, queens)){
    queens.pop_back();
    queen_count--;
    return false;
  }
  
  col_available[q.col - 1] = false;
  row_available[q.row - 1] = false;

  return true;
}

// pass Queen(1,0) to start check
Queen Board::next_queen_to_check(Queen q){
  
  for(int i = q.col; i <= size; i++){

    if(col_available[i - 1]){

      for(int j = q.row + 1; j <= size; j++){

        if(row_available[j - 1]){

          return Queen(i,j);
        }
      }
    }
  }

  return Queen(0,0);
}


bool Queen::order(Queen a, Queen b){
  return a.col < b.col;
}

//tested
bool is_pair_of_queens_safe(Queen A, Queen B){

  int row_dist = abs(A.row - B.row);
  int col_dist = abs(A.col - B.col);

  return (row_dist * col_dist != 0) && (row_dist != col_dist);
}

//tested
bool are_queens_safe(int count, vector<Queen> queens){

  for(int i = 0; i < count - 1; i++){
    for(int j = i + 1; j < count; j++){

      if( !is_pair_of_queens_safe(queens[i], queens[j]))
        return false;

    }
  }

  return true;
}


vector<Queen> solve_board(int size, int given, vector<Queen> queens){
  
  if(!are_queens_safe(given, queens)){ //if given queens are not safe, there is no solution
    return vector<Queen>{};
  }
  
  stack<Board> mystack;


  Board initial(size);             // Initial board has all given queens
  for(int i = 0; i < given; i++){  //
    initial.add_queen(queens[i]);  //
  }                                //
                                   //
  mystack.push(initial);           //


  while(!mystack.empty()){         //process stack elements
    Board curr = mystack.top();
    mystack.pop();
    

    if(curr.queen_count == size){ //curr board is a solution
      return curr.queens;
    }

    Queen to_add(1,0);




    Queen temp = curr.next_queen_to_check(to_add);
    to_add = temp;


    while(to_add.col != 0){
      Board next(curr);
      
      if(next.add_queen(to_add)){
        mystack.push(next);
      }
      

      temp = curr.next_queen_to_check(to_add);
      to_add = temp;
    }

  }
  
  return vector<Queen>{};
}
