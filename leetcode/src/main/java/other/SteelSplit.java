package other;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;




/*	钢条分割问题* 
 *	给定一张钢条价格表lengthPriceMap
 *	和一个固定的切割代价 COST_PER_SPLIT
 *	
 *	给定一条长钢条，要求切割使其总价最大化
 * 
 */
public class SteelSplit {
	private static Map<Integer, Double> lengthPriceMap = null;
	private static Map<Integer, Double> lengthMaxPriceMap = new HashMap<Integer, Double>();
	public final static double COST_PER_SPLIT = 1.0;
	
	public static void setLengthPriceMap(Map<Integer, Double> lengthPriceMap){
		SteelSplit.lengthPriceMap = lengthPriceMap;
	}
	
	public static void loadDefaultLengthPriceMap(){
		lengthPriceMap = new HashMap<Integer, Double>();
		SteelSplit.lengthPriceMap.put(1, 1.0);
		SteelSplit.lengthPriceMap.put(2, 5.0);
		SteelSplit.lengthPriceMap.put(3, 8.0);
		SteelSplit.lengthPriceMap.put(4, 9.0);
		SteelSplit.lengthPriceMap.put(5, 10.0);
		SteelSplit.lengthPriceMap.put(6, 17.0);
		SteelSplit.lengthPriceMap.put(7, 17.0);
		SteelSplit.lengthPriceMap.put(8, 20.0);
		SteelSplit.lengthPriceMap.put(9, 24.0);
		SteelSplit.lengthPriceMap.put(10, 30.0);
	}
	
	
	
	public static double getMaxPriceBySplit(int totalLength){
		if (SteelSplit.lengthPriceMap == null)
			loadDefaultLengthPriceMap();
		
		double maxPrice = 0;
		if (lengthMaxPriceMap.containsKey(totalLength)){
			maxPrice = lengthMaxPriceMap.get(totalLength);
//			System.out.println("problem solved before, len:" + totalLength + "==>" + maxPrice);
			return maxPrice;
		}
		
//		System.out.println("solving-len:" + totalLength);
		int maxSplitPoint = totalLength / 2;
		double[] maxPriceArr = new double[maxSplitPoint + 1];
		if (lengthPriceMap.containsKey(totalLength)){
			maxPriceArr[0] = lengthPriceMap.get(totalLength);
		} else {
			maxPriceArr[0] = 0;
		}
		
		for (int splitPoint = 1; splitPoint <= maxSplitPoint; splitPoint ++){
			int subLength1 = splitPoint;
			int subLength2 = totalLength - splitPoint;
//			System.out.println("div:" + totalLength + " = " + subLength1 + " + " + subLength2  );
			maxPriceArr[splitPoint] = getMaxPriceBySplit(subLength1) + getMaxPriceBySplit(subLength2) - SteelSplit.COST_PER_SPLIT;
		}
		
		for (int i = 0; i < maxPriceArr.length; i ++){
			if (maxPriceArr[i] >  maxPrice)
				maxPrice = maxPriceArr[i];
		}
//		System.out.println(maxPrice + "\t" + Arrays.toString(maxPriceArr) );
		lengthMaxPriceMap.put(totalLength, maxPrice);
		return maxPrice;
	}
	
	public static void main(String[] args) {
		long[] times = new long[5];
		int x = 1;
		for (int i = 0; i < times.length; i ++){
			long begin = System.currentTimeMillis();
			System.out.println(getMaxPriceBySplit(x));
			x = x * 10;
			times[i] = System.currentTimeMillis() - begin;
		}
		System.out.println(Arrays.toString(times));
		System.out.println(SteelSplit.lengthMaxPriceMap.get(10000));
		
		
	}
	
}
