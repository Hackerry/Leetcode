#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // Professor Cao metioned this during algorithm class
    int majorityElement(vector<int>& nums) {
      int prev = 0;
      int count = 0;

      for(int i: nums) {
        if(i == prev) count++;
        else if(count > 0) count--;
        else {
          prev = i;
          count = 1;
        }
      }

      return prev;
    }
};

int main() {
  Solution s;

  vector<int> input = {2,2,1,1,1,2,2};
  cout << "Majority: " << s.majorityElement(input) << endl;
}
