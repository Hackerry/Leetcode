#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Solution {
  public:
    // A compromise, using unsigned to avoid interger overflow
    // O(MxN)
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
      unsigned int m = obstacleGrid.size();
      unsigned int n = obstacleGrid[0].size();
      unsigned int matrix[m][n];

      // Cutoff for row and column, can't be reached
      char rowCutOff = false;
      char colCutOff = false;

      for(unsigned int i = 0; i < m; i++) {
        for(unsigned int j = 0; j < n; j++) {
          if(obstacleGrid[i][j]) {
            matrix[i][j] = 0;
            if(i == 0) rowCutOff = true;
            if(j == 0) colCutOff = true;
          }
          else if(i == 0) {
            if(rowCutOff) matrix[i][j] = 0;
            else matrix[i][j] = 1;
          }
          else if(j == 0) {
            if(colCutOff) matrix[i][j] = 0;
            else matrix[i][j] = 1;
          }
          else matrix[i][j] = matrix[i-1][j] + matrix[i][j-1];
        }
      }

      return matrix[m-1][n-1];
    }
};

int main() {
  vector<int> l1 = {0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0};
  vector<int> l2 = {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
  vector<int> l3 = {0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0};
  vector<int> l4 = {1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1};
  vector<int> l5 = {0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0};
  vector<int> l6 = {0,0,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0};
  vector<int> l7 = {1,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0};
  vector<int> l8 = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0};
  vector<int> l9 = {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0};
  vector<int> l10 = {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0};
  vector<int> l11 = {0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};
  vector<int> l12 = {1,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,1};
  vector<int> l13 = {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0};
  vector<int> l14 = {0,1,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0};
  vector<int> l15 = {0,1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1};
  vector<int> l16 = {1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  vector<int> l17 = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0};
  vector<int> l18 = {0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1};
  vector<int> l19 = {0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1};
  vector<int> l20 = {1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0};
  vector<int> l21 = {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1};
  vector<int> l22 = {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0};
 
  Solution s;
  vector<vector<int>> input = {l1,l2,l3,l4,l5,l6,l7,l8,l9,l10,l11,l12,l13,l14,l15,l16,l17,l18,l19,l20,l21,l22};
  cout << s.uniquePathsWithObstacles(input) << endl;
}
