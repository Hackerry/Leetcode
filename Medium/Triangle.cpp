#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "../Collections/Parser.cpp"

using namespace std;

class Solution {
  public:
    // Original solution, top-down, two passes
    // Not so good as I have to store the changed value
    int minimumTotalOri(vector<vector<int>>& triangle) {
      int N = triangle.size();
      vector<int> aux(N, 0);

      // Start traversing
      int temp, newVal;
      for(int i = 0; i < N; i++) {
        temp = aux[0];
        aux[0] += triangle[i][0];
        for(int j = 1; j < i; j++) {
          newVal = triangle[i][j] + min(temp, aux[j]);
          temp = aux[j];
          aux[j] = newVal;
        }

        // Skip first line
        if(i != 0) aux[i] = triangle[i][i] + temp;
      }

      // Find minimum
      int minimum = numeric_limits<int>::max();
      for(int i: aux) {
        if(i < minimum) minimum = i;
      }

      return minimum;
    }

    // Discussion solution
    // https://leetcode.com/problems/triangle/discuss/38730/DP-Solution-for-Triangle
    // Bottom up, one pass, no need to store temp value
    int minimumTotal(vector<vector<int>>& triangle) {
      vector<int> aux = triangle.back();
      int N = triangle.size();

      for(int i = N-2; i >= 0; i--) {
        for(int j = 0; j < i+1; j++) {
          aux[j] = min(aux[j], aux[j+1]) + triangle[i][j];
        }
      }

      return aux[0];
    }
};

int main() {
  Solution s;
  Parser p;
  vector<vector<int>> list = p.parse2DInt("[[-1],[2,3],[1,-1,-3]]");
  cout << s.minimumTotal(list) << endl;
}
