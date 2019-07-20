#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> searchRange(vector<int>& nums, int target) {
      if(nums.size() == 0) return vector<int>{-1,-1};

      int start = binarySearch(target-1, nums, 0, nums.size()-1);
      int end = binarySearch(target, nums, 0, nums.size()-1);

      // Value doesn't exsist
      // {7} return 1,1 {8} return 0,1 {10} return 0,0
      // if two values are the same, then value doesn't exsist
      if(start == end)
        return vector<int>{-1,-1};
      else
        return vector<int>{start, end-1};
    }

    // Helper function to find the smallest number which is larger than target
    // and return that number's index
    int binarySearch(int target, vector<int>& nums, int start, int end) {
      if(nums.size() == 0 || start > end) return -1;

      int mid;
      while(start <= end) {
        mid = (start+end)/2;

        if(nums[mid] <= target) {
          start = mid+1;
        } else if(nums[mid] > target) {
          end = mid-1;
        }
      }

      return start;
    }
};

int main() {
  Solution s;
  vector<int> input = {7,10};
  int target = 8;

  for(int i: s.searchRange(input, target)) cout << i << " ";
  cout << endl;
}
