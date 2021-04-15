import java.util.Arrays;

public class Insert_Interval {
    // Mistake 1: failed to consider non-overlapping interval (length+1)
    // Mistake 2: failed to consider edge case where interval starts and/or ends outside the last interval
    // Ttricky to implement (draw out pictures and remember to address the edge cases)
    public int[][] insert(int[][] intervals, int[] newInterval) {
        // Q1: boundary values are within the interval or not?

        // Edge case, empty intervals list
        if(intervals.length == 0 || intervals == null) return new int[][]{newInterval};

        // Initialize result, add one more in case that new interval never overlaps with any other intervals
        int[][] result = new int[intervals.length+1][];

        // Maintain the indices of the starting and ending intervals
        int startIdx = -1, endIdx = -1;
        int currIdx = 0, i = 0;

        // New interval not start within range
        while(i < intervals.length && intervals[i][1] < newInterval[0]) result[currIdx++] = intervals[i++];

        // Start index found or -1 if list is exhausted
        if(i < intervals.length && intervals[i][1] >= newInterval[0]) startIdx = i;

        // Find end index or -1 if list is exhausted
        while(i < intervals.length && intervals[i][0] <= newInterval[1]) endIdx = i++;

        // Edge case, end of list and non-overlapping intervals
        if(startIdx == -1) result[currIdx++] = new int[]{newInterval[0], Math.max(intervals[intervals.length-1][1], newInterval[1])};
        else if(endIdx == -1) result[currIdx++] = new int[]{Math.min(intervals[intervals.length-1][0], newInterval[0]), newInterval[1]};

        // Normal case, merge if possible
        else result[currIdx++] = new int[]{Math.min(intervals[startIdx][0], newInterval[0]), Math.max(intervals[endIdx][1], newInterval[1])};

        // Append the rest of the list, if any
        while(i < intervals.length) result[currIdx++] = intervals[i++];

        // Copy of array to eliminate unused cells
        int[][] newResult = new int[currIdx][];
        for(i = 0; i < currIdx; i++) newResult[i] = result[i];

        return newResult;
    }

    public static void main(String[] args) {
        int[][] list = new int[][]{
            {1,5}
        };
        int[] newInterval = new int[] {1,5};
        int[][] result = new Insert_Interval().insert(list, newInterval);

        for(int[] is: result) {
            System.out.println(is[0] + " " + is[1]);
        }
    }
}
