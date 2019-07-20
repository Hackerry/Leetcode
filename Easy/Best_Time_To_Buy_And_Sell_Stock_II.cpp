#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
  public:
    // See solution
    // We buy at the lowest point before a decreasing value,
    // and find the next min price after the peak.
    // Correspond to the normal sense of buy and sell quick.
    int maxProfit(vector<int>& prices) {
      if(prices.size() <= 1) return 0;

      int minPrice = prices[0];
      int maxProfit = 0;

      for(int i = 1; i < prices.size(); i++) {
        if(prices[i] < minPrice) {
          minPrice = prices[i];
        }
        // Value increasing
        else if(prices[i] > prices[i-1]) {
          maxProfit += (prices[i] - prices[i-1]);
        } else {
          minPrice = prices[i];
        }
      }

      return maxProfit;
    }
};

int main() {
  Solution s;
  vector<int> prices = {7,1,5,3,6,4};

  cout << "Max profit: " << s.maxProfit(prices) << endl;
}
