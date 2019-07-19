#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int search(vector<int>& nums, int target) {
      return improveRuntime(nums, target);
    }

    int improveRuntime(vector<int>& nums, int target) {
      if(nums.size() == 0) return -1;

      int start = 0;
      int end = nums.size()-1;
      int first = nums[0];
      int last = nums[nums.size()-1];
      int mid;

      if(target == first) return 0;
      else if(target == last) return nums.size()-1;
      else if(target < first && target > last) return -1;

      while(start <= end) {
        mid = (start + end)/2;

        if(target == nums[mid]) return mid;
        else if(target > first) {
          if(nums[mid] < first) end = mid-1;
          else if(target < nums[mid]) end = mid-1;
          else start = mid+1;
        } else if(target < last){
          if(nums[mid] > last) start = mid+1;
          else if(target < nums[mid]) end = mid-1;
          else start = mid+1;
        }
      }

      return -1;
    }

    // O(log N)
    // Binary search, not sure why it's slow though
    int orignalSolution(vector<int>& nums, int target) {
      if(nums.size() == 0) return -1;

      int start = 0;
      int end = nums.size()-1;
      int mid;
      char leftHalf;

      if(target > nums[0]) {
        leftHalf = true;
      } else if(target < nums[nums.size()-1]) {
        leftHalf = false;
      }
      else if(target == nums[0]) return 0;
      else if(target == nums[nums.size()-1]) return nums.size()-1;
      else return -1;

      while(start <= end) {
        mid = (start+end)/2;

        if(nums[mid] == target) return mid;
        else if(leftHalf) {
          // Pass over the split point
          if(nums[mid] < nums[0]) end = mid-1;
          else if(nums[mid] < target) start = mid+1;
          else if(nums[mid] > target) end = mid-1;
        } else {
          // Pass over the split point
          if(nums[mid] > nums[nums.size()-1]) start = mid+1;
          else if(nums[mid] < target) start = mid+1;
          else if(nums[mid] > target) end = mid-1;
        }
      }

      return -1;
    }
};

int main() {
  // Warning, there are duplicates in the list
  srand(time(NULL));
  vector<int> list;

  // Generate random list
  for(int i = 0; i < 7; i++) list.push_back(rand() % 100);
  sort(list.begin(), list.end());

  cout << "Generated list: ";
  for(int i: list) cout << i << " ";

  cout << endl << "Please specify rotate point: ";
  int pos;
  cin >> pos;

  if(pos < 0 || pos > list.size()) cerr << "Check input." << endl;

  // Need to rotate
  if(pos != list.size() && pos != 0) {
    vector<int> newList = vector<int>(list.begin()+pos, list.end());
    for(int i = 0; i < pos; i++) newList.push_back(list[i]);
    list = newList;
  }

  cout << "Final list: ";
  for(int i: list) cout << i << " ";

  int target;
  Solution s;
  while(1) {
    cout << endl << "Enter target (101 to exit): ";
    cin >> target;

    if(target == 101) break;
    
    cout << "Found " << target << " at " << s.search(list, target);
  }
}
