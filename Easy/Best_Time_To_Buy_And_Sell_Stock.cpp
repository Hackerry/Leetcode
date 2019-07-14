#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Solution {
  public:
    int maxProfit(vector<int>& prices) {
      return solution(prices);
    }

    int bruteForce(vector<int>& prices) {
      if(prices.size() < 2) return 0;

      int maxProfit = 0;
      int currProfit;
      for(int i = 0; i < prices.size()-1; i++) {
        currProfit = 0;
        for(int j = i+1; j < prices.size(); j++) {
          if(prices[j] - prices[i] > currProfit)
            currProfit = prices[j]-prices[i];
        }

        if(currProfit > maxProfit) maxProfit = currProfit;
      }

      return maxProfit;
    }

    int solution(vector<int>& prices) {
      if(prices.size() < 2) return 0;

      int min = numeric_limits<int>::max();
      int profit = 0;
      for(int i: prices) {
        if(i < min) {
          min = i;
        } else if(i - min > profit) {
          profit = i-min;
        }
      }

      return profit;
    }
};

int main() {
  Solution s;
  vector<int> input = {/*4,1,2*//*3,2,6,5,0,3*//*7,6,4,3,1*/1,2,4,2,5,7,2,4,9,0,9};

  cout << s.maxProfit(input) << endl;
}
