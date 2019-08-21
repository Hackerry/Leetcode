#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Solution 3
    // It's fast!
    // Keep track of indices and update max along the way
    int longestValidParenthesesSolution(string s) {
      vector<int> idx;
      idx.push_back(-1);
      int maxans = 0;

      for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') {
          idx.push_back(i);
        } else {
          idx.pop_back();
          if(idx.empty()) {
            idx.push_back(i);
          } else {
            maxans = max(maxans, i-idx.back());
          }
        }
      }

      return maxans;
    }

    // Solution 4
    // Who is this genius???
    // Space O(1)
    // Crucial oberservation:
    // The only way to cut off two parts from left to right is ')'
    // The only way to cut off two parts from right to left is '('
    int longestValidParentheses(string s) {
      int left = 0, right = 0;
      int maxans = 0;

      for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') left++;
        else if(s[i] == ')') right++;

        if(left == right) maxans = max(maxans, left+right);
        else if(right > left) left = right = 0;
      }

      left = 0;
      right = 0;
      for(int i = s.size()-1; i >= 0; i--) {
        if(s[i] == '(') left++;
        else if(s[i] == ')') right++;

        if(left == right) maxans = max(maxans, left+right);
        else if(right < left) left = right = 0;
      }

      return maxans;
    }

    // My solution, not bad
    // 59% - 68%
    // Store the number of valid '(' so far
    // ())(())
    // 0 -> 0 0 -> 1 -> 0 -> 0 0 -> 0 0 0 -> 0 1 -> 2 * 2 = 4
    int longestValidParenthesesMy(string s) {
      vector<int> stack;
      int currVal;
      int maxNow = 0;
      // Virtual head
      stack.push_back(0);

      for(int i = 0; i < s.size(); i++) {
        if(s[i] == '(') stack.push_back(0);
        else {
          if(stack.size() > 1) {
            currVal = stack.back() + 1;
            stack.pop_back();
            currVal += stack[stack.size()-1];
            stack[stack.size()-1] = currVal;
            if(currVal > maxNow) maxNow = currVal;
          } else if(stack.size() == 1) {
            // Record current max value
            if(stack[0] > maxNow) maxNow = stack[0];

            // Reset virtual head as previous parens have been cut off
            stack[0] = 0;
          }
        }
      }

      return 2*maxNow;
    }
};

int main() {
  Solution s;
  vector<string> input = {"())", "())()()", "(()))", ")(())", "(()((()", ")()()()((", "(", ""};
  for(string str: input) {
    cout << str << ": " << s.longestValidParentheses(str) << endl;
  }
}
