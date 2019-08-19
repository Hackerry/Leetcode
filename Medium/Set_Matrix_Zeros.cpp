#include <iostream>
#include <vector>
#include "../Collections/Parser.cpp"

using namespace std;

class Solution {
  public:
    // Solution 3!!!!
    void setZeroes(vector<vector<int>>& matrix) {
      int N = matrix.size();
      int M = matrix[0].size();
      char topRowZero = false;

      for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
          if(matrix[i][j] == 0) {
            matrix[0][j] = 0;
            if(i != 0) matrix[i][0] = 0;

            if(i == 0) topRowZero = true;
          }
        }
      }

      for(int i = 1; i < N; i++) {
        if(matrix[i][0] == 0) {
          for(int j = 1; j < M; j++) {
            matrix[i][j] = 0;
          }
        }
      }

      for(int j = 0; j < M; j++) {
        if(matrix[0][j] == 0) {
          for(int i = 0; i < N; i++) {
            matrix[i][j] = 0;
          }
        }
      }

      if(topRowZero) {
        for(int j = 0; j < M; j++) {
          matrix[0][j] = 0;
        }
      }
    }
};

int main() {
  Solution s;
  Parser p;
  vector<vector<int>> input = p.parse2DList("[[0,1,2,0],[3,4,5,2],[1,3,1,5]]");
  for(vector<int>& v: input) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
  cout << "==================" << endl;

  s.setZeroes(input);
  for(vector<int>& v: input) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
