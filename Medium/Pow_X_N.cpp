#include <iostream>
#include <vector>
#include <limits>
#include <math.h>

using namespace std;

class Solution {
  public:
    // My solution - similar to divide by 2 but store the results along the way
    double myPow(double x, int n) {
      // Edge case, n = 0
      if(n == 0) return 1;

      char reverse = (n < 0);
      double result = x;
      int currPower = (n < 0? -1: 1);
      vector<double> scratch;
      vector<int> powers;           // I can't use pow(2,n) because I'm writing one!

      scratch.push_back(result);
      powers.push_back(currPower);

      while(currPower != n) {
        if((reverse && currPower < n/2) || (!reverse && currPower > n/2)) {
          int nextPowerIdx = (int)floor(log2(abs(n-currPower)));
          result *= scratch[nextPowerIdx];
          currPower += powers[nextPowerIdx];
        } else {
          result *= result;
          currPower *= 2;
          scratch.push_back(result);
          powers.push_back(currPower);
        }
      }

      return reverse? (1/result): result;
    }

    // https://leetcode.com/problems/powx-n/discuss/19563/Iterative-Log(N)-solution-with-Clear-Explanation
    double myPowOP(double x, int n) {
      double result = 1;
      unsigned int absN = (unsigned int)abs((double)n);

      while(absN != 0) {
        if((absN & 1) == 1) result *= x;
        absN >>= 1;
        x *= x;
      }

      return (n < 0? 1/result: result);
    }

    // https://leetcode.com/problems/powx-n/discuss/19546/Short-and-easy-to-understand-solution
    // Problem with INTEGER.min(), because casting n to positive result in overflow.
    double myPowGoodTry(double x, int n) {
      if(n == 0)
        return 1;
      if(n<0){
        n = -n;
        x = 1/x;
      }
      return (n%2 == 0) ? pow(x*x, n/2) : x*pow(x*x, n/2);
    }
};

int main() {
  Solution s;
  vector<double> bases = {0,1,-4,-2,99.9,-99,9,10,10,10,10,34.00515};
  vector<int> powers = {10,10,10,-2,numeric_limits<int>::max(),numeric_limits<int>::min(),0,3,-2,19,20,-3};

  for(int i = 0; i < min(bases.size(), powers.size()); i++) {
    cout << bases[i] << "^" << powers[i] << " = " << s.myPow(bases[i], powers[i]) << " - " << pow(bases[i], powers[i]) << endl;
  }
}
