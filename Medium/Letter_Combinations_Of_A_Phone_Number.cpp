#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<string> letterCombinations(string digits) {
      const string LETTERS[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

      vector<string> result;
      if(digits == "") return result;
      bool firstRound = true;
      int startIndex = 0;
      int endIndex = 0;
      for(char c: digits) {
        // Setting boundary between string from previous round and this round
        startIndex = endIndex;
        endIndex = result.size();
        for(char l: LETTERS[c-'2']) {
          // If this is the first letter, insert each letter as a new string
          if(firstRound) {
            string newString = "";
            newString += l;
            result.push_back(newString);
          } else {
            // For each string in the previous round, add the new letter
            for(int i = startIndex; i < endIndex; i++) {
              string newString = result[i] + l;
              result.push_back(newString);
            }
          }
        }

        // Toggle first round
        if(firstRound) firstRound = false;
      }

      return vector<string>(result.cbegin()+endIndex, result.cend());
    }
};

int main() {
  Solution solution;

  string inputs[] = {"23", "45", "376", "288", "629", "657"};
  for(string s: inputs) {
    cout << s << ": ";
    for(string t: solution.letterCombinations(s)) {
      cout << t << " ";
    }
    cout << endl;
  }
}
