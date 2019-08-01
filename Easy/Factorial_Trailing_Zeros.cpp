#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // The only thing that result in a 0 is 2*5?
    // Two is the only even prime
    int trailingZeroesSlow(int n) {
      int numTwos = 0;
      int numFives = 0;
      int temp;

      for(int i = 1; i <= n; i++) {
        temp = i;
        while(temp % 2 == 0) {
          numTwos++;
          temp /= 2;
        }

        while(temp % 5 == 0) {
          numFives++;
          temp /= 5;
        }
      }

      return min(numTwos, numFives);
    }

    // Better version
    // Observe the limiting factor is 5.
    // For every multiple of five, there are enough 2s for it
    // So only need to find 5s.
    // Careful of 25,50,125 (5*5, 10*5, 15*5, 20*5)
    int trailingZeroes(int n) {
      int count = 0;

      while(n >= 5) count += (n/=5);

      return count;
    }
};

int main() {
  Solution s;

  int input = 0;
  while(true) {
    cout << "Input: ";
    cin >> input;
    if(input == -1) break;
    cout << input << "! has " << s.trailingZeroes(input) << " 0s." << endl;
  }
}
