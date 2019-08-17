#include <iostream>
#include <vector>
#include <queue>
#include "../Collections/Parser.cpp"

using namespace std;

class Solution {
  public:
    // Problem - change the original grid
    int minPathSum(vector<vector<int>>& grid) {
      if(grid.size() == 0) return 0;

      int N = grid.size();
      int M = grid[0].size();
      for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
          if(i == 0 && j == 0) {
            grid[i][j] = grid[i][j];
          } else if(i == 0) {
            grid[i][j] = grid[i][j-1] + grid[i][j];
          } else if(j == 0) {
            grid[i][j] = grid[i-1][j] + grid[i][j];
          } else {
            grid[i][j] = min(grid[i-1][j], grid[i][j-1]) + grid[i][j];
          }
        }
      }

      return grid[N-1][M-1];
    }
};

int main() {
  Solution s;
  Parser p;
  vector<vector<int>> board = p.parse2DList("[[1]]");
  cout << s.minPathSum(board) << endl;
}
