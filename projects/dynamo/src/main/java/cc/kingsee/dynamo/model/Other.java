package cc.kingsee.dynamo.model;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import cc.kingsee.dynamo.Conf;
import cc.kingsee.dynamo.util.ArrayHelper;

public class Other {
	public static final double[] NOISE_STANDARD = {0, 60, 70, 90, 100};
	public static final double[] REVOLUTION_STANDARD = {600, 1499, 1501, 1500, 3000};

	private double noise;
	private double revolution;
	
	public Other(double noise, double revolution) {
		super();
		this.noise = noise;
		this.revolution = revolution;
	}

	public boolean suggest() throws InterruptedException{
		String badParamString = "";
		if (!Conf.inSafeRange(noise, NOISE_STANDARD))
			badParamString += "噪音";
		if (!Conf.inSafeRange(revolution, REVOLUTION_STANDARD))
			badParamString += ",转数";

		boolean status = true;
		if (badParamString.isEmpty())
			System.out.println("其他参数正常");
		else {
			System.out.println(badParamString + "参数异常，可能会造成机器故障，请即刻前往检查机器状态！");
			Thread.sleep(3000);
			System.out.println("机器是否正常？Y/N");
			status = new Scanner(System.in).nextLine().equals("Y");
//			Scanner scanner = new Scanner(System.in);
//			status = scanner.nextLine().equals("Y");
//			scanner.close();
		}
		return status;
	}

	public Map<String, String> getParametersMap(){
		Map<String, String> parametersMap = new HashMap<String, String>();
		parametersMap.put("11", String.valueOf(noise));
		parametersMap.put("12", String.valueOf(revolution));
		return parametersMap;
	}
	
	public double getErrorProb(){
		double[] paramsErrorProbArr = new double[4];
		paramsErrorProbArr[0] = Conf.getErrorProb(noise, NOISE_STANDARD);
		paramsErrorProbArr[1] = Conf.getErrorProb(revolution, REVOLUTION_STANDARD);
		return ArrayHelper.max(paramsErrorProbArr);
	}
	
}



