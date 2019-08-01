#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Kinda like solution but using space O(1)
    // O(NlogN)
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
      if(intervals.size() <= 1) return intervals;

      vector<vector<int>> result;
      sort(intervals.begin(), intervals.end(), Comparator());

      int start = intervals[0][0];
      int end = intervals[0][1];
      for(int i = 1; i < intervals.size(); i++) {
        // These two lists overlap
        if(intervals[i][0] <= end) {
          // Expand the lower bound
          if(intervals[i][0] < start) start = intervals[i][0];
          // Expand the higher bound
          if(intervals[i][1] > end) end = intervals[i][1];
        }
        // Two lists dose not overlap
        else {
          vector<int> newList = {start, end};
          result.push_back(newList);
          start = intervals[i][0];
          end = intervals[i][1];
        }
      }

      // Add the last element
      vector<int> newList = {start, end};
      result.push_back(newList);

      return result;
    }

    struct Comparator {
      bool operator()(vector<int>& v1, vector<int>& v2) {
        return v1[0] < v2[0];
      }
    };
};

int main() {
  Solution s;

  vector<int> v1 = {1,3};
  vector<int> v2 = {2,6};
  vector<int> v3 = {8,10};
  vector<int> v4 = {15,18};
  vector<int> v5 = {1,4};
  vector<int> v6 = {0,0};

  vector<vector<int>> list = {v5,v6};

  for(vector<int>&v: s.merge(list)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
