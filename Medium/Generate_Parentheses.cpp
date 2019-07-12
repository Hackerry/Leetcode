#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Solution {
  public:
    vector<string> generateParenthesis(int n) {
      vector<string> result;
      queue<string> tempList;
      queue<unsigned int> numOfLParens;
      unsigned int strLen = n*2;

      if(n == 0) return result;

      // Start the search by putting left a parenthese
      tempList.push("(");
      numOfLParens.push(1);

      string currStr;
      unsigned int currNum;
      while(!tempList.empty()) {
        currStr = tempList.front();
        tempList.pop();
        currNum = numOfLParens.front();
        numOfLParens.pop();

        // Use up all left parens
        if(currNum == n) {
          for(int i = currStr.size(); i < strLen; i++) {
            currStr += ")";
          }
          result.push_back(currStr);
        } else {
          // Open a new pair of parens
          tempList.push(currStr+"(");
          numOfLParens.push(currNum+1);

          // If not all left parens are closed yet, close one layer
          if(currStr.size() < currNum*2) {
            tempList.push(currStr+")");
            numOfLParens.push(currNum);
          }
        }
      }

      return result;
    }
};

int main() {
  Solution s;

  for(int i = 0; i < 5; i++) {
    vector<string> ss = s.generateParenthesis(i);

    cout << i << ": ";
    for(string str: ss) {
      cout << str << " ";
    }
    cout << endl;
  }
}
