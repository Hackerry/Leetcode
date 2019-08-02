#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<vector<int>> generateMatrix(int n) {
      vector<vector<int>> result(n,vector<int>(n,0));
      if(n == 0) return result;

      int counter = 1;
      int i1 = 0, j1 = 0;
      int i2 = n-1, j2 = n-1;
      while(i1 <= i2 && j1 <= j2) {
        for(int j = j1; j <= j2; j++) result[i1][j] = counter++;
        for(int i = i1+1; i <= i2; i++) result[i][j2] = counter++;

        if(i1 < i2 && j1 < j2) {
          for(int j = j2-1; j >= j1; j--) result[i2][j] = counter++;
          for(int i = i2-1; i > i1; i--) result[i][j1] = counter++;
        }

        i1++;
        i2--;
        j1++;
        j2--;
      }

      return result;
    }
};

int main() {
  Solution s;
  int input = 2;

  for(vector<int>& v: s.generateMatrix(input)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
