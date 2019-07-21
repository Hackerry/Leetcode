#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Solution {
  private: 
    const char ZERO = '0';

  public:
    // https://leetcode.com/problems/multiply-strings/discuss/17646/Brief-C%2B%2B-solution-using-only-strings-and-without-reversal
    string multiply(string num1, string num2) {
      // Critical observation 1: product of two numbers can only have as many digits as the sum of the number of digits of these two numbers
      // You can never carry a 10
      string result(num1.size()+num2.size(), '0');

      int carry, sum;
      for(int i = num1.size()-1; i >= 0; i--) {
        carry = 0;
        for(int j = num2.size()-1; j >= 0; j--) {
          sum = carry + (num1[i]-ZERO) * (num2[j]-ZERO) + (result[i+j+1]-ZERO);
          result[i+j+1] = sum%10 + ZERO;
          carry = sum/10;
        }

        result[i] += carry;
      }

      size_t index = result.find_first_not_of('0');
      if(index != string::npos) return result.substr(index);
      
      return "0";
    }

    string slowMultiply(string num1, string num2) {
      string longNum = num1.size() < num2.size()? num2: num1;
      string shortNum = num1.size() < num2.size()? num1: num2;

      reverse(longNum.begin(), longNum.end());

      string result = "0";
      for(int i = shortNum.size()-1; i >= 0; i--) {
        if(shortNum[i] == ZERO) continue;
        else if(shortNum[i] == ZERO+1) {
          result = simpleAdd(result, longNum, shortNum.size()-1-i);
        } else {
          string mult = simpleMult(longNum, shortNum[i]);
          result = simpleAdd(result, mult, shortNum.size()-1-i);
        }
      }

      reverse(result.begin(), result.end());

      return result;
    }

    string simpleAdd(string baseNum, string offsetNum, int offset) {
      int i;
      int carry = 0;
      int sum;

      // Three cases need to be considered
      // Case 1: two numbers don't overlap
      // Case 2: overlap and baseNum is longer
      // Case 3: overlap and offsetNum is longer

      for(i = 0; i < min(offset, (int)baseNum.size()); i++);

      // Case 1: two numbers don't overlap
      if(i == baseNum.size()) {
        for(; i < offset; i++) baseNum += ZERO;
        baseNum += offsetNum;
      }
      // Case 2&3: overlap
      else {
        for(; i < min(baseNum.size(), offset+offsetNum.size()); i++) {
          sum = (baseNum[i]-ZERO) + (offsetNum[i-offset]-ZERO) + carry;
          baseNum[i] = sum%10 + ZERO;
          carry = sum/10;
        }

        // Case 2: baseNum is longer, deal with potential carry
        if(i < baseNum.size()) {
          for(; i < baseNum.size(); i++) {
            if(carry == 0) return baseNum;

            sum = baseNum[i]-ZERO + carry;
            baseNum[i] = sum%10 + ZERO;
            carry = sum/10;
          }
        }
        // Case 3: offsetNum is longer, copy over all the digits
        else {
          for(; i < offsetNum.size()+offset; i++)  {
            if(carry == 0) baseNum += offsetNum[i-offset];
            else {
              sum = offsetNum[i-offset]-ZERO + carry;
              baseNum += sum%10 + ZERO;
              carry = sum/10;
            }
          }
        }

        if(carry != 0) baseNum += (carry + ZERO);
      }

      return baseNum;
    }

    // Return multiplication of a single digit
    // Input must be in reverse order
    string simpleMult(string num, char c) {
      int multiNum = c-ZERO;
      int product = 0;
      int carry = 0;

      string result = "";
      for(int i = 0; i < num.size(); i++) {
        product = (num[i]-ZERO)*multiNum + carry;
        result += (product % 10) + ZERO;
        carry = product / 10;
      }

      if(carry != 0) result += (carry + ZERO);

      return result;
    }
};

int main() {
  Solution s;

  srand(time(NULL));

  int a, b;
  string c;
  int pass = 0;
  int all = 20;
  for(int i = 0; i < all; i++) {
    a = rand() % 10000;
    b = rand() % 10000;

    c = s.multiply(to_string(b), to_string(a));

    cout << a << "*" << b << " = " << c << "-" << (a*b) << " ";
    if(stoi(c) == a*b) {
      cout << "PASS" << endl;
      pass++;
    } else cout << "FAIL" << endl;
  }

  cout << "===============================" << endl;
  cout << "Pass: " << pass << " Fail: " << (all-pass) << endl;

  string d = "9123823489234123";
  string e = "12897289347189273123";
  cout << d << "*" << e << " = " << s.multiply(d, e) << endl;
}
