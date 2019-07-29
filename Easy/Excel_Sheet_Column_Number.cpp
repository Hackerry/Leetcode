#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    int titleToNumber(string s) {
      const char A_CHAR = 'A';
      const int BASE = 26;
      int result = 0;

      for(char c: s) {
        result *= BASE;
        result += c-A_CHAR+1;
      }

      return result;
    }
};

int main() {
  Solution s;

  vector<string> input = {"A", "Z", "AA", "AB", "AZ", "BA", "BZ", "ZY"};
  for(string ss: input) {
    cout << ss << ": " << s.titleToNumber(ss) << endl;
  }
}
