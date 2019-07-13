#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
  public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      return elegantSolution(nums);
    }

    // O(N^2) -- No sort, but seems slow
    // Keep record of each distinct number and its # of copies
    // When the third number doesn't appear in the list or its copy # is smaller
    // than 0, the target number is not found.
    vector<vector<int>> bruteForce(vector<int>& nums) {
      vector<vector<int>> result;
      if(nums.size() < 3) return result;

      unordered_map<int, int> numList;
      for(int i: nums) {
        if(numList.find(i) != numList.end()) numList[i]++;
        else numList.insert({i, 1});
      }

      auto a = numList.begin();
      // Initialize type(doesn't mean anything)
      auto b = a;
      int toFind;
      auto c = a;
      while(a != numList.end()) {
        b = a;
        // Mark one copy of the number as used
        a->second--;

        while(b != numList.end()) {
          // Mark one copy of the number as used if such one exsists
          if(b->second > 0) b->second--;
          else {
            b++;
            continue;
          }

          toFind = -(a->first + b->first);
          if((c = numList.find(toFind)) != numList.end() && c->second > 0) {
            vector<int> newList;
            newList.push_back(a->first);
            newList.push_back(b->first);
            newList.push_back(toFind);
            result.push_back(newList);
          }

          // First restore copy
          b->second++;
          // Temporarily erase all copy to avoid duplicates
          b->second *= -1;
          b++;
        }

        // Restore all copy
        b = a;
        while(++b != numList.end()) b->second *= -1;

        // Erase all copy, this number can't be used again
        a->second = 0;
        a++;
      }

      return result;
    }


    // O(N^2) -- Still seems slow. Probably because of binary search.
    // Sort list first. For each num smaller than/equal to 0, find two other
    // number that makes the sum 0.
    vector<vector<int>> otherSolution(vector<int>& nums) {
      sort(nums.begin(), nums.end());

      vector<vector<int>> result;
      if(nums.size() < 3) return result;

      unsigned int aIdx;
      unsigned int bIdx;
      int toFind;
      char firstRound = true;
      int lastNumA, lastNumB;
      for(aIdx = 0; aIdx < nums.size()-2 || nums[aIdx] <= 0; aIdx++) {
        if(firstRound) {
          lastNumA = nums[aIdx];
          firstRound = false;
        } else {
          if(lastNumA == nums[aIdx]) continue;
          else lastNumA = nums[aIdx];
        }

        lastNumB = lastNumA-1;

        for(bIdx = aIdx+1; bIdx < nums.size()-1; bIdx++) {
          if(lastNumB == nums[bIdx]) continue;
          else lastNumB = nums[bIdx];

          toFind = -(nums[aIdx]+nums[bIdx]);
          if(binary_search(nums.begin()+bIdx+1, nums.end(), toFind)){
            vector<int> newList;
            newList.push_back(nums[aIdx]);
            newList.push_back(nums[bIdx]);
            newList.push_back(toFind);
            result.push_back(newList);
          }
        }
      }

      return result;
    }

    // O(N^2) -- So simple and elegant!
    // From discussion https://leetcode.com/problems/3sum/discuss/7514/~20-lines.-68ms.-c%2B%2B-solution.-Used-two-pointers-similar-to-2sum
    vector<vector<int>> elegantSolution(vector<int>& nums) {
      vector<vector<int>> result;
      sort(nums.begin(), nums.end());
      if(nums.size() < 3) return result;

      int index = 0;
      int start;
      int end;
      while(index < nums.size()-2) {
        start = index+1;
        end = nums.size()-1;

        while(start < end) {
          if(nums[index]+nums[start]+nums[end] == 0) {
            vector<int> newList;
            newList.push_back(nums[index]);
            newList.push_back(nums[start]);
            newList.push_back(nums[end]);

            result.push_back(newList);

            start++;
            end--;
            while((start < end) && nums[start] == nums[start-1]) start++;
            while((start < end) && nums[end] == nums[end+1]) end--;
          } else if(nums[index]+nums[start]+nums[end] < 0) {
            start++;
            while((start < end) && nums[start] == nums[start-1]) start++;
          } else {
            end--;
            while((start < end) && nums[end] == nums[end+1]) end--;
          }
        }

        index++;
        while((index < nums.size()) && nums[index] == nums[index-1]) index++;
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> input = {-1, 0, 1, 2, -1, -4, 0, 0, 1/*1,2,-2,-1*//*0,0,0*//*-1,0,1,2,-1,-4*/};

  for(vector<int> v: s.threeSum(input)) {
    for(int i: v) cout << i << " ";
    cout << endl;
  }

  return 0;
}
