#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
  public:
    int myAtoi(string str) {
      if(str.size() == 0) return 0;

      //Eliminate leading whitespaces
      int index = 0;
      while(index < str.size()) {
        if(str[index] != ' ') break;
        index++;
      }

      // All whitespaces
      if(index == str.size()) return 0;

      // Deal with sign
      char positive = true;
      if(str[index] == '+') index++;
      else if(str[index] == '-') {
        positive = false;
        index++;
      }

      char nextVal;
      int result = 0;
      int max = numeric_limits<int>::max();
      int min = numeric_limits<int>::min();
      while(index < str.size()) {
        nextVal = str[index]-'0';
        // It's a valid digit
        if(nextVal <= 9 && nextVal >= 0) {
          if(positive) {
            // Positive overflow
            if(max / 10 < result || (max / 10 == result && nextVal > max % 10))
              return numeric_limits<int>::max();
            result *= 10;
            result += nextVal;
          } else {
            // Negative overflow
            if(min / 10 > result || (min / 10 == result && nextVal > -(min % 10)))
              return numeric_limits<int>::min();
            result *= 10;
            result -= nextVal;
          }
          
          index++;
        } else return result;
      }

      return result;
    }
};

int main() {
  /*cout << "Max: " << numeric_limits<int>::max() << endl;
  cout << "Max+1: " << (numeric_limits<int>::max()+1) << endl;
  cout << "Min: " << numeric_limits<int>::min() << endl;
  cout << "Min-1: " << (numeric_limits<int>::min()-1) << endl;*/

  Solution s;
  string test[] = {"123", "+34", "99999999999999", "9j", "-30z", "-109", "-9999999999999999999999", "       ", "    123   ", "   99hj  ", "", "asd", "0123", "-2147483647"};

  for(int i = 0; i < 14; i++) {
    cout << "\"" << test[i] << "\": " << s.myAtoi(test[i]) << endl;
  }
}
