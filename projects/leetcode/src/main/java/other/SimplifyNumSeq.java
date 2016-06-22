package other;


public class SimplifyNumSeq {
	
	public static int getEndIndexQuickly(int beginIndex, int[] numArr){
		int maxIncre = numArr.length - beginIndex - 1;
		int lastIncre = 0;
		int thisIncre = 0;
		int increment = 1;
		//expand by exponential order
		boolean expand = true;
		while (expand) {
			if (increment <= maxIncre && numArr[increment + beginIndex] == numArr[beginIndex] + increment){
				increment *= 2;
			}
			else if (increment <= maxIncre){
//				System.out.println("Stop at: " + increment + " because of unmatch!");
				lastIncre = increment / 2;
				thisIncre = increment;
				expand = false;
			} else {
//				System.out.println("Stop at: " + maxIncre + " because of out of bound!");
				lastIncre = increment / 2;
				thisIncre = maxIncre;
				expand = false;
			}
		}
		
		//use bisection method to find endIndex
		while (thisIncre - lastIncre > 1){
			increment = (thisIncre + lastIncre) / 2;
			if (numArr[increment + beginIndex] == numArr[beginIndex] + increment){
//				System.out.println(lastIncre + "o\t" + increment + "o\t" + thisIncre + "x" );
				lastIncre = increment;
			} else {
//				System.out.println(lastIncre + "o\t" + increment + "x\t" + thisIncre + "x");
				thisIncre = increment;
			}
		}
		return lastIncre + beginIndex;
	}
	
	public static String getSimpleNumSeq(int[] numArr){
		String result = "";
		int beginIndex = 0;
		while (beginIndex < numArr.length){
			int endIndex = getEndIndexQuickly(beginIndex, numArr);
			String beginValue = String.valueOf(numArr[beginIndex]);
			String endValue = String.valueOf(numArr[endIndex]);
			if (beginIndex == endIndex)
				result +=  "," + beginValue;
			else
				result += "," + beginValue + "-" + endValue;
			beginIndex = endIndex + 1;
		}
		return result.substring(1);
	}
	
	public static void main(String[] args) {
		int[] arr = {1,2,3,4,11,23,24};
		System.out.println(getSimpleNumSeq(arr));
	}
	
}
