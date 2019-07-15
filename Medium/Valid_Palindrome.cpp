#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

class Solution {
  public:
    bool isPalindrome(string s) {
      if(s == "") return true;

      int start = 0;
      int end = s.size()-1;
      while(start < end) {
        if(!isalnum(s[start])) start++;
        else if(!isalnum(s[end])) end--;
        else {
          if(isalpha(s[start]) && isalpha(s[end])) {
            if(tolower(s[start]) != tolower(s[end])) return false;
            start++;
            end--;
          } else if(isdigit(s[start]) && isdigit(s[end])) {
            if(s[start] != s[end]) return false;
            start++;
            end--;
          } else return false;
        }
      }

      return true;
    }
};

int main() {
  Solution s;

  vector<string> input = {"A man, a plan, a canal: Panama", "race a car"};

  for(string ss: input) {
    cout << ss << ": " << (s.isPalindrome(ss)==1? "true": "false") << endl;
  }
}
