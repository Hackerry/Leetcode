public class Jump_Game_II {
    // Although O(N^2) worst-case: ie-[4,3,2,1,1,8]
    public int jump(int[] nums) {
        int[] minJump = new int[nums.length];
        
        // Initialize min jump array
        for(int i = 0; i < minJump.length; i++) minJump[i] = -1;
        minJump[0] = 0;

        int j;
        for(int i = 0; i < minJump.length; i++) {
            j = i+1;
            while(j < nums.length && (j-i) <= nums[i]) {
                // Update indices where we can jump to
                if(minJump[j] > minJump[i] + 1 || minJump[j] == -1) minJump[j] = minJump[i] + 1;
                j++;
            }
        }

        return minJump[minJump.length-1];
    }

    public static void main(String[] args) {
        int[] list = new int[]{2,2,1,1,4};
        System.out.println(new Jump_Game_II().jump(list));
    }
}
