#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class Solution {
  public:
    // O(n)
    string convertOriginal(string s, int numRows) {
      if(numRows == 1) return s;

      unsigned int len = s.size();
      int arr[len];
      int num = 0;

      char increasing = true;
      for(unsigned int i = 0; i < len; i++) {
        if(increasing) arr[i] = num++;
        else arr[i] = num--;

        if(num == numRows) {
          increasing = false;
          num -= 2;
        }
        if(num == -1) {
          increasing = true;
          num += 2;
        }
      }

      vector<string> parts;
      for(int i = 0; i < numRows; i++) {
        parts.push_back("");
      }
      for(int i = 0; i < len; i++) {
        parts[arr[i]] += s[i];
      }

      string result = "";
      for(int i = 0; i < numRows; i++) {
        result += parts[i];
      }

      return result;
    }

    // O(n) with scaler of 1
    // Crucial observation:
    // Appear in row: 0 1 2 3 2 1 0 1 2 3 2 1 0 1 2 3...
    // Next index:    6 4 2 6 4 2 6 4 2 6 4 2 6 4 2 6...
    string convert(string s, int numRows) {
      if(numRows == 1) return s;

      string result = "";

      int index;
      for(int i = 0; i < numRows; i++) {
        index = i;
        while(index < s.size()) {
          result += s[index];
          index += (numRows-1-index%(numRows-1))*2;
        }
      }

      return result;
    }
};

int main() {
  string str = "PAYPALISHIRING";
  int numRows = 4;

  Solution s;
  cout << s.convert(str, numRows) << endl;
}
