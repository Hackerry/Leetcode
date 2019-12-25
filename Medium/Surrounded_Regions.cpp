#include <iostream>
#include <vector>
#include <queue>
#include "../Collections/Parser.cpp"

using namespace std;

class Solution {
  public:
    void solve(vector<vector<char>>& board) {
      int N = board.size();
      if(N == 0) return;
      int M = board[0].size();
      if(M == 0) return;
      vector<bool> connectedCols(M, false);

      // Initialize first row
      for(int i = 0; i < M-1; i++) {
        if(board[0][i] == 'O') connectedCols[i] = true;
      }

      // Search from top & left
      for(int i = 1; i < N-1; i++) {
        // Set first to be connected if it's O
        if(board[i][0] == 'O') connectedCols[0] = true;

        for(int j = 1; j < M-1; j++) {
          if(board[i][j] == 'O') {
            // If it's not connected to edges, set it to . for now
            connectedCols[j] = connectedCols[j-1] | connectedCols[j];
            if(!connectedCols[j]) board[i][j] = '.';
          } else connectedCols[j] = false;
        }
      }

      // Initialize last row
      for(int i = 1; i < M; i++) {
        if(board[N-1][i] == 'X') connectedCols[i] = false;
        else connectedCols[i] = true;
      }

      // Search from bottom & right
      for(int i = N-1; i >= 0; i--) {
        // Set last to be connected if it's O
        if(board[i][M-1] == 'O') connectedCols[M-1] = true;

        for(int j = M-1; j >= 0; j--) {
          if(board[i][j] != 'X') {
            connectedCols[j] = connectedCols[j+1] | connectedCols[j];

            if(board[i][j] == '.') {
              // If it's connected, set it back to O
              if(connectedCols[j]) board[i][j] = 'O';
              // If not, flip it to X
              if(!connectedCols[j]) board[i][j] = 'X';
            }
          } else connectedCols[j] = false;
        }
      }
    }
};

int main() {
  Solution s;
  Parser p;

  vector<vector<char>> input = p.parse2DChar("[['O','O','O','O','X','X'],['O','O','O','O','O','O'],['O','X','O','X','O','O'],['O','X','O','O','X','O'],['O','X','O','X','O','O'],['O','X','O','O','O','O']]");
  s.solve(input);
  for(vector<char>& v: input) {
    for(char c: v) cout << c;
    cout << endl;
  }
}
