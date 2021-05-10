public class Coin_Change_2 {
    // Solution 1: runtime & space O(NM)
    public int change1(int amount, int[] coins) {
        // Give no coin.
        if(amount == 0) return 1;
        else if(coins.length == 0) return 0;

        java.util.Arrays.sort(coins);

        int[][] values = new int[coins.length][amount];
        
        for(int i = 0; i < coins.length; i++) {
            for(int j = 0; j < amount; j++) {
                // Use prev coin
                if(i-1 >= 0) values[i][j] += values[i-1][j];

                // Use current coin
                if(j-coins[i] >= 0) values[i][j] += values[i][j-coins[i]];

                // Use single coin
                if(coins[i] == j+1) values[i][j]++;
            }
        }

        // for(int i = 0; i < values.length; i++) System.out.println(java.util.Arrays.toString(values[i]));

        return values[coins.length-1][amount-1];
    }

    // Solution 2: Runtime O(NM) Space O(N)
    public int change(int amount, int[] coins) {
        // Give no coin.
        if(amount == 0) return 1;
        else if(coins.length == 0) return 0;

        // Sorting is unneeded
        // java.util.Arrays.sort(coins);

        int[] values = new int[amount];
        
        for(int i = 0; i < coins.length; i++) {
            for(int j = 0; j < amount; j++) {
                // Use prev coin - already stored

                // Use current coin
                if(j-coins[i] >= 0) values[j] += values[j-coins[i]];

                // Use single coin
                if(coins[i] == j+1) values[j]++;
            }
        }

        // for(int i = 0; i < values.length; i++) System.out.println(java.util.Arrays.toString(values[i]));

        return values[amount-1];
    }

    public static void main(String[] args) {
        Coin_Change_2 s = new Coin_Change_2();
        int[] Cm = {1,2,5};
        int amount = 5;
        System.out.println(s.change(amount, Cm));
    }
}
