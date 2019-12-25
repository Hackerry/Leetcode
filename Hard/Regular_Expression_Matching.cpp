#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

class Solution {
  public:
    // 8ms 66.34%-74.58% Wow!
    bool isMatch(string s, string p) {
      int P = p.length();
      int S = s.length();

      // Edge case, pattern is empty
      if(P == 0) {
        if(S == 0) return true;
        else return false;
      }

      // Process pattern for matching
      vector<char> nodes;
      vector<bool> optional;
      nodes.push_back(p[0]);
      bool lastOptional = false;
      for(int i = 1; i < P; i++) {
        if(p[i] != '*') {
          nodes.push_back(p[i]);
          if(!lastOptional) optional.push_back(false);
          lastOptional = false;
        }
        else {
          optional.push_back(true);
          lastOptional = true;
        }
      }
      if(!lastOptional) optional.push_back(lastOptional);

      // Match string and pattern
      int N = nodes.size()+1;
      queue<int> indices;
      vector<bool> simulateIndex(N, 0);

      // Edge case, string is empty
      if(S == 0) {
        for(bool b: optional) {
          if(!b) return false;
        }
        return true;
      }

      indices.push(0);
      indices.push(-1);

      int nextIndex;
      int length = 0;
      while(!indices.empty()) {
        nextIndex = indices.front();
        indices.pop();

        // Simulate on next character input
        if(nextIndex == -1) {
          // Done reading input
          if(++length >= S) return simulateIndex[N-1];

          // Push all nodes to be simulated next
          for(int i = 0; i < N-1; i++) {
            if(simulateIndex[i]) indices.push(i); 
          }
          // Mark current length
          if(!indices.empty()) indices.push(-1);

          // Record the next round of nodes to be simulated
          for(int i = 0; i < N; i++) simulateIndex[i] = false;
        } else if(nextIndex < N-1) {
          char input = s[length];
          bool matching = false;
          while(nextIndex < N-1) {
            if(optional[nextIndex]) {
              // Matching input and pattern, stay at * or test next character
              if(input == nodes[nextIndex] || nodes[nextIndex] == '.') {
                simulateIndex[nextIndex] = true;
                matching = true;
              }

              // This character is optional, move on to test the next character
              nextIndex++;

              // If input matches some character before, this is a valid start point
              if(matching) simulateIndex[nextIndex] = true;
            } else {
              if(input == nodes[nextIndex] || nodes[nextIndex] == '.') {
                simulateIndex[++nextIndex] = true;

                // Next character can be optional
                while(nextIndex < N-1) {
                  if(optional[nextIndex]) simulateIndex[++nextIndex] = true;
                  else break;
                }
              }
              break;
            }
          }
        }
      }
      return length == S;
    }
};

int main() {
  Solution s;
  // vector<string> patterns = {"c*ab", "**ab", ".*ab", "a*b*c*", "a*bc...", ".*", "..", "**.*", "b*a*"};
  // vector<string> patterns = {"", ".", ".*", "a*"};
  // vector<string> patterns = {"a*b*c*"};
  string ori = "a";
  /*for(string str: patterns) {
    cout << str << " - " << ori << ": " << s.isMatch(ori, str) << endl;
  }*/

  string input = "a";
  do {
    cout << input << " - " << ori << ": " << s.isMatch(ori, input) << endl;
    cout << "====" << endl;

    cin >> input;
    cin >> ori;
  } while(input.compare("q") != 0);
}
