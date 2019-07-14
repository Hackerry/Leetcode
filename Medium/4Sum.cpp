#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
      vector<vector<int>> result;
      if(nums.size() < 4) return result;

      sort(nums.begin(), nums.end());
      int first, second, third, fourth;
      int i,j;
      i = 0;
      while(i < nums.size()-3) {
        first  = i;
        j = i+1;

        while(j < nums.size()-2) {
          second = j;

          third = j+1;
          fourth = nums.size()-1;
          while(third < fourth) {
            if(nums[first]+nums[second]+nums[third]+nums[fourth] == target) {
              vector<int> newList;
              newList.push_back(nums[first]);
              newList.push_back(nums[second]);
              newList.push_back(nums[third]);
              newList.push_back(nums[fourth]);
              result.push_back(newList);

              while(++third < fourth && nums[third] == nums[third-1]);
              while(--fourth > third && nums[fourth] == nums[fourth+1]);
            } else if(nums[first]+nums[second]+nums[third]+nums[fourth] < target) {
              while(++third < fourth && nums[third] == nums[third-1]);
            } else {
              while(--fourth > third && nums[fourth] == nums[fourth+1]);
            }
          }

          while(++j < nums.size()-2 && nums[j] == nums[j-1]);
        }

        while(++i < nums.size()-3 && nums[i] == nums[i-1]);
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> input = {1, 0, -1, 0, -2, 2};

  for(vector<int> v: s.fourSum(input, 0)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
