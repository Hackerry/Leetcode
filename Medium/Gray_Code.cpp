#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
  public:
    // Gray code property:
    // Reflect value and add 1 at the front
    vector<int> grayCode(int n) {
      vector<int> result;

      int pos = 0;
      int lastPos, temp;
      result.push_back(0);
      while(n > 0) {
        lastPos = result.size();
        temp = pow(2, pos++);

        for(int i = lastPos-1; i >= 0; i--)
          result.push_back(result[i] + temp);

        n--;
      }

      return result;
    }
};

int main() {
  Solution s;
  for(int i: s.grayCode(4)) cout << i << " ";
  cout << endl;
}
