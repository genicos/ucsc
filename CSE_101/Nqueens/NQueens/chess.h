#ifndef CHESS
#define CHESS

#include <vector>

using namespace std;

class Queen{
  public:
    int col;
    int row;
    Queen(){}
    Queen(int a, int b){
      col = a;
      row = b;
    }
    static bool order(Queen a, Queen b); 
};

class Board{
  public:
    vector<bool> col_available;  //col_avalable[i] means col i+1 is not inhabited by a queen
    vector<bool> row_available;  //row ''
    int size;                    //Board would be a size*size chess board
    vector<Queen> queens;
    int queen_count = 0;
    
    Board(int size);
    Board(const Board &b);
    bool add_queen(Queen q);
    Queen next_queen_to_check(Queen q);
};


//Determines if a pair of queens is safe
// a pair of queens are safe if they may not immediately attack eatchother
bool is_pair_of_queens_safe(Queen A, Queen B);

//Determines if a set of queens is safe
// a set of queens is safe if every pair of queens within the set is safe
bool are_queens_safe(int count, vector<Queen> queens);


vector<Queen> solve_board(int size, int given, vector<Queen> queens);

#endif
