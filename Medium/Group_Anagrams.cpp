#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
      
    }

    vector<vector<string>> betterGroupAnagrams(vector<string>& strs) {
      const int NUM_ALBET = 26;

      vector<vector<string>> result;
      vector<string> patterns;
      string tempStr;

      for(string s: strs) {
        tempStr = s;
        // Sort the string for comparison
        sort(tempStr.begin(), tempStr.end());

        int i = 0, j =0;
        for(; i < patterns.size(); i++) {
          // If sizes are different, no way they are anagrams
          if(patterns[i].size() == tempStr.size()) {
            for(j = 0; j < patterns[i].size(); j++) {
              // Character is different
              if((tempStr[j] ^ patterns[i][j]) != 0) break;
            }

            // All characters are the same, add it to list
            if(j == patterns[i].size()) {
              result[i].push_back(s);
              break;
            }
          }
        }

        // This string does not match with any words
        if(i == patterns.size()) {
          patterns.push_back(tempStr);
          vector<string> newList = {s};
          result.push_back(newList);
        }
      }

      return result;
    }

    // Super slow solution (untested)
    // Time limit exceeds
    vector<vector<string>> slowGroupAnagrams(vector<string>& strs) {
      const int NUM_ALBET = 26;
      const char A = 'a';

      vector<vector<string>> result;
      vector<vector<int>> patterns;
      vector<int> currPattern(NUM_ALBET, 0);

      for(string s: strs) {
        // Reset pattern
        for(int& i: currPattern) i = 0;
        for(char c: s) currPattern[c-A]++;

        // Convert string to a pattern
        int i = 0;
        if(!patterns.empty()) {
          for(; i < patterns.size(); i++) {
            // This is an anagram of a word seen before
            if(patterns[i] == currPattern) {
              result[i].push_back(s);
              break;
            }
          }
        }

        // This is a new pattern or patterns is empty
        if(i == patterns.size()) {
          patterns.push_back(currPattern);
          vector<string> newWord = {s};
          result.push_back(newWord);
        }
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<string> input = {"eat", "tea", "tan", "ate", "nat", "bat", "eate", "gym", "any"};

  for(vector<string>& v: s.groupAnagrams(input)) {
    for(string ss: v) cout << ss << " ";
    cout << endl;
  }
}
