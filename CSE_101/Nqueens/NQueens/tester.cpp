#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
  cout << "Testing queens" << endl;
  
  Queen qa(1,1);
  Queen qb(2,3);
  Queen qc(3,5);
  Queen qd(4,7);
  
  cout << "Created qa qb, qa.col = " << qa.col << endl;
  
  cout << "Testing is_pair_of_queens_safe(qa,qb)"<< endl;
  cout << is_pair_of_queens_safe(qa, qb) << endl;
  
  cout << "Testing all spots on 10 * 10 board for safety from qa ( at (1,1))" << endl;
  for(int i = 1; i <= 10; i++){
    for(int j = 1 ; j <= 10; j++){
      cout << ((is_pair_of_queens_safe(qa , Queen(i,j))) ? "#" : "*");
    }
    cout << endl;
  }

  vector<Queen> q_vect = {qa, qb, qc , qd};

  cout << "Testing are_queens_safe on four safe queens" << endl;
  cout << are_queens_safe(4,q_vect) << endl;
  
  cout << "Testing Boards, creating board of size 5" << endl;
  
  Board b(5);
  cout << "b.size: " << b.size << endl;
  
  cout << "Row and column avalability " << endl;

  for(int i = 0; i < b.size; i++){
    cout << b.col_available[i] << b.row_available[i] << endl;
  }
  
  cout << "Adding 3 safe queens ";
  cout << b.add_queen(qa);
  cout << b.add_queen(qb);
  cout << b.add_queen(qc)<< endl;
  
  cout << "attempting to add out of bounds queen " << b.add_queen(qd) << endl;
  cout << "attempting to add unsafe queen " << b.add_queen(Queen(1,5)) << endl;
  cout << "attempting to add unsafe queen " << b.add_queen(Queen(4,4)) << endl;
  
  Queen ne = b.next_queen_to_check(Queen(1,0));
  cout << "Queen to add: col:" << ne.col << " row:" << ne.row << endl;
  
  Board c(b);

  cout << "Copied board b size : " << b.size << " " << c.size << endl;
  cout << "queen count: " << b.queen_count << " " << c.queen_count << endl;
  
  return 0;
}
