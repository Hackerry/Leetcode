public class Number_Of_1_Bits {
    // you need to treat n as an unsigned value
    public int hammingWeight(int n) {
        int len = 32;
        int mask = 0x1;
        int count = 0;

        for(int i = 0; i < len; i++) {
            if((n & mask) == mask) count++;
            n >>>= 1;
        }

        return count;
    }

    public static void main(String[] args) {
        System.out.println("\n" + new Number_Of_1_Bits().hammingWeight(-3));
    }
}
