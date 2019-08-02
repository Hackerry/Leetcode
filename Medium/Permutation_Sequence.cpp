#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

class Solution {
  public:
    // Hooray! Original solution
    // Can use iota(http://www.cplusplus.com/reference/numeric/iota/) for
    // initializing digits array.
    string getPermutation(int n, int k) {
      const char ONE = '1';
      vector<char> digits(n, 0);

      string result = "";
      int index;
      int factorial = 1;
      for(int i = 2; i < n; i++) factorial *= i;
      // Counting start at 1
      k--;

      while(n > 0) {
        index = k/factorial;
        for(int i = 0; i < digits.size(); i++) {
          if(!digits[i]) {
            if(index == 0) {
              result += (i+ONE);
              digits[i] = 1;
              break;
            } else index--;
          }
        }

        k %= factorial;
        if(--n) factorial /= n;
      }

      return result;
    }
};

int main() {
  Solution s;

  int n = 2;
  int k = 2;
  cout << "n-" << n << " k-" << k << ": " << s.getPermutation(n, k) << endl;
}
