#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    int singleNumber(vector<int>& nums) {
      int val = nums[0];
      for(int i = 1; i < nums.size(); i++) val ^= nums[i];

      return val;
    }
};

int main() {
  Solution s;
  vector<int> input = {4,1,2,1,2};

  cout << s.singleNumber(input) << endl;
}
