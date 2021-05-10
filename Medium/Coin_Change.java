import java.util.HashMap;
import java.util.Map;

// Tricky case: 1, 2, 11, 13, 20 -> If use large coins first with max # of that coin, then 46 would use
// 20, 20, 2, 2, 2 - 5
// 13, 13, 13, 2, 2, 1 - 6
// 11, 11, 11, 11, 2 - 5
// while in fact, 11, 11, 11, 13 is the minimum configuration

class Coin_Change {
    // Solution 1: Keep track of min number for constructing each amount value.
    /* 
     * Correctness check:
     * Base case: 1) For any amount that has a corresponding coin value, the min # of coin is 1.
     *            2) We can only use a coin if the amount is larger than the coin value.
     * Induction case: For amount X and valid coin [Y,Z,W...], the min # of coin is the minimum of min(coin(X-Y),coin(X-Z),coin(X-W),...)+1 or 1 if X == Y/Z/W/...
     *                 To construct amount X, we can either use 1 coin (coint=amount) or add a coin to a previous amount using valid coins [Y/Z/W/...].
     */
    // Runtime: O(MN) Space: O(M) where M=amount and N=coins.length
    public int coinChange1(int[] coins, int amount) {
        if(amount == 0) return 0;

        java.util.Arrays.sort(coins);

        int[] values = new int[amount+1];
        for(int i = 0; i < values.length; i++) {
            int minNum = Integer.MAX_VALUE;

            int lastCoinNum;
            for(int j = 0; j < coins.length && coins[j] <= amount && i-coins[j] >= 0; j++) {
                lastCoinNum = values[i - coins[j]];
                if(lastCoinNum != 0) {
                    minNum = Math.min(minNum, lastCoinNum+1);
                } else if(coins[j] == i) {
                    // If there is a coin for this value, set to 1
                    minNum = 1;
                }
            }

            // Update coin num
            if(minNum != Integer.MAX_VALUE) values[i] = minNum;
        }

        // System.out.println(java.util.Arrays.toString(values));

        return values[amount] == 0? -1: values[amount];
    }

    // Solution 2: Use coin as the tracking amount with memorization of calculate values.
    /*
     * Correctness check:
     * It's just brute-force.
     */
    public int coinChange2(int[] coins, int amount) {
        if(amount == 0) return 0;

        java.util.Arrays.sort(coins);

        HashMap<Integer, Integer> values = new HashMap<>();
        int value = coinChangeHelper(coins, amount, values);
        // System.out.println(values);
        return value;
    }

    private int coinChangeHelper(int[] coins, int amount, HashMap<Integer, Integer> values) {
        int minCoin = Integer.MAX_VALUE;
        for(int i = 0; i < coins.length; i++) {
            if(coins[i] < amount) {
                int newAmount = amount - coins[i];
                int newAmountCoin;
                if(values.get(newAmount) != null) newAmountCoin = values.get(newAmount);
                else newAmountCoin = coinChangeHelper(coins, newAmount, values);

                if(newAmountCoin != -1) {
                    minCoin = Math.min(minCoin, newAmountCoin + 1);
                }
            } else if(coins[i] == amount) {
                minCoin = 1;
                break;
            } else {
                break;
            }
        }

        if(minCoin != Integer.MAX_VALUE) {
            values.put(amount, minCoin);
            return minCoin;
        } else {
            values.put(amount, -1);
            return -1;
        }
    }

    public static void main(String[] args) {
        Coin_Change s = new Coin_Change();
        int[] Cm = {1,1000};
        int amount = 2;
        System.out.println(s.coinChange(Cm, amount));
    }
}