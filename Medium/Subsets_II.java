import java.util.*;

public class Subsets_II {
    // Inspiration from: https://leetcode.com/problems/subsets-ii/discuss/30137/Simple-iterative-solution
    /**
     * Recall from BST questions, the current nodes to be working on is bounded by two pointer both increasing in the list.
     * Here we use the same technique to only process necessary values.
     * Also, since the input has only 10 elements, sorting is really fast.
     */
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        // Sort 10 elems is really fast
        java.util.Arrays.sort(nums);

        List<List<Integer>> result = new LinkedList<>();
        result.add(new LinkedList<>());

        int cutIdx = 0, startIdx = 0;
        for(int i = 0; i < nums.length; i++) {
            // Duplicate
            if(i > 0 && nums[i] == nums[i-1]) startIdx = cutIdx;
            else startIdx = 0;

            cutIdx = result.size();

            for(int j = startIdx; j < cutIdx; j++) {
                LinkedList<Integer> newList = new LinkedList<>(result.get(j));
                newList.add(nums[i]);
                result.add(newList);
            }
        }

        return result;
    }
    /**
     * This is directly translated from the subset_i problem with additional code to deal with duplicates (lexical solution).
     */
    public List<List<Integer>> subsetsWithDup1(int[] nums) {
        // Record distinct values and duplicate times for non-distinct values
        HashMap<Integer, Integer> values = new HashMap<>();
        for(int i: nums) {
            Integer times = values.get(i);
            if(times == null) values.put(i, 1);
            else values.put(i, times+1);
        }

        List<List<Integer>> result = new LinkedList<>();
        // Get distinct value length
        int[] keys = new int[values.size()];
        int idx = 0;
        for(int key: values.keySet()) keys[idx++] = key;
        int distinctValues = keys.length;
        for(int i = (int)Math.pow(2, distinctValues); i < (int)Math.pow(2, distinctValues+1); i++) {
            String mask = Integer.toBinaryString(i).substring(1);
            
            // Get asserted postions and values
            LinkedList<LinkedList<Integer>> subsets = new LinkedList<>();
            subsets.add(new LinkedList<>());

            for(int j = 0; j < distinctValues; j++) {
                // If asserted, add the corresponding value
                if(mask.charAt(j) == '1') {
                    LinkedList<LinkedList<Integer>> newSubsets = new LinkedList<>();

                    // First pass, add new value and to subset
                    for(LinkedList<Integer> subset: subsets) {
                        subset.add(keys[j]);
                        LinkedList<Integer> newSubset = new LinkedList<>(subset);
                        newSubsets.add(newSubset);
                    }

                    for(int k = 1; k < values.get(keys[j]); k++) {
                        for(LinkedList<Integer> subset: newSubsets) {
                            subset.add(keys[j]);
                            LinkedList<Integer> newSubset = new LinkedList<>(subset);
                            subsets.add(newSubset);
                        }
                    }
                }
            }

            // Add to result list after removing the initial empty set
            result.addAll(subsets);
        }

        return result;
    }

    public static void main(String[] args) {
        Subsets_II s = new Subsets_II();
        System.out.println(s.subsetsWithDup(new int[]{1,2,2}));
    }
}
