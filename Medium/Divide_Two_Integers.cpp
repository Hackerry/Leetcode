#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
  public:
    int divide(int dividend, int divisor) {
      return bitSolutionNew(dividend, divisor);
    }

    int naiveSolution(int dividend, int divisor) {
      if(dividend == 0) return 0;
      else if(divisor == 1) return dividend;
      else if(divisor == -1) {
        if(dividend == std::numeric_limits<int>::min()) return std::numeric_limits<int>::max();
        else return -dividend;
      }

      int quotient = 0;
      if((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) {
        if(dividend > 0) {
          while(dividend != 0 && dividend >= -divisor) {
            dividend += divisor;
            quotient--;
          }
        } else {
          while(dividend != 0 && dividend <= -divisor) {
            dividend += divisor;
            quotient--;
          }
        }
      } else {
        if(dividend > 0) {
          while(dividend != 0 && dividend >= divisor) {
            dividend -= divisor;
            if(quotient != std::numeric_limits<int>::max()) quotient++;
            else return std::numeric_limits<int>::max();
          }
        } else {
          while(dividend != 0 && dividend <= divisor) {
            dividend -= divisor;
            if(quotient != std::numeric_limits<int>::max()) quotient++;
            else return std::numeric_limits<int>::max();
          }
        }
      }

      return quotient;
    }

    int bitSolutionNew(int dividend, int divisor) {
      const int COUNT = 32;

      unsigned int posDividend = dividend < 0? -(unsigned)dividend: dividend;
      unsigned int posDivisor = divisor < 0? -(unsigned)divisor: divisor;
      unsigned int tempDivisor;
      unsigned int quotient = 0;
      unsigned int currQuotient;
      int index;

      char pos = true;
      if((dividend < 0) ^ (divisor < 0 == 1)) pos = false;

      if(posDividend < posDivisor) return 0;
      else if(posDividend == posDivisor) return pos? 1: -1;

      while((posDividend > 0) && (posDividend >= posDivisor)) {
        tempDivisor = posDivisor;
        currQuotient = 1;
        index = 0;
        // cout << posDividend << " " << tempDivisor << endl;
        // cout << tempDivisor << endl;

        while(index++ < COUNT && (tempDivisor << 1) < posDividend) {
          // cout << tempDivisor << " " << posDividend << " " << index << endl;
          tempDivisor <<= 1;
          currQuotient <<= 1;
        }

        quotient += currQuotient;
        posDividend -= tempDivisor;
      }

      // Overflow for positive integers
      if(quotient >= (unsigned)std::numeric_limits<int>::max()+1 && pos)
        return std::numeric_limits<int>::max();
      else
        return pos? quotient: -quotient;
    }

    int bitSolution(int dividend, int divisor) {
      if(dividend == std::numeric_limits<int>::min() && divisor == -1)
        return std::numeric_limits<int>::max();
      else if(dividend == std::numeric_limits<int>::min() && divisor == 1)
        return std::numeric_limits<int>::max();

      char pos = true;
      if(dividend > 0 ^ divisor > 0 == 1) pos = false;

      unsigned int posDivisor = divisor < 0? -(unsigned)divisor: divisor;
      unsigned int posDividend = dividend < 0? -(unsigned)dividend: dividend;
      unsigned int tempDivisor;
      int quotient = 0;
      int tempQuotient;

      // cout << posDivisor << " " << posDividend << endl;
      if(posDivisor > posDividend) return 0;

      while(posDividend >= posDivisor) {
        tempQuotient = 1;
        tempDivisor = posDivisor;

        while(posDividend > (tempDivisor << 1)) {
          tempDivisor <<= 1;
          tempQuotient <<= 1;
          cout << "td: " << tempDivisor << endl;
        }

        quotient += tempQuotient;
        posDividend -= tempDivisor;
        cout << "q: " << quotient << endl;
      }

      return pos? quotient: -quotient;
    }
};

int main() {
  Solution s;

  vector<int> dividend = {4,2,10,5,234,123,-2147483648,1,7,-6,100,-2147483648, -2147483648, -2147483648,2147483647};
  vector<int> divisor = {2,4,9,1,15,34,-1,-1,-3,-2,-5,2,-2147483648, 2147483647,2147483647};

  /*cout << std::numeric_limits<int>::max() << endl;
    cout << std::numeric_limits<int>::min() << endl;
    cout << (-2147483648 < 0) << endl;*/
  int min = std::numeric_limits<int>::min();
  unsigned int test = -(unsigned)min;
  cout << test << endl;

  setvbuf(stdout, NULL, _IONBF, 0);
  for(int i = 0; i < dividend.size(); i++) {
    cout << dividend[i] << "/" << divisor[i] << "=" << s.divide(dividend[i], divisor[i]) << endl;
  }
}
