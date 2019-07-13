#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // Hooray! A greate solution at first shot!
    int trap(vector<int>& height) {
      if(height.size() <= 1) return 0;

      int start = 0;
      int end = height.size()-1;
      int totalTrapped = 0;
      int mid;
      while(start < end) {
        if(height[start] < height[end]) {
          mid = start;
          while(++mid <= end && height[mid] < height[start])
            totalTrapped += (height[start]-height[mid]);

          start = mid;
        } else {
          mid = end;
          while(--mid >= start && height[mid] < height[end])
            totalTrapped += (height[end]-height[mid]);

          end = mid;
        }
      }

      return totalTrapped;
    }
};

int main() {
  Solution s;
  vector<int> input = {7,1,2,3,4,5,6};

  cout << s.trap(input) << endl;
}
