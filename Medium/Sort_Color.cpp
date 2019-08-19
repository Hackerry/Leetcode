#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // 3-Sort algorithm
    void sortColors(vector<int>& nums) {
      int start = 0, mid = 0, end = nums.size()-1;
      int temp;

      while(mid <= end) {
        if(nums[mid] == 0) {
          temp = nums[mid];
          nums[mid] = nums[start];
          nums[start] = temp;
          start++;
        } else if(nums[mid] == 2) {
          temp = nums[end];
          nums[end] = nums[mid];
          nums[mid] = temp;
          end--;
          mid--;
        }

        mid++;
      }
    }
};

int main() {
  Solution s;
  vector<int> input = {2,0,2,1,1,0};
  for(int i: input) cout << i << " ";
  cout << endl;
  s.sortColors(input);
  for(int i: input) cout << i << " ";
  cout << endl;
}
