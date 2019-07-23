#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> twoSum(vector<int>& numbers, int target) {
      int start = 0;
      int end = numbers.size()-1;

      int sum;
      while(start < end) {
        sum = numbers[start]+numbers[end];
        if(sum == target) break;
        else if(sum < target) start++;
        else end--;
      }

      return vector<int>{start+1, end+1};
    }
};

int main() {
  Solution s;

  vector<int> input = {2,7,11,15,17};
  int target = 17;

  vector<int> result = s.twoSum(input, target);
  cout << "[" << result[0] << "," << result[1] << "]" << endl;
}
