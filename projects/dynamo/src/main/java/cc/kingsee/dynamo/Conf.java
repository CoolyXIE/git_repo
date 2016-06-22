package cc.kingsee.dynamo;

import java.text.DecimalFormat;
import java.util.Random;

import cc.kingsee.dynamo.model.Climate;
import cc.kingsee.dynamo.model.Electric;
import cc.kingsee.dynamo.model.Oil;
import cc.kingsee.dynamo.model.Other;

public class Conf {
	static final DecimalFormat df = new DecimalFormat(".00");
	
	public static boolean inSafeRange(double value, double[] standard){
		double safeMin = standard[1];
		double safeMax = standard[3];
		if (value <= safeMax && value >= safeMin)
			return true;
		else
			return false;
	}

	public static double[] generateOneRandRecord(){
		double[] paramArr = new double[12];
		paramArr[0] = getRandSafeValue(Climate.TEMPERATURE_STANDARD);
		paramArr[1] = getRandSafeValue(Climate.HUMIDITY_STANDARD);
		paramArr[2] = getRandSafeValue(Climate.PRESSURE_STANDARD);
		paramArr[3] = getRandSafeValue(Electric.CURRENT_STANDARD);
		paramArr[4] = getRandSafeValue(Electric.VOLTAGE_STANDARD);
		paramArr[5] = getRandSafeValue(Electric.POWER_STANDARD);
		paramArr[6] = getRandSafeValue(Electric.HERTZ_STANDARD);
		paramArr[7] = getRandSafeValue(Oil.VOLUME_STANDARD);
		paramArr[8] = getRandSafeValue(Oil.PRESSURE_STANDARD);
		paramArr[9] = getRandSafeValue(Oil.TEMPERATURE_STANDARD);
		paramArr[10] = getRandSafeValue(Other.NOISE_STANDARD);
		paramArr[11] = getRandSafeValue(Other.REVOLUTION_STANDARD);
		
		return paramArr;
	}
	
	public static double getRandSafeValue(double[] standard){
		double safeMin = standard[1];
		double bestValue = standard[2];
		double safeMax = standard[3];
		
		double h = 2.0 / (safeMax -safeMin);
		double middleProb = 0.5 * (bestValue - safeMin) * h;
		
		Random random = new Random();
		double randDouble = random.nextDouble();
		double eps = 1e-3;
		if (randDouble < middleProb - eps)
			return Math.sqrt(randDouble / middleProb) * (bestValue - safeMin) + safeMin;
		else if (randDouble > middleProb + eps)
			return safeMax - Math.sqrt((1 - randDouble) / (1 - middleProb)) * (safeMax - bestValue);
		else 
			return bestValue;
	}
	
	public static double getErrorProb(double param, double[] standard){
		double dangerMin = standard[0];
		double safeMin = standard[1];
		double safeMax = standard[3];
		double dangerMax = standard[4];
		
		if (param > safeMax)
			return Math.pow(param - safeMax, 2.0) / Math.pow(dangerMax - safeMax, 2.0);
		else if (param < safeMin)
			return Math.pow(param - safeMin, 2.0) / Math.pow(dangerMin - safeMin, 2.0);
		else
			return 0.0;
	}
	
	public static double getErrorProb(Climate climate, Electric electric, Oil oil, Other other){
		return 1 - (1 - climate.getErrorProb()) * (1 - electric.getErrorProb()) * (1 - oil.getErrorProb()) * (1 - other.getErrorProb());
	}
	
//	public static void generateRecords(int n, String filePath) throws IOException{
//		BufferedWriter bw = FileHelper.writerFile(filePath);
//		for (int i = 0; i < n; i ++){
//			bw.write(formatToString(generateOneRandRecord()));
//		}
//		bw.close();
//		
//	}
	
	
	
//	public static String formatToString(double[] values){
//		String output = "";
//		for(int i = 0; i < values.length; i ++)
//			output += "\t" + df.format(values[i]);
//		output = output.substring(1) + "\n";
//		return output;
//	}
	
//	private static void show(){
//		System.out.println("air T： " + getRandSafeValue(TEMPERATURE_STANDARD) + "C");
//		System.out.println("H: " + getRandSafeValue(HUMIDITY_STANDARD) * 100 + "%");
//		System.out.println("air P: " + getRandSafeValue(PRESSURE_STANDARD) + "hPa");
//		System.out.println("I: " + getRandSafeValue(ELECTRIC_CURRENT_STANDARD) + "A");
//		System.out.println("U: " + getRandSafeValue(ELECTRIC_VOLTAGE_STANDARD) + "V");
//		System.out.println("W: " + getRandSafeValue(ELECTRIC_POWER_STANDARD) + "kW");
//		System.out.println("f: " + getRandSafeValue(ELECTRIC_HERTZ_STANDARD) + "Hz");
//		System.out.println("V: " + getRandSafeValue(OIL_VOLUME_STANDARD) * 100 + "%");
//		System.out.println("oil P: " + getRandSafeValue(OIL_PRESSURE_STANDARD) + "MPa");
//		System.out.println("oil T: " + getRandSafeValue(OIL_TEMPERATURE_STANDARD) + "C");
//		System.out.println("noise: " + getRandSafeValue(NOISE_STANDARD) + "dB");
//		System.out.println("N: " + getRandSafeValue(REVOLUTION_STANDARD) + "rpm");
//	}
	
//	public static void main(String[] args) throws IOException {
////		generateRecords(100, "F:/data/ab.txt");
//		show();
//	}

	


}
