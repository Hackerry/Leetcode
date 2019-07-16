#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  private:
    int n1Idx, n2Idx;

  public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      return normalON(nums1, nums2);
    }

    double logRuntime() {
      
    }

    // O(N) = N/2
    double normalON(vector<int>& nums1, vector<int>& nums2) {
      int odd = (nums1.size()+nums2.size())%2;
      int midIdx = (nums1.size()+nums2.size())/2 + (odd?0: -1);
      n1Idx = 0;
      n2Idx = 0;

      while(midIdx-- > 0) next(nums1, nums2);

      // We've found the midian
      if(odd) return next(nums1, nums2);
      else return (next(nums1, nums2) + next(nums1,nums2))/2.0;
    }

    // Helper to find the next number in the sorted sequence
    int next(vector<int>& nums1, vector<int>& nums2) {
      if(n1Idx < nums1.size() && n2Idx < nums2.size()) {
        if(nums1[n1Idx] < nums2[n2Idx]) return nums1[n1Idx++];
        else return nums2[n2Idx++];
      } else if(n1Idx < nums1.size()) {
        return nums1[n1Idx++];
      } else if(n2Idx < nums2.size()) {
        return nums2[n2Idx++];
      } else {
        // Error fetching the next element
        return std::numeric_limits<int>::max();
      }
    }
};

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  Solution s;
  vector<int> input1 = {1,2,3,14,15};
  vector<int> input2 = {7,8,9,10,11,12};

  vector<int> sorted(input1.size()+input2.size());
  merge(input1.begin(), input1.end(), input2.begin(), input2.end(), sorted.begin());
  for(int i: sorted) cout << i << " ";
  cout << endl;
  cout << "Median: " << s.normalON(input1, input2) << endl;

  // Odd number
  if(sorted.size()%2) cout << "Expected: " << sorted[sorted.size()/2] << endl;
  else cout << "Expected: " << (sorted[sorted.size()/2-1] + sorted[sorted.size()/2])/2.0 << endl;
}
