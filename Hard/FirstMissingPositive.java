class Solution {
    // It's a simple bucket sort!!!!
    // Lesson learned: No constraints on modifying input
    // Thanks to this answer https://leetcode.com/problems/first-missing-positive/discuss/17071/My-short-c%2B%2B-solution-O(1)-space-and-O(n)-time
    public int firstMissingPositive(int[] nums) {
        // Bucket sort
        for(int i = 0; i < nums.length; i++) {
            int currNum = nums[i];
            if(currNum > 0 && currNum <= nums.length && nums[currNum-1] != currNum) {
                int temp = nums[currNum-1];
                nums[currNum-1] = currNum;
                nums[i] = temp;
                i--;
            }
        }

        System.out.println(java.util.Arrays.toString(nums));

        // Check which index is not right
        for(int i = 0; i < nums.length; i++) {
            if(nums[i] != i+1) return i+1;
        }

        return nums.length+1;
    }
}

public class FirstMissingPositive {
    public static void main(String[] args) {
        Solution s = new Solution();

        int[] list = new int[]{};
        System.out.println(s.firstMissingPositive(list));
    }
}