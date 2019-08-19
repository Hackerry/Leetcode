#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

class Cell {
  public:
    bitset<9> origDigits;
    bitset<9> currDigits;
    int i, j;

    Cell(int i, int j) {
      this->i = i;
      this->j = j;
    }
};

// Use back track technique
// No need to sort, as it slows things down
// 53.33% - 96.95%
class Solution {
  public:
    const char EMPTY = '.';
    const char ONE = '1';
    const int SIZE = 9;
    const int S_SIZE = 3;

    void solveSudoku(vector<vector<char>>& board) {
      vector<vector<Cell*>> cells(SIZE, vector<Cell*>(SIZE, nullptr));
      vector<Cell*> cellsList;
      for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
          if(board[i][j] == EMPTY) {
            cells[i][j] = new Cell(i, j);
            getInvalids(cells[i][j], board, false);
            cellsList.push_back(cells[i][j]);
            cells[i][j]->currDigits = cells[i][j]->origDigits;
          }
        }
      }

      // Perform search
      Cell* currCell;
      int idx;
      for(int i = 0; i >= 0 && i < cellsList.size(); ) {
        currCell = cellsList[i];

        // Update according to the board
        getInvalids(currCell, board, true);
        idx = getNextPossibleIdx(currCell);

        // Invalid found
        if(idx == SIZE) {
          currCell->currDigits = currCell->origDigits;
          board[currCell->i][currCell->j] = EMPTY;
          // cout << "Invalid at " << currCell->i << " " << currCell->j << endl;
          i--;
        }

        // Else try solution
        else {
          board[currCell->i][currCell->j] = idx + ONE;
          currCell->currDigits.set(idx, 1);
          // cout << "Fill " << currCell->i << "," << currCell->j << " " << (idx+1) << endl;
          i++;
        }
      }

      // Delete cells matrix
      for(Cell* c: cellsList) {
        delete(c);
      }
    }

    int getNextPossibleIdx(Cell* cell) {
      for(int i = 0; i < SIZE; i++) {
        if(!cell->currDigits[i]) return i;
      }
      return SIZE;
    }

    void getInvalids(Cell* cell, vector<vector<char>>& board, bool test) {
      int i = cell->i;
      int j = cell->j;
      int I = i/S_SIZE*S_SIZE;
      int J = j/S_SIZE*S_SIZE;

      bitset<9>& set = (test? cell->currDigits: cell->origDigits);
      for(int k = 0; k < SIZE; k++) {
        if(board[i][k] != EMPTY) set.set(board[i][k]-ONE, 1);
        if(board[k][j] != EMPTY) set.set(board[k][j]-ONE, 1);
        if(board[I+k/S_SIZE][J+k%S_SIZE] != EMPTY) set.set(board[I+k/S_SIZE][J+k%S_SIZE]-ONE, 1);
      }

      // Print in reverse order (why...?)
      // cout << i << ", " << j << ": " << cell->origDigits.to_string<char,std::string::traits_type,std::string::allocator_type>() << endl;
    }
};

int main() {
  Solution s;

  vector<char> l1 = {'5','3','.','.','7','.','.','.','.'};
  vector<char> l2 = {'6','.','.','1','9','5','.','.','.'};
  vector<char> l3 = {'.','9','8','.','.','.','.','6','.'};
  vector<char> l4 = {'8','.','.','.','6','.','.','.','3'};
  vector<char> l5 = {'4','.','.','8','.','3','.','.','1'};
  vector<char> l6 = {'7','.','.','.','2','.','.','.','6'};
  vector<char> l7 = {'.','6','.','.','.','.','2','8','.'};
  vector<char> l8 = {'.','.','.','4','1','9','.','.','5'};
  vector<char> l9 = {'.','.','.','.','8','.','.','7','9'};

  vector<vector<char>> board = {l1,l2,l3,l4,l5,l6,l7,l8,l9};

  s.solveSudoku(board);
  for(vector<char>& v: board) {
    for(char i: v) cout << i << " ";
    cout << endl;
  }
}
