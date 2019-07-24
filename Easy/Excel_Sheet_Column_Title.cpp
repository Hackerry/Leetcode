#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Although it seems like a number system with base 26, this system has no 0
    // 26 - Z -> 27 - A0 but it jumps directly to AA - 28
    // So when converting across powers of 26, subtract one to account for 0
    string convertToTitle(int n) {
      const int BASE = 26;
      const char ZERO_IDX = 'A';

      string result = "";

      while(n > 0) {
        result += ((n-1) % BASE + ZERO_IDX);
        n = (n-1)/BASE;
      }

      reverse(result.begin(), result.end());
      return result;
    }
};

int main() {
  Solution s;

  vector<int> input = {1,2,3,4,24,25,26,27,50,51,52,53,701};

  for(int i: input) {
    cout << i << ": " << s.convertToTitle(i) << endl;
  }
}
