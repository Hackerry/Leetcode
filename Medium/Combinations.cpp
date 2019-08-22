#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    // Not bad!
    // 89.8% - 100%
    vector<vector<int>> combine(int n, int k) {
      vector<vector<int>> result;

      // Edge case, n or k is 0
      if(n == 0 || k == 0) return result;

      vector<int> val(k, 0);
      int idx;
      for(int i = 0; i < val.size(); i++) val[i] = i+1;

      while(val[0] <= n-k+1) {
        result.push_back(val);

        idx = k-1;
        // Update previous values
        while(idx >= 0 && ++val[idx] > n-k+1+idx) idx--;

        // Reached the last permutation
        if(idx == -1) continue;

        for(++idx; idx < k; idx++) {
          val[idx] = val[idx-1]+1;
        }
      }

      return result;
    }
};

int main() {
  Solution s;
  vector<int> ns = {1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 0, 5};
  vector<int> ks = {1, 2, 1, 2, 3, 1, 2, 3, 2, 3, 4, 0, 2};

  for(int i = 0; i < ns.size(); i++) {
    cout << ns[i] << "-" << ks[i] << ": " << endl;
    for(vector<int>& v: s.combine(ns[i], ks[i])) {
      for(int k: v) cout << k << " ";
      cout << endl;
    }
  }
}
