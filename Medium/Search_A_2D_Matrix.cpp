#include <iostream>
#include <vector>
#include "../Collections/Parser.cpp"

using namespace std;

class Solution {
  public:
    // My solution - doesn't get the gist of this problem
    bool searchMatrixMy(vector<vector<int>>& matrix, int target) {
      // Edge case
      if(matrix.size() == 0 || matrix[0].size() == 0) return false;

      int lo, hi, mid;

      // Search row first
      lo = 0;
      hi = matrix.size()-1;
      while(lo <= hi) {
        mid = (hi-lo)/2 + lo;

        if(matrix[mid][0] == target) return true;
        else if(matrix[mid][0] < target) lo = mid + 1;
        else hi = mid - 1;
      }

      // Row number goes out of range
      if(hi == -1) return false;

      int row = hi;
      lo = 0;
      hi = matrix[row].size()-1;
      while(lo <= hi) {
        mid = (hi-lo)/2 + lo;

        if(matrix[row][mid] == target) return true;
        else if(matrix[row][mid] < target) lo = mid + 1;
        else hi = mid - 1;
      }

      return false;
    }

    // Treat it as a sorted list
    // https://leetcode.com/problems/search-a-2d-matrix/discuss/26220/Don't-treat-it-as-a-2D-matrix-just-treat-it-as-a-sorted-list
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
      int n = matrix.size();
      int m = matrix[0].size();
      int l = 0, r = m * n - 1;
      while (l != r){
        int mid = (l + r - 1) >> 1;
        if (matrix[mid / m][mid % m] < target)
          l = mid + 1;
        else 
          r = mid;
      }
      return matrix[r / m][r % m] == target;
    }
};

int main() {
  Solution s;
  Parser p;
  vector<int> searchList = {3,8,10,0,60,16,20,7,9};
  vector<vector<int>> input = p.parse2DList(/*"[[1,3,5,7],[10,11,16,20],[23,30,34,50]]"*/"[[0,3,9]]");
  for(int i: searchList)
    cout << "Find " << i << ": " << s.searchMatrix(input, i) << endl;
}
