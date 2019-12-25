#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // Dynamic programming
    // dp[i][j] = text[i:] and pattern[j:] match
    // Cases:
    // 1. Current character is a match
    //    a. This character is optional(*) in pattern
    //        i. Don't consume input and omit the pattern, dp[i][j+2] is already a match
    //       ii. Take the input and test whether dp[i+1][j] is a match
    //    b. This character is not optional
    //       Depends on i) it's a match ii) dp[i+1][j+1] is a match
    // 2. Current character isn't a match
    //    a. This character is optional(*)
    //       Depends on dp[i][j+2]
    //    b. This character is not optional
    //       False
    bool isMatch(string text, string pattern) {
      int T = text.size();
      int P = pattern.size();
      vector<vector<bool>> dp(T+1, vector<bool>(P+1, 0));
      dp[T][P] = 1;

      for(int i = T; i>= 0; i--) {
        for(int j = P-1; j >= 0; j--) {
          bool firstMatch = (i < T && (pattern[j] == text[i] || pattern[j] == '.'));

          if(j + 1 < P && pattern[j+1] == '*') {
            dp[i][j] = dp[i][j+2] || (firstMatch && dp[i+1][j]);
          } else {
            dp[i][j] = firstMatch && dp[i+1][j+1];
          }
        }
      }

      // Debug output
      cout << "  ";
      for(char c: pattern) cout << c << " ";
      cout << endl;
      for(int i = 0; i < T+1; i++) {
        cout << (i == T? ' ': text[i]) << " ";
        for(int j = 0; j < P+1; j++) {
          cout << dp[i][j] << " ";
        }
        cout << endl;
      }

      return dp[0][0];
    }
};

int main() {
  Solution s;
  string pattern = "a*b*c";
  string text = "ac";
  cout << s.isMatch(text, pattern) << endl;
}
