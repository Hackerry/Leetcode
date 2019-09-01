#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Only needs to store two number and test do they always exsist across
    // the line
    int minDominoRotations(vector<int>& A, vector<int>& B) {
      int one = A[0];
      int two = B[0];
      int topA, topB, botA, botB;
      topA = topB = botA = botB = 0;
      int N = A.size();

      if(one == two) {
        two = 0;
        botA++;
      } else {
        botB++;
      }
      topA++;

      for(int i = 1; i < N; i++) {
        if(A[i] == one) topA++;
        if(B[i] == one) botA++;
        if(A[i] != one && B[i] != one) one = 0;

        if(A[i] == two) topB++;
        if(B[i] == two) botB++;
        if(A[i] != two && B[i] != two) two = 0;

        if(one == 0 && two == 0) return -1;
      }

      return min(one == 0? N+1:min(N-topA, N-botA), two == 0? N+1:min(N-topB, N-botB));
    }
};

int main() {
  Solution s;
  vector<int> A = {3,3,1,1,2,2};
  vector<int> B = {3,2,3,2,2,2};
  cout << s.minDominoRotations(A, B) << endl;
}
