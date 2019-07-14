#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int threeSumClosest(vector<int>& nums, int target) {
      return better(nums, target);
    }

    // O(N^3)
    int nCube(vector<int>& nums, int target) {
      if(nums.size() < 3) return 0;

      // Sort the list first
      sort(nums.begin(), nums.end());

      int start, end;
      int currShift = 0;
      int currMinShift = numeric_limits<int>::max();
      int toFind;
      for(int index = 0; index < nums.size()-2; index++) {
        for(start = index+1; start < nums.size()-1; start++) {
          // Try to find the exact value and update the minimum difference
          toFind = target-nums[start]-nums[index];
          currShift = numeric_limits<int>::max();
          for(end = start+1; end < nums.size(); end++) {
            // If we are moving further in the sorted list, break out
            if(abs(nums[end]-toFind) <= abs(currShift)) {
              currShift = nums[end] - toFind;
            } else break;
          }

          // Update global min difference
          if(abs(currMinShift) > abs(currShift)) currMinShift = currShift;
        }
      }

      return target+currMinShift;
    }

    // Use two pointer
    // Still (N^2)
    int better(vector<int>& nums, int target) {
      if(nums.size() < 3) return 0;

      // Sort the list first
      sort(nums.begin(), nums.end());

      int start, end;
      int minShift = numeric_limits<int>::max();
      int currShift;
      int diff;
      int index = 0;
      while(index < nums.size()-2) {
        start = index+1;
        end = nums.size()-1;

        currShift = numeric_limits<int>::max();
        while(start < end) {
          diff = nums[index]+nums[start]+nums[end]-target;

          // Update min(diff)
          if(abs(diff) < abs(currShift)) currShift = diff;
          // Can't break here as moving the end and start may improve the result
          // Ex: -5 0 2 3 5 / -2

          // Approach min(diff) and return target if a sum is present
          if(diff < 0) while(++start < nums.size() && nums[start] == nums[start-1]);
          else if(diff > 0) while(--end >= start && nums[end] == nums[end+1]);
          else return target;
        }

        // Update global min difference
        if(abs(minShift) > abs(currShift)) minShift = currShift;

        while(++index < nums.size()-2 && nums[index] == nums[index-1]);
      }

      return target+minShift;
    }
};

int main() {
  Solution s;
  vector<int> input = {/*-1, 2, 1, -40,2,1,-3*/4,0,5,-5,3,3,0,-4,-5};

  cout << s.threeSumClosest(input, -2) << endl;
}
