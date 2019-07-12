import java.util.Arrays;

public class LongestPalindrome {
	/**
	 * Expand around center, O(n).
	 * See leetcode solution.
	 */
	public static String longestPalindrome(String s) {
		if(s.length() == 0) return "";
		
		int len1, len2;
		int maxL = 0, start = 0, end = 0, temp;
		for(int i = 0; i < s.length(); i++) {
			len1 = expandAroundCenter(s, i, i);
			len2 = expandAroundCenter(s, i, i+1);
			
			if((temp = Math.max(len1, len2)) > maxL) {
				maxL = temp;
				start = i-(maxL-1)/2;
				end = i+maxL/2;
			}
		}
		
		return s.substring(start, end+1);
	}
	
	// Helper for expanding around center
	private static int expandAroundCenter(String s, int left, int right) {
		while(left >= 0 && right < s.length() && s.charAt(left) == s.charAt(right)) {
			left--; right++;
		}
		
		return right-left-1;
	}
	
	/**
	 * Manacher's algorithm, O(n).
	 * Good source: https://www.youtube.com/watch?v=V-sEwsca1ak, Wikipedia
	 */
	public static String ManacherAlgorithm(String s) {
		if(s.length() == 0) return "";
		
		char[] schars = addGaps(s);
		int[] maxLength = new int[schars.length];
		
		int currCenter = 0, currHalfLength = 0;
		int mirrorLength;
		Outer: for(int i = 0; i < schars.length; i++) {
			// Outside last palindrome or at the last of last palindrome
			if(currCenter + currHalfLength <= i) {
				maxLength[i] = expandAroundCenter(schars, i);
				currCenter = i;
				currHalfLength = maxLength[i]/2;
			} else {
				// Test every char within this 
				for(int j = currCenter+1; j <= currCenter+currHalfLength; j++) {
					mirrorLength = maxLength[2*currCenter-j];
					
					// Palindrome totally contained
					if(mirrorLength/2+j < currCenter+currHalfLength) {
						maxLength[j] = mirrorLength;
					}
					// Palindrome mirror pass the last palindrome
					else if(mirrorLength/2+j > currCenter+currHalfLength) {
						maxLength[j] = (currCenter+currHalfLength-j)*2+1;
					}
					// Reach the last char of last palindrome
					else {
						maxLength[j] = expandAroundCenter(schars, j);
						currCenter = j;
						currHalfLength = maxLength[j]/2;
						
						// No more things to test
						if(currCenter+currHalfLength >= schars.length) {
							break Outer;
						}
					}
				}
			}
		}
		
		//System.out.println(Arrays.toString(maxLength));
		
		int maxL = 0, maxIdx = -1;
		for(int i = 0; i < maxLength.length; i++) {
			if(maxLength[i] > maxL) {
				maxL = maxLength[i];
				maxIdx = i;
			}
		}
		
		return getString(schars, maxIdx, maxL);
	}
	
	/**
	 * Helper function to make all palindrome odd-length for easy process.
	 */
	private static char[] addGaps(String s) {
		char gap = '|';
		char[] result = new char[s.length()*2+1];
		result[0] = gap;
		
		for(int i = 0; i < s.length(); i++) {
			result[2*i+1] = s.charAt(i);
			result[2*i+2] = gap;
		}
		
		// System.out.println(Arrays.toString(result));
		return result;
	}
	
	/**
	 * Helper function to get the expanded length at index.
	 */
	private static int expandAroundCenter(char[] chars, int index) {
		int left = index-1, right = index+1;
		while(left >= 0 && right < chars.length && chars[left] == chars[right]) {
			left--; right++;
		}
		
		return right-left-1;
	}
	
	/**
	 * Helper function to get string back without gaps.
	 */
	private static String getString(char[] chars, int idx, int length) {
		char[] result = new char[length/2];
		int index = 0;
		for(int i = idx-length/2; i < idx+length/2; i+=2) {
			result[index++] = chars[i+1];
		}
		
		return new String(result);
	}

	public static void main(String[] args) {
		String[] input = new String[] { "ekkeacaekkect", "", "asd", "a", "bab", "acca", "ac", "abb", "222020221" };
		for (String s : input) {
			System.out.println("Longest Palindrome: " + longestPalindrome(s));
			System.out.println("Longest Palindrome: " + ManacherAlgorithm(s));
		}
	}
}

