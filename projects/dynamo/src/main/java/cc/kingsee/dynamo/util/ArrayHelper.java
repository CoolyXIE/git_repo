package cc.kingsee.dynamo.util;

public class ArrayHelper {
	public static double max(double[] array){
		double max = array[0];
		for (int i = 1; i < array.length; i ++){
			if (array[i] > max)
				max = array[i];
		}
		return max;
	}
}
