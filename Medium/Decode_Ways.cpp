#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // 0ms Hooray!!!!
    // Lots of edge cases. I can see why so many people downvoted it.
    int numDecodings(string s) {
      int L = s.size();
      vector<int> numWays(L+1, 0);
      numWays[0] = 1;

      if(s[0] != '0') numWays[1] = 1;
      for(int i = 1; i < L; i++) {
        numWays[i+1] = numWays[i];

        // Cases with 0
        if(s[i] == '0') {
          // If previous number isn't valid '10/20', set to 0
          if(s[i-1] < '1' || s[i-1] > '2')
            numWays[i+1] = 0;
          // If previous number is valid, it can't be a valid solution for n-1
          // eg. 'XX10'
          else
            numWays[i+1] = numWays[i-1];
        } else if((s[i-1] == '1' && s[i] != '0') || (s[i-1] == '2' && s[i] > '0' && s[i] < '7'))
          // Can form a valid double-digit number with previous number
          numWays[i+1] += numWays[i-1];
      }

      return numWays[L];
    }
};

int main() {
  Solution s;
  vector<string> input = {"1232", "1210", "2220", "102", "1020", "1", "222322", "0", "0123", "100", "10022", "302", "110", "11010"};
  for(string str: input) {
    cout << str << ": " << s.numDecodings(str) << endl;
  }
}
