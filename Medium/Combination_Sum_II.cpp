#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
  public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
      return recursiveSolution(candidates, target);
    }

    // Recursive with a worst case runtime of O(N^2)
    vector<vector<int>> recursiveSolution(vector<int>& candidates, int target) {
      vector<vector<int>> result;
      if(candidates.size() == 0) return result;

      sort(candidates.begin(), candidates.end());

      return recursiveHelper(candidates, 0, target);
    }

    // Simply copy and paste, with the slight change of i+1 in sub calls
    vector<vector<int>> recursiveHelper(vector<int>& candidates, int start, int target) {
      vector<vector<int>> result;
      int prev = -1;
      for(int i = start; i < candidates.size(); i++) {
        // Avoid duplicates
        if(candidates[i] == prev) continue;
        else prev = candidates[i];

        if(target == candidates[i]) {
          vector<int> newList = {candidates[i]};
          result.push_back(newList);
          break; // Array is sorted, everything following will be bigger
        } else if(target > candidates[i]) {
          vector<vector<int>> returnList = recursiveHelper(candidates, i+1, target-candidates[i]);
          if(!returnList.empty()) {
            for(vector<int>& v: returnList) {
              v.push_back(candidates[i]);
              result.push_back(v);
            }
          }
        } else break; // Array is sorted
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> input = {2,5,2,1,2};
  int target = 5;

  for(vector<int> v: s.combinationSum(input, target)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
