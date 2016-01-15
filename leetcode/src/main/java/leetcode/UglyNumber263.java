package leetcode;

public class UglyNumber263 {

	/* Write a program to check whether a given number is an ugly number.
	 * Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. 
	 * For example, 6, 8 are ugly while 14 is not ugly 
	 * since it includes another prime factor 7.
	 * 
	 * Note that 1 is typically treated as an ugly number.
	 * 
	 */
	public boolean isUgly(int num) {
		if (num < 1)
			return false;
		else if (num == 1)
			return true;
		else {
			int[] uglyPrimes = {2,3,5};
			for (int i = 0; i < uglyPrimes.length; i ++){
				int uglyPrime = uglyPrimes[i];
				while(num % uglyPrime == 0)
					num = num / uglyPrime;
			}
			if (num == 1)
				return true;
			else
				return false;
		}
	}
}
