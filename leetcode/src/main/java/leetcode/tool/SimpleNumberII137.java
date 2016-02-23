package leetcode.tool;

import tool.Digits;

public class SimpleNumberII137 {
	private int k;
	private int[] nums;
	
	public SimpleNumberII137(int k, int[] nums) {
		super();
		this.k = k;
		this.nums = nums;
	}
	
	public int findTheSingleOne(){
		int[] digits = new int[32];
		for (int num : nums){
			for (int i = 31; i >= 0; i -- ){
				if ((num >> i) % 2 != 0){
					digits[i] = (digits[i] + 1) % k;
				}
			}
		}
		//从二进制位还原该数
		return Digits.parseInt(digits);
	}
}
