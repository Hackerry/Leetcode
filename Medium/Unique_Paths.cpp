#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
  public:
    // Critical observation:
    // Path entering matrix[i][j] is the sum of matrix[i-1][j] and matrix[i][j-1]
    int uniquePaths(int m, int n) {
      int matrix[m][n];

      for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
          if(i == 0) matrix[i][j] = 1;
          else if(j == 0) matrix[i][j] = 1;
          else {
            matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
          }
        }
      }

      return matrix[m-1][n-1];
    }

    // Space limit exceeds
    int uniquePathsNaive(int m, int n) {
      int goal = m*n-1;
      int count = 0;
      list<int> positions = {0};

      int currPos = 0;
      while(!positions.empty()) {
        currPos = positions.front();
        positions.pop_front();

        // One possible way reached
        if(currPos == goal) {
          count++;
          continue;
        }

        // One way right
        if(currPos % m < m-1) positions.push_back(currPos+1);
        // One way down
        if(currPos / m < n-1) positions.push_back(currPos+m);
      }

      return count;
    }
};

int main() {
  Solution s;

  vector<int> ms = {1,2,3,4,3,2,1,7};
  vector<int> ns = {4,2,2,4,5,10,1,3};
  for(int i = 0; i < ms.size(); i++) {
    cout << ms[i] << "x" << ns[i] << ": " << s.uniquePaths(ms[i], ns[i]) << endl;
  }
}
