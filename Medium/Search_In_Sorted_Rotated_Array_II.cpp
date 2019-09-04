#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // mem usage 100%
    bool search(vector<int>& nums, int target) {
      if(nums.size() == 0) return false;

      int i = 0;
      int j = nums.size()-1;
      int start = nums[i];
      int end = nums[j];
      int mid;

      // Worst case O(N), find the representative value for end
      if(start == end) {
        while(j > 0 && start == nums[j]) j--;
        end = nums[j];
      }
      if(target == start || target == end) return true;

      while(i <= j) {
        mid = i+(j-i)/2;

        // Target in the right half
        if(target < end) {
          // Still in the left half
          if(nums[mid] > end) i = mid+1;
          else {
            if(nums[mid] < target) i = mid+1;
            else if(nums[mid] > target) j = mid-1;
            else return true;
          }
        } else if(target > start) {
          // Still in the right half
          if(nums[mid] < start) j = mid-1;
          else {
            if(nums[mid] < target) i = mid+1;
            else if(nums[mid] > target) j = mid-1;
            else return true;
          }
        } else return false;
      }

      return false;
    }
};

int main() {
  Solution s;
  vector<int> input = {2,2,3,3,0,1,1};
  cout << s.search(input, 0) << endl;
}
