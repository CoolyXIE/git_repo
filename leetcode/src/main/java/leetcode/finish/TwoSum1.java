package leetcode.finish;

import java.util.ArrayList;
import java.util.List;

public class TwoSum1 {
	static class IndexPair{
		int begin;
		int end;
		
		//constructor
		public IndexPair(int begin, int end) {
			super();
			this.begin = begin;
			this.end = end;
		}
		
		//public method
		@Override
		public String toString() {
			return begin + "-->" + end;
		}
		
		public int getBegin() {
			return begin;
		}
		
		public void setBegin(int begin) {
			this.begin = begin;
		}
		
		public int getEnd() {
			return end;
		}
		
		public void setEnd(int end) {
			this.end = end;
		}
		
		
	}

	public static List<IndexPair> findIndex(int[] nums, int target) {
		List<IndexPair> indexPairList = new ArrayList<TwoSum1.IndexPair>();
		for (int i = 0; i < nums.length; i ++) {
			int pairedIndex = target - nums[i];
			for (int j = i + 1; j < nums.length; j ++) {
				if (nums[j] == pairedIndex) {
					IndexPair indexPair = new IndexPair(i, j);
					indexPairList.add(indexPair);
				}
			}
		}
		return indexPairList;
	}
	public static void main(String[] args) {
		int[] nums = {1,3,4,5,6,7};
		System.out.println(findIndex(nums, 10));
		
	}
}

