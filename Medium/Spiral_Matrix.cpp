#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Genious solution: see solution 2
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
      vector<int> result;
      if(matrix.size() == 0) return result;

      int i1 = 0, j1 = 0;
      int i2 = matrix.size()-1, j2 = matrix[0].size()-1;

      while(i1 <= i2 && j1 <= j2) {
        for(int j = j1; j <= j2; j++) result.push_back(matrix[i1][j]);
        for(int i = i1+1; i <= i2; i++) result.push_back(matrix[i][j2]);

        if(i1 < i2 && j1 < j2) {
          for(int j = j2-1; j >= j1; j--) result.push_back(matrix[i2][j]);
          for(int i = i2-1; i > i1; i--) result.push_back(matrix[i][j1]);
        }

        i1++;
        i2--;
        j1++;
        j2--;
      }

      return result;
    }

    // Original solution
    // Verbose and slow
    vector<int> spiralOrderOriginal(vector<vector<int>>& matrix) {
      int loop = 0;

      vector<int> result;
      // Edge cases:
      // Empty list
      // List with either row or col # of 1
      if(matrix.size() == 0) return result;

      while(loop < min(matrix.size(), matrix[0].size())/2) {
        // Left to right
        for(int i = loop; i < matrix[loop].size()-loop; i++) {
          result.push_back(matrix[loop][i]);
        }

        // Up to down
        for(int i = loop+1; i < matrix.size()-loop; i++) {
          result.push_back(matrix[i][matrix[i].size()-loop-1]);
        }

        // Right to left
        for(int i = matrix[loop].size()-loop-2; i >= loop; i--) {
          result.push_back(matrix[matrix.size()-1-loop][i]);
        }

        // Down to up (remember to avoid duplicate of the starting point)
        for(int i = matrix.size()-2-loop; i > loop; i--) {
          result.push_back(matrix[i][loop]);
        }

        loop++;
      }

      // Deal with odd rows and cols
      char code = -1;
      if(matrix.size() % 2) {
        if(matrix.size() <= matrix[0].size()) code = 0;
        else if(matrix[0].size() % 2) code = 1;
      } else if(matrix[0].size() % 2) {
        if(matrix.size() >= matrix[0].size()) code = 1;
        else if(matrix.size() % 2) code = 0;
      }

      int mid;
      if(code == 0) {
        mid = matrix.size()/2;
        for(int i = loop; i < matrix[mid].size()-loop; i++) {
          result.push_back(matrix[mid][i]);
        }
      } else if(code == 1) {
        mid = matrix[0].size()/2;
        for(int i = loop; i < matrix.size()-loop; i++) {
          result.push_back(matrix[i][mid]);
        }
      }

      return result;
    }
};

int main() {
  Solution s;


  vector<int> l1 = {1,2,3,4,5};
  vector<int> l2 = {11,12,13,14,15};
  vector<int> l3 = {21,22,23,24,25};
  vector<int> l4 = {31,32,33,34,35};
  vector<int> l5 = {41,42,43,44,45};

  vector<int> l6 = {1,2,3};
  vector<int> l7 = {5,6,7};
  vector<int> l8 = {9,10,11};
  vector<int> l9 = {12,13,14};
  vector<int> l10 = {15,16,16};

  vector<int> l11 = {1,2,3};
  vector<int> l12 = {2};
  vector<int> l13 = {3};

  vector<vector<int>> input = {l1,l2,l3,l4};

  for(int i: s.spiralOrder(input)) cout << i << " ";
  cout << endl;
}
