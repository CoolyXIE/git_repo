package leetcode.finish;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

public class ContainerWithMostWater11 {
	/*
	 * Given n non-negative integers a1, a2, ..., an, where each represents a
	 * point at coordinate (i, ai). n vertical lines are drawn such that the two
	 * endpoints of line i is at (i, ai) and (i, 0).
	 * 
	 * Find two lines, which together with x-axis forms a container, such that
	 * the container contains the most water.
	 * 
	 * Note: You may not slant the container.
	 */
	/*
	 * 
	 * 
	 * 
	 * 
	 */
	public static int myGetMaxArea(int[] height) {
		int finalLeftIndex = 0;
		int finalRightIndex = 0;
		if (height.length < 2)
			return 0;
		// optimize heightArray
		int highestIndex = 0;
		List<Integer> rightIndexList = new ArrayList<Integer>();
		List<Integer> leftIndexList = new ArrayList<Integer>(Arrays.asList(0));
		for (int i = 1; i < height.length; i++) {
			if (height[i] > height[highestIndex]) {
				highestIndex = i;
				leftIndexList.add(i);
				rightIndexList = new ArrayList<Integer>();
			} else if (rightIndexList.isEmpty()
					|| height[i] < height[rightIndexList.get(rightIndexList
							.size() - 1)]) {
				rightIndexList.add(i);
			} else {
				boolean remove = false;
				for (Iterator<Integer> it = rightIndexList.iterator(); it
						.hasNext();) {
					if (remove) {
						it.next();// 必须it.next()
						it.remove();
						continue;
					}
					if (height[it.next()] <= height[i]) {
						it.remove();
						remove = true;
					}
				}
				rightIndexList.add(i);
			}
		}

		rightIndexList.add(0, highestIndex);
		System.out.println(leftIndexList);
		System.out.println(rightIndexList);

		int maxArea = 0;
		if (leftIndexList.size() <= 1) {
			finalLeftIndex = highestIndex;
			for (int i = 1; i < rightIndexList.size(); i++) {
				int thisArea = (rightIndexList.get(i) - rightIndexList.get(0))
						* height[rightIndexList.get(i)];
				if (thisArea >= maxArea) {
					maxArea = thisArea;
					finalRightIndex = rightIndexList.get(i);
				}
			}
		} else {
			for (Integer rightIndex : rightIndexList) {
				// find maxAread to construct containers with each index in
				// leftIndexList
				for (Integer leftIndex : leftIndexList) {
					int thisArea = (rightIndex - leftIndex)
							* Math.min(height[leftIndex], height[rightIndex]);
					if (thisArea >= maxArea) {
						maxArea = thisArea;
						finalLeftIndex = leftIndex;
						finalRightIndex = rightIndex;
					}
				}
			}
		}
		System.out.println("(" + finalRightIndex + " - " + finalLeftIndex
				+ ") * min(" + height[finalLeftIndex] + ","
				+ height[finalRightIndex] + ") = " + maxArea);
		return maxArea;
	}

	public  static int hisGetMaxArea1(int[] height) {
		int start = 0;
		int end = height.length - 1;
		int max = 0;
		int area = 0;

		if (height.length == 0 || height.length == 1) {
			return 0;
		}
		// two-pointer scan, start from both sides of the array
		while (start < end) {
			area = getArea(height, start, end);
			if (area > max) {
				max = area;
			}

			if (height[start] < height[end]) {
				start++;
			} else {
				end--;
			}

		}
		return max;
	}

	public static int getArea(int[] height, int start, int end) {
		int Height = Math.min(height[start], height[end]);
		return Height * (end - start);
	}

	public static void main(String[] args) {
		int[] height = new int[15000];
		for (int i = 0; i < 15000; i++) {
			height[i] = 15000 - i;
		}
		long start = System.currentTimeMillis();
		System.out.println(myGetMaxArea(height));
		System.out.println(System.currentTimeMillis() - start);
		start = System.currentTimeMillis();
		System.out.println(hisGetMaxArea1(height));
		System.out.println(System.currentTimeMillis() - start);
		
	}
}
