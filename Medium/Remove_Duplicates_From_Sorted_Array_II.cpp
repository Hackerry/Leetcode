#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/discuss/27976/3-6-easy-lines-C%2B%2B-Java-Python-Ruby
    int removeDuplicates(vector<int>& nums) {
      int i = 0;
      for(int n: nums) {
        if(i < 2 || n > nums[i-2])
          nums[i++] = n;
      }

      return i;
    }

    int removeDuplicatesSecond(vector<int>& nums) {
      int N = nums.size();
      if(N <= 2) return nums.size();

      int idx = 1;
      int prev = nums[0];
      for(int i = 1; i < N; i++) {
        if(nums[i] == nums[i-1]) {
          nums[idx++] = nums[i];
          prev = nums[i];

          while(++i < N && prev == nums[i]);
        }
        if(i < N) nums[idx++] = nums[i];
      }

      return idx;
    }

    int removeDuplicatesFirst(vector<int>& nums) {
      if(nums.size() == 0) return 0;

      int prev = nums[0];
      int count = 0;
      int prevIdx = -1;
      for(int i = 0; i < nums.size(); i++) {
        if(prev != nums[i]) {
          prev = nums[i];
          count = 1;
        } else {
          if(++count > 2) {
            if(prevIdx == -1) prevIdx = i;
            continue;
          }
        }

        // Swap
        if(prevIdx != -1) {
          nums[prevIdx++] = nums[i];
        }
      }

      return prevIdx == -1? nums.size(): prevIdx;
    }
};

int main() {
  Solution s;
  vector<int> input = {1,1,1,1,2,2,3,3,3,4,4};

  int len = s.removeDuplicates(input);
  cout << len << endl;
  for(int i = 0; i < len; i++) cout << input[i] << " ";
  cout << endl;
}
