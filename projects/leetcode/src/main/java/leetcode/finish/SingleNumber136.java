package leetcode.finish;

public class SingleNumber136 {
	/* 	Given an array of integers
	 * 	every element appears twice except for one. 
	 * 	Find that single one.
	 * 
	 * Note: 
	 *  Your algorithm should have a linear runtime complexity. 
	 *  Could you implement it without using extra memory?
	 */

	public static int singleNumber(int[] nums) {
		int x = 0;
		for (int i = 0; i < nums.length; i ++)
			x = x ^ nums[i];
		for (int i = 0; i < nums.length; i ++)
			if (nums[i] == x)
				return i;
		return 0;
	}
}
