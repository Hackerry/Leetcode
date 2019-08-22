#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
  public:
    vector<vector<int>> subsets(vector<int>& nums) {
      vector<vector<int>> result;

      for(int i = 0; i < pow(2, nums.size()); i++) {
        vector<int> subset;
        int bits = i;

        for(int j = 0; j < nums.size(); j++) {
          if(bits & 1) subset.push_back(nums[j]);
          bits >>= 1;
        }

        result.push_back(subset);
      }

      return result;
    }
};

int main() {
  Solution s;

  vector<int> input = {1,2,3,4,5,6};
  for(vector<int>& v: s.subsets(input)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
