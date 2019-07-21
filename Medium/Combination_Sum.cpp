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
          vector<vector<int>> returnList = recursiveHelper(candidates, i, target-candidates[i]);
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

    // O(NlogN) for sorting (Examples are misleading as the set may not be sorted
    // O(N^2) for searching
    vector<vector<int>> slowSum(vector<int>& candidates, int target) {
      vector<vector<int>> result;
      if(candidates.size() == 0) return result;

      // Sort the list first
      sort(candidates.begin(), candidates.end());

      queue<int> sumList;
      queue<vector<int>> resultList;
      sumList.push(0);
      resultList.push(vector<int>());

      int currSum;
      int nextSum;
      while(!sumList.empty()) {
        currSum = sumList.front();
        vector<int> currList(resultList.front());
        sumList.pop();
        resultList.pop();

        for(int i: candidates) {
          // Remove duplicates
          if(!currList.empty() && i < currList.back()) continue;

          nextSum = currSum + i;

          // Possible answer, keep it in the list
          if(nextSum < target) {
            vector<int> newList(currList);
            newList.push_back(i);
            resultList.push(newList);
            sumList.push(nextSum);
          }
          // We have found an answer
          else if(nextSum == target) {
            currList.push_back(i);
            result.push_back(currList);
          }
          // Otherwise it's invalid
        }
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> input = {2};
  int target = 24;

  for(vector<int> v: s.combinationSum(input, target)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }
}
