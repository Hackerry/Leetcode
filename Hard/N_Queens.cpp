#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<vector<string>> solveNQueens(int n) {
      vector<vector<string>> result;
      if(n < 1) return result;

      int half = (n%2 + n)/2;
      vector<string> newBoard;
      for(int i = 0; i < half; i++) {
        for(int j = 0; j < half; j++) {
          newBoard = getNewBoard(n);

          // Valid solution found
          if(testBoard(newBoard, i, j))
            result.push_back(newBoard);
        }
      }

      cout << result.size() << endl;
      return result;
    }

    vector<string> getNewBoard(int n) {
      vector<string> result;
      for(int i = 0; i < n; i++) {
        string s;
        for(int j = 0; j < n; j++) {
          s += 'O';
        }
        result.push_back(s);
      }

      return result;
    }

    bool testBoard(vector<string>& board, int I, int J) {
      int N = board.size();
      int num = board.size()-1;
      updateBoard(board, I, J);

      while(num > 0) {
        for(int i = 0; i < N; i++) {
          for(int j = 0; j < N; j++) {
            if(board[i][j] == 'O') {
              updateBoard(board, i, j);
              num--;
            }
          }
        }

        return false;
      }

      return true;
    }

    void updateBoard(vector<string>& board, int I, int J) {
      board[I][J] = 'Q';
      int n = board.size();

      // Update rows and cols
      for(int x = 0; x < n; x++) {
        if(x != I) board[x][J] = '.';
        if(x != J) board[I][x] = '.';
      }

      // Update diagonals
      int i = I-1;
      int j = J-1;
      while(i >= 0 && j >= 0) board[i--][j--] = '.';
      i = I+1; j = J-1;
      while(i < n && j >= 0) board[i++][j--] = '.';
      i = I-1; j = J+1;
      while(i >= 0 && j < n) board[i--][j++] = '.';
      i = I+1; j = J+1;
      while(i < n && j < n) board[i++][j++] = '.';
    }
};

int main() {
  Solution s;
  int input = 4;
  for(vector<string>& v: s.solveNQueens(input)) {
    for(string str: v) cout << str << endl;
    cout << endl;
  }
}
