#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    int maxArea(vector<int>& height) {
      return solution(height);
    }

    // O(n^2)
    int bruteForce(vector<int>& height) {
      int maxVal = 0;
      int tempVal;
      for(int i = 0; i < height.size(); i++) {
        for(int j = i+1; j < height.size(); j++) {
          tempVal = min(height[i], height[j])*(j-i);
          if(tempVal > maxVal) {
            maxVal = tempVal;
          }
        }
      }

      return maxVal;
    }

    // Smart search O(n)
    // 16ms the opposite of solution
    // Start from the longest two lines and search outwards(left of left line &
    // right of right line). If area is bigger that way, update area and move
    // the boundary outwards.
    int smartSearch(vector<int>& height) {
      // Find the tallest two and start searching
      int firstVal = 0, secondVal = 0;
      int firstIdx = -1, secondIdx = -1;
      for(int i = 0; i < height.size(); i++) {
        if(height[i] > firstVal) {
          secondVal = firstVal;
          secondIdx = firstIdx;
          firstVal = height[i];
          firstIdx = i;
        } else if(height[i] > secondVal) {
          secondVal = height[i];
          secondIdx = i;
        }
      }

      // Make firstVal the left value and secondVal the right value
      int tempVal;
      if(firstIdx > secondIdx) {
        tempVal = firstVal;
        firstVal = secondVal;
        secondVal = tempVal;
        tempVal = firstIdx;
        firstIdx = secondIdx;
        secondIdx = tempVal;
      }

      // Find possible improvements
      int maxAmount = min(firstVal, secondVal)*(secondIdx-firstIdx);
      char improved = true;
      int improveIdx;
      while(improved) {
        improved = false;
        for(int i = 0; i < firstIdx; i++) {
          tempVal = min(height[i], secondVal)*(secondIdx-i);
          if(tempVal > maxAmount) {
            maxAmount = tempVal;
            improveIdx = i;
            improved = true;
          }
        }
        
        for(int i = secondIdx+1; i < height.size(); i++) {
          tempVal = min(firstVal, height[i])*(i-firstIdx);
          if(tempVal > maxAmount) {
            maxAmount = tempVal;
            improveIdx = i;
            improved = true;
          }
        }

        if(improved) {
          if(improveIdx < firstIdx) {
            firstIdx = improveIdx;
            firstVal = height[firstIdx];
          } else {
            secondIdx = improveIdx;
            secondVal = height[secondIdx];
          }
        }
      }

      return min(firstVal, secondVal)*(secondIdx-firstIdx);
    }

    int solution(vector<int>& height) {
      int maxArea = 0;
      int leftIdx = 0;
      int rightIdx = height.size()-1;

      while(leftIdx < rightIdx) {
        maxArea = max(maxArea, min(height[leftIdx], height[rightIdx])*(rightIdx-leftIdx));

        if(height[leftIdx] < height[rightIdx]) leftIdx++;
        else rightIdx--;
      }

      return maxArea;
    }
};

int main() {
  Solution s;
  vector<int> input = {/*1,8,6,2,5,4,8,3,71,2,4,3*/5,2,12,1,5,3,4,11,9,4};

  cout << s.maxArea(input) << endl;
}
