#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<vector<int>> generate(int numRows) {
      vector<vector<int>> result;

      if(numRows == 0) return result;
      vector<int> currRow = {1};
      result.push_back(currRow);

      for(int i = 1; i < numRows; i++) {
        currRow = vector<int>();
        currRow.push_back(1);

        for(int j = 0; j < i-1; j++) {
          currRow.push_back(result[i-1][j] + result[i-1][j+1]);
        }
        currRow.push_back(1);

        result.push_back(currRow);
      }

      return result;
    }
};

int main() {
  Solution s;
  for(vector<int> v: s.generate(2)) {
    for(int i: v) {
      cout << i << " ";
    }
    cout << endl;
  }
}
