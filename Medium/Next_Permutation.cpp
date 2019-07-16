#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

class Solution {
  public:
    void nextPermutation(vector<int>& nums) {
      return fastPermutation(nums);
    }

    // O(N) -- 3 passes
    // Find the last of a increasing sequence starting from the end of the list
    // Replace the previous number with the next larger number in the sequence
    // Then reverse the order of the list starting from the last position
    // ps. Swapping the two numbers doesn't break the sorting
    void fastPermutation(vector<int>& nums) {
      if(nums.size() <= 1) return;

      int index, temp;
      for(index = nums.size()-1; index > 0; index-- ) {
        if(nums[index] > nums[index-1]) break;
      }

      // Next permutation exsists
      if(index != 0) {
        for(int i = nums.size()-1; i >= index; i--) {
          // Swap the next larg element to desired position
          if(nums[i] > nums[index-1]) {
            temp = nums[i];
            nums[i] = nums[index-1];
            nums[index-1] = temp;
            break;
          }
        }
      }

      // Reverse the order
      for(int i = 0; i < (nums.size()-index)/2; i++) {
        temp = nums[index+i];
        nums[index+i] = nums[nums.size()-i-1];
        nums[nums.size()-i-1] = temp;
      }
    }

    // O(N^2)
    // Find the last position that can be swapped
    void slowPermutation(vector<int>& nums) {
      if(nums.size() <= 1) return;

      int i, j;
      int maxIndex, swapIndex;
      maxIndex = -1;
      for(i = nums.size()-1; i >= 1 && i >= maxIndex; i--) {
        for(j = i-1; j >= 0 && j >= maxIndex; j--) {
          // Found the first smaller position to swap with
          if(nums[j] < nums[i] && j > maxIndex) {
            maxIndex = j;
            swapIndex = i;
            break;
          }
        }
      }

      // Next permutation doesn't exsist
      if(maxIndex == -1) sort(nums.begin(), nums.end());
      else {
        int temp = nums[maxIndex];
        nums[maxIndex] = nums[swapIndex];
        nums[swapIndex] = temp;
        sort(nums.begin()+maxIndex+1, nums.end());
      }
    }
};

int main() {
  srand(time(NULL));
  vector<int> nums;
  Solution s;

  for(int i = 0; i < 20; i++) {
    nums.clear();
    for(int i = 0; i < 5; i++) {
      nums.push_back(rand() % 50);
    }

    cout << "[";
    for(int i: nums) cout << i << " ";
    cout << "] -> [";
    s.nextPermutation(nums);
    for(int i: nums) cout << i << " ";
    cout << "]" << endl;
  }
}
