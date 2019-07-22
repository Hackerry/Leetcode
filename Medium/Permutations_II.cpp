#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Copy of Permutations.cpp
    vector<vector<int>> permuteUnique(vector<int>& nums) { 
      vector<vector<int>> result;
      if(nums.size() == 0) return result;

      // Sort the list and set this permutation as the end point
      sort(nums.begin(), nums.end());
      result.push_back(nums);

      int index = nums.size()-1;
      int tempIdx;
      int tempVal;
      while(index >= 1) {
        // Find next permutation
        if(nums[index-1] < nums[index]) {
          // Find the smallest number larger than nums[index-1]
          for(tempIdx = nums.size()-1; tempIdx >= index; tempIdx--) {
            if(nums[tempIdx] > nums[index-1]) break;
          }

          // Swap two elements
          tempVal = nums[index-1];
          nums[index-1] = nums[tempIdx];
          nums[tempIdx] = tempVal;

          // Sort the changed part
          sort(nums.begin()+index, nums.end());
          index = nums.size()-1;

          // Add to result
          vector<int> answer(nums);
          result.push_back(answer);
        } else index--;
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> input = {1,1,3};

  for(vector<int>& v: s.permuteUnique(input)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
