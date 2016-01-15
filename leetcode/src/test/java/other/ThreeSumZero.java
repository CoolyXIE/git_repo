package other;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;


public class ThreeSumZero {
	public static List<List<Integer>> myThreeSum(int[] nums) {
		for (int i = 0; i < nums.length - 1; i ++){
			int minIndex = i;
			for (int j = i + 1; j < nums.length; j ++)
				if (nums[j] < nums[minIndex]) 
					minIndex = j;
			int minValue = nums[minIndex];
			nums[minIndex] = nums[i];
			nums[i] = minValue;
		}
		List<List<Integer>> tripletList = new ArrayList<List<Integer>>();
		for (int index1 = 0; index1 < nums.length; index1 ++){
			int index3 = nums.length - 1;
			for (int index2 = index1 + 1; index2 < index3;){
				if (nums[index1] + nums[index2] + nums[index3] == 0){
					List<Integer> sortedTriplet = new ArrayList<Integer>(Arrays.asList(nums[index1],nums[index2],nums[index3]));
					Collections.sort(sortedTriplet,new Comparator<Integer>(){   
				           public int compare(Integer o1, Integer o2) {   
				               return o1 - o2;   
				            }   
				        });
					if (!tripletList.contains(sortedTriplet))
						tripletList.add(sortedTriplet);
					index2 ++;
				} else if (nums[index1] + nums[index2] + nums[index3] > 0) {
					index3 --;
				} else {
					index2 ++;
				}
			}
		}
		return tripletList;
    }
	
	public static List<List<Integer>> hisThreeSum1(int[] num) {
	    Arrays.sort(num);
	    List<List<Integer>> res = new LinkedList<List<Integer>>(); 
	    for (int i = 0; i < num.length-2; i++) {
	        if (i == 0 || (i > 0 && num[i] != num[i-1])) {
	            int lo = i+1, hi = num.length-1, sum = 0 - num[i];
	            while (lo < hi) {
	                if (num[lo] + num[hi] == sum) {
	                    res.add(Arrays.asList(num[i], num[lo], num[hi]));
	                    while (lo < hi && num[lo] == num[lo+1]) lo++;
	                    while (lo < hi && num[hi] == num[hi-1]) hi--;
	                    lo++; hi--;
	                } else if (num[lo] + num[hi] < sum) lo++;
	                else hi--;
	           }
	        }
	    }
	    return res;
	    
	    /*评价：跟我最初的思路基本一致，但是实现去重的代码部分设计的更为精巧
	     * 算法的设计与代码细处的实现还需加强
	     */
	}
	
	
	
	
	public static void main(String[] args) {
		int[] nums = {12,0,3,-14,5,-11,11,-5,-2,-1,6,-7,-10,1,4,1,1,9,-3,6,-15,0,6,1,6,-12,3,7,11,-6,-8,0,9,3,-7,-1,7,-10,1,13,-4,-7,-9,-7,9,3,1,-13,-3,13,8,-11,-9,-8,-3,4,-13,7,-11,5,-14,-4,-9,10,6,-9,-6,-9,-12,11,-11,-9,11,-5,0,-3,13,-14,-1,-13,7,-7,14,5,0,-4,-6,-6,-11,-2,14,-10,2,12,8,-7,-11,-13,-9,14,5,-5,-9,1,-2,6,5,-12,-1,-10,-9,-9,-10,12,11};
		long start = System.currentTimeMillis();
		System.out.println(hisThreeSum1(nums));
		System.out.println("hisThreeSum1: " + (System.currentTimeMillis() - start) + "ms");
		start = System.currentTimeMillis();
		System.out.println(myThreeSum(nums));
		System.out.println("myThreeSum: " + (System.currentTimeMillis() - start) + "ms");
		
	}
}
