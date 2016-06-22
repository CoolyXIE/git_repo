package leetcode;

import java.util.Arrays;



/*
 * 	There are N children standing in a line. Each child is assigned a rating value.

 You are giving candies to these children subjected to the following requirements:

 Each child must have at least one candy.
 Children with a higher rating get more candies than their neighbors.

 What is the minimum candies you must give?
 * 
 * 
 */
public class Candy135 {
	public static int myCandy(int[] ratings) {
		if (ratings.length == 1){
			return 1;
		}
		int[] candyNum = new int[ratings.length];
		candyNum[0] = 1;
		int descBeginIndex = 0;
		int descEndIndex = 0;
		
		for (int i = 1; i < candyNum.length; i++) {
			if (ratings[i] >= ratings[i - 1]) {
				descEndIndex = i - 1;
				// handle this desc candy
				if (i!= 1 &&ratings[i-1] <= ratings[i-2]){
					if (candyNum[i - 1] <= 1) {
						for (int j = descBeginIndex; j <= descEndIndex; j++){
							candyNum[j] = candyNum[j] + 1 - candyNum[i - 1];
							System.out.println("index: " + j + "\t" + candyNum[j]);
						}
							
					} else {
						for (int j = descBeginIndex + 1; j <= descEndIndex; j ++){
							candyNum[j] =candyNum[j] - candyNum[i -1] + 1;
							System.out.println("index: " + j + "\t" + candyNum[j]);
						}
					}
				}
				
				
				if (ratings[i] > ratings[i - 1]){
					candyNum[i] = candyNum[i - 1] + 1;
					System.out.println("index: " + i + "\t" + candyNum[i]);
				}
				else {
					if (i == candyNum.length -1 || ratings[i + 1] >= ratings[i]) {
						candyNum[i] = 1;
						System.out.println("index: " + i + "\t" + candyNum[i]);
					} else {
						candyNum[i] = 2;
						System.out.println("index: " + i + "\t" + candyNum[i]);
						descBeginIndex = i;
					}
				}
			} 
			else {
				if (i == 1 || ratings[i - 1] >= ratings[i - 2])
					descBeginIndex = i - 1;
				candyNum[i] = candyNum[i - 1] - 1;
				System.out.println("index: " + i + "\t" + candyNum[i]);
			}

		}
		
		//hand last one
		if (candyNum[candyNum.length -1] < candyNum[candyNum.length-2]){
			descEndIndex = candyNum.length - 1;
			if (candyNum[descEndIndex] <= 1){
				for (int j = descBeginIndex; j <= descEndIndex; j ++){
					candyNum[j] += 1 - candyNum[descEndIndex];
				}
			}else {
				for (int j = descBeginIndex + 1; j <= descEndIndex; j ++)
					candyNum[j] -= candyNum[j] - 1;
			}
		}
		System.out.println(Arrays.toString(candyNum));
		int sum = 0;
		for (int i = 0; i < candyNum.length; i ++){
			sum += candyNum[i];
		}
		return sum;
	}
	
	
	
	public static void main(String[] args) {
		int[] r = {58,21,72,77,48,9,38,71,68,77,82,47,25,94,89,54,26,54,54,99,64,71,76,63,81,82,60,64,29,51,87,87,72,12,16,20,21,54,43,41,83,77,41,61,72,82,15,50,36,69,49,53,92,77,16,73,12,28,37,41,79,25,80,3,37,48,23,10,55,19,51,38,96,92,99,68,75,14,18,63,35,19,68,28,49,36,53,61,64,91,2,43,68,34,46,57,82,22,67,89};
		System.out.println(myCandy(r));
	}
	
}
