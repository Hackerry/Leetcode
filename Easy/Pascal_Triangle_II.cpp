#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> getRow(int rowIndex) {
      vector<int> result = {1};

      if(rowIndex == 0) return vector<int>(result);
      result.push_back(1);
      if(rowIndex == 1) return vector<int>(result);

      for(int i = 1; i < rowIndex; i++) {
        for(int j = 1; j < result.size(); j++) {
          result[j-1] = result[j-1] + result[j];
        }
        result.insert(result.begin(), 1);
      }

      return vector<int>(result);
    }
};

int main() {
  Solution s;
  for(int i: s.getRow(2)) {
    cout << i << " ";
  }
  cout << endl;
}
