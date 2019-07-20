#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
  public:
    bool isValidSudoku(vector<vector<char>>& board) {
      const int NUM = 9;
      const char EMPTY = '.';
      const char ZERO = '0';

      bitset<10> digits;

      char cell;
      // Check rows
      for(int i = 0; i < NUM; i++) {
        digits.reset();
        for(int j = 0; j < NUM; j++) {
          cell = board[i][j];
          if(cell != EMPTY) {
            // If this bit has been set, return false
            if(digits[cell - ZERO]) return false;
            else digits.set(cell - ZERO, true);
          }
        }
      }

      // Check cols
      for(int i = 0; i < NUM; i++) {
        digits.reset();
        for(int j = 0; j < NUM; j++) {
          cell = board[j][i];
          if(cell != EMPTY) {
            // If this bit has been set, return false
            if(digits[cell - ZERO]) return false;
            else digits.set(cell - ZERO, true);
          }
        }
      }

      // Check squares
      const int SIZE = 3;
      for(int i = 0; i < NUM/SIZE; i++) {
        for(int j = 0; j < NUM/SIZE; j++) {
          digits.reset();
          for(int k = 0; k < NUM; k++) {
            cell = board[i*SIZE+k/SIZE][j*SIZE+k%SIZE];
            if(cell != EMPTY) {
              // This bit has been set
              if(digits[cell - ZERO]) return false;
              else digits.set(cell - ZERO, true);
            }
          }
        }
      }

      // It's a valid sudoku
      return true;
    }
};
