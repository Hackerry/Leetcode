#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Solution {
  public:
    string intToRoman(int num) {
      const char M = 'M';         // 1000
      const char D = 'D';         // 500
      const char C = 'C';         // 100
      const char L = 'L';         // 50
      const char X = 'X';         // 10
      const char V = 'V';         // 5
      const char I = 'I';         // 1

      string result = "";
      while(num >= 1000) {
        result += M;
        num -= 1000;
      }

      if(num >= 900) {
        result += C;
        result += M;
        num -= 900;
      }

      while(num >= 500) {
        result += D;
        num -= 500;
      }

      if(num >= 400) {
        result += C;
        result += D;
        num -= 400;
      }

      while(num >= 100) {
        result += C;
        num -= 100;
      }

      if(num >= 90) {
        result += X;
        result += C;
        num -= 90;
      }

      while(num >= 50) {
        result += L;
        num -= 50;
      }

      if(num >= 40) {
        result += X;
        result += L;
        num -= 40;
      }

      while(num >= 10) {
        result += X;
        num -= 10;
      }

      if(num >= 9) {
        result += I;
        result += X;
        num -= 9;
      }

      while(num >= 5) {
        result += V;
        num -= 5;
      }

      if(num >= 4) {
        result += I;
        result += V;
        num -= 4;
      }

      while(num >= 1) {
        result += I;
        num -= 1;
      }

      return result;
    }
};

int main() {
  Solution s;
  srand(time(NULL));

  int random;
  for(int i = 0; i < 100; i++) {
    random = rand() % 3998 + 1;

    cout << random << ": " << s.intToRoman(random) << endl;
  }
}
