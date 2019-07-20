#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  private:
    int n1Idx, n2Idx;

  public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      return solution(nums1, nums2);
    }

    // https://www.youtube.com/watch?v=LPFhl65R7ww&feature=youtu.be
    // Binary search through the list and cut two lists into four parts.
    // When two parts on the left side is strictly less than or equal to the
    // right two parts, we've found the right partition.
    // Find the median based on this partition.
    double solution(vector<int>& nums1, vector<int>& nums2) {
      int iMin, iMax;
      int posA, posB;
      int sizeShort, sizeLong;

      vector<int>& longList = (nums1.size() > nums2.size()? nums1: nums2);
      vector<int>& shortList = (nums1.size() > nums2.size()? nums2: nums1);
      iMin = 0; iMax = shortList.size();
      sizeShort = shortList.size(); sizeLong = longList.size();

      while(iMin <= iMax) {
        posA = (iMin+iMax)/2;
        // Take into account odd#
        posB = (shortList.size()+longList.size()+1)/2-posA;

        if(posA > 0 && shortList[posA-1] > longList[posB]) iMax = posA-1;
        else if(posA < sizeShort && longList[posB-1] > shortList[posA]) iMin = posA+1;
        else {
          int maxLeft, minRight;
          if(posA == 0) maxLeft = longList[posB-1];
          else if(posB == 0) maxLeft = shortList[posA-1];
          else maxLeft = max(shortList[posA-1], longList[posB-1]);

          if((sizeShort + sizeLong) % 2) return maxLeft;

          if(posA == sizeShort) minRight = longList[posB];
          else if(posB == sizeLong) minRight = shortList[posA];
          else minRight = min(shortList[posA], longList[posB]);

          return (minRight + maxLeft) / 2.0;
        }
      }

      return -1;
    }

    double solutionCopy(vector<int>& nums1, vector<int>& nums2) {
      vector<int>& longList = (nums1.size() > nums2.size()? nums1: nums2);
      vector<int>& shortList = (nums1.size() > nums2.size()? nums2: nums1);
      int m, n;
      m = shortList.size();
      n = longList.size();

      int iMin = 0, iMax = m, halfLen = (m+n+1)/2;
      while(iMin <= iMax) {
        int i = (iMin + iMax) / 2;
        int j = halfLen - i;
        if (i < iMax && longList[j-1] > shortList[i]){
          iMin = i + 1; // i is too small
        }
        else if (i > iMin && shortList[i-1] > longList[j]) {
          iMax = i - 1; // i is too big
        }
        else { // i is perfect
          int maxLeft = 0;
          if (i == 0) { maxLeft = longList[j-1]; }
          else if (j == 0) { maxLeft = shortList[i-1]; }
          else { maxLeft = max(shortList[i-1], longList[j-1]); }
          if ( (m + n) % 2 == 1 ) { return maxLeft; }

          int minRight = 0;
          if (i == m) { minRight = longList[j]; }
          else if (j == n) { minRight = shortList[i]; }
          else { minRight = min(longList[j], shortList[i]); }

          return (maxLeft + minRight) / 2.0;
        }
      }
      return 0.0;
    }

    // Failed attempt
    // Additionally, after analyzing, it has a runtime of (log(log n))
    double failedAttempt(vector<int>& nums1, vector<int>& nums2) {
      vector<int>& longList = (nums1.size() > nums2.size()? nums1: nums2);
      vector<int>& shortList = (nums1.size() > nums2.size()? nums2: nums1);

      int startLong = 0;
      int endLong = longList.size()-1;
      int mid;

      int startShort = 0;
      int endShort = shortList.size()-1;
      int splitShortIdx;
      int diff;

      while(startLong <= endLong) {
        mid = (startLong+endLong)/2;

        splitShortIdx = findSplitPos(longList[mid], shortList, startShort, endShort);
        diff = 2*(splitShortIdx + mid) - longList.size() - shortList.size();
        cout << "Diff: " << diff << endl;

        // No other value to take when at end of list
        if(splitShortIdx == shortList.size()) {
          // Total inclusion of the short list
          if(diff == -1) return longList[mid];
          // It exsists in the first half some where
          // We need to pinpoint its position to get the average
          else if(diff == 0) {
            if(longList[mid-1] > shortList[splitShortIdx-1])
              return (longList[mid] + longList[mid-1])/2.0;
            else
              return (longList[mid] + shortList[splitShortIdx-1])/2.0;
          }
          // Need to find the larger value as split point eg:{1,3}{2}
          else if(diff == 1) {
            return longList[mid-1] > shortList[splitShortIdx-1]? longList[mid-1]: shortList[splitShortIdx-1];
          }
        }

        // Even number of intergers
        if(diff == 0) {
          return (longList[mid] + shortList[splitShortIdx]) / 2.0;
        }
        // Odd number of integers
        else if(diff == 1) {
          return longList[mid] > shortList[splitShortIdx]? longList[mid]: shortList[splitShortIdx];
        } else if(diff == -1) {
          return longList[mid] < shortList[splitShortIdx]? longList[mid]: shortList[splitShortIdx];
        }
        // Keep searching
        else if(diff < 0) {
          startShort = splitShortIdx;
          startLong = mid+1;
        } else if(diff > 0) {
          endShort = splitShortIdx;
          endLong = mid-1;
        }
      }

      // This value should never be returned
      return -1;
    }

    // Return the index of the smallest number that is larger than or equal to
    // the target number
    int findSplitPos(int target, vector<int>& nums, int start, int end) {
      int mid;
      while(start < end) {
        mid = (start+end)/2;

        if(nums[mid] == target) return mid;
        else if(nums[mid] < target) start = mid+1;
        else end = mid-1;
      }

      if(start == end && target > nums[start]) {
        cout << "Search " << target << " return: " << start+1 << endl;
        return start+1;
      }
      else if(end < 0) {
        cout << "Search " << target << " return: 0" << endl;
        return 0;
      }

      cout << "Search " << target << " return: " << end;
      return end;
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
  vector<int> input1 = {1,3,5,7,11};
  vector<int> input2 = {2};

  vector<int> sorted(input1.size()+input2.size());
  merge(input1.begin(), input1.end(), input2.begin(), input2.end(), sorted.begin());
  for(int i: sorted) cout << i << " ";
  cout << endl;
  cout << "Median: " << s.findMedianSortedArrays(input1, input2) << endl;

  // Odd number
  if(sorted.size()%2) cout << "Expected: " << sorted[sorted.size()/2] << endl;
  else cout << "Expected: " << (sorted[sorted.size()/2-1] + sorted[sorted.size()/2])/2.0 << endl;
}
