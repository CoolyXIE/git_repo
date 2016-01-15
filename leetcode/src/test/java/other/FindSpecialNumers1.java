package other;

import java.util.ArrayList;
import java.util.List;

public class FindSpecialNumers1 {
/* 
 	find how many numbers of length n are there such that 
	each number is at least 4 smaller/greater than the number 
	before and after it. Eg: if n = 5, such numbers are 39518, 15951, etc.
*/
	static final int diff = 7;
	public static List<Integer> getSpecialNumerList(int n){
		List<Integer> specialNumberList = new ArrayList<Integer>();
		if (n < 2) 
			System.err.println("至少两位数: n >= 2");
		else if (n == 2) {
			for (int i = 1; i <= 9; i ++){
				for (int j = 1; j <= 9; j++){
					if (Math.abs(i - j) >= diff)
						specialNumberList.add(i * 10 + j);
				}
			}
		} else {
			for (Integer specialNumber : getSpecialNumerList(n - 1)){
				int left = specialNumber/((int)Math.pow(10, n-2));
				int right = specialNumber%10;
				for (int i =1; i <= 9; i ++){
					if (Math.abs(left - i) >= diff)
						specialNumberList.add(i*(int)Math.pow(10, n-1) + specialNumber);
					if (Math.abs(right - i) >= diff)
						specialNumberList.add(specialNumber * 10 + i);
				}
			}
		}
		System.out.println("End: n = " + n + "Total number: " + specialNumberList.size());
		System.out.println(specialNumberList);
		return specialNumberList;
	}
	
	public static void main(String[] args) {
		getSpecialNumerList(5);
	}
}
