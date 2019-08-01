#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // Original solution
    // Find the next longest range to jump
    // Iterate over this range and find the next jump
    // Or return false if we are stalled
    bool canJumpOriginal(vector<int>& nums) {
      int start = 0;
      int end = 0;

      int maxVal = 0;
      while(end < nums.size()-1) {
        maxVal = end;
        for(int i = start; i <= end; i++) {
          if(nums[i] + i > maxVal) maxVal = nums[i] + i;
        }

        // Still can jump
        if(maxVal > end) {
          start = end;
          end = maxVal;
        } else {
          // Can't jump any more
          return false;
        }
      }

      return true;
    }

    // Another solution, going backwards
    // Much cleaner and slower (consider 6,5,4,3,2,1 where each number is updated)
    bool canJump(vector<int>& nums) {
      if(nums.size() <= 1) return true;
      int idx = nums.size()-1;

      for(int i = nums.size()-1; i >= 0; i--) {
        if(i < idx && i + nums[i] >= idx) idx = i;
      }

      return idx == 0;
    }
};

int main() {
  Solution s;

  vector<int> input = {3,0};
  cout << s.canJump(input) << endl;
}
