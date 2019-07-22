#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // Rotate each number in the upper-left quadrant four times
    // O(N)
    // If the size is odd, the middle cross only need to rotate once,
    // so subtract one when going through the rows
    // . 1 .
    // 2 3 4
    // . 5 .
    void rotateMy(vector<vector<int>>& matrix) {
      int nextI, nextJ;
      int i, j;
      int temp, prev;
      int squareSize = (matrix.size()+1)/2;
      int size = matrix.size()-1;

      // If odd, the middle cross only need to be rotated once
      char odd = matrix.size() % 2;
      for(i = 0; i < (odd? squareSize-1: squareSize); i++) {
        for(j = 0; j < squareSize; j++) {
          nextI = i; nextJ = j;
          prev = matrix[i][j];

          do {
            temp = nextI; nextI = nextJ; nextJ = size-temp;
            temp = matrix[nextI][nextJ];
            matrix[nextI][nextJ] = prev;
            prev = temp;
          } while(nextI != i || nextJ != j);
        }
      }
    }

    // Discuss section solution
    // https://leetcode.com/problems/rotate-image/discuss/19002/4ms-few-lines-C%2B%2B-code-Rotate-Image-90-degree-for-O(1)-space
    void rotate(vector<vector<int>>& matrix) {
      int n = matrix.size();
      int a = 0;
      int b = n-1;
      while(a<b){
        for(int i=0;i<(b-a);++i){
          cout << "Swap: " << a << "," << (a+i) << "<->" << (a+i) << "," << b << "->";
          swap(matrix[a][a+i], matrix[a+i][b]);
          cout << a << "," << (a+i) << "<->" << b << "," << (b-i) << "->";
          swap(matrix[a][a+i], matrix[b][b-i]);
          cout << a << "," << (a+i) << "<->" << (b-i) << "," << a << endl;
          swap(matrix[a][a+i], matrix[b-i][a]);
        }
        ++a;
        --b;
      }
    }
};

int main() {
  Solution s;

  vector<vector<int>> image;
  for(int i = 0; i < 4; i++) {
    vector<int> list = {1,2,3,4};
    image.push_back(list);
  }

  s.rotate(image);
  for(vector<int> v: image) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
