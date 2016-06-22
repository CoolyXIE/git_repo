package cc.kingsee.dynamo.model;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import cc.kingsee.dynamo.Conf;
import cc.kingsee.dynamo.util.ArrayHelper;

public class Oil {
	public static final double[] VOLUME_STANDARD = {0, 0.2, 0.8, 1, 1};
	public static final double[] PRESSURE_STANDARD = {0, 0.2, 0.8, 1.0, 1.0};
	public static final double[] TEMPERATURE_STANDARD = {15, 25, 38, 55, 80};
	
	private double volume;
	private double pressure;
	private double temperature;
	
	
	public Oil(double volume, double pressure, double temperature) {
		super();
		this.volume = volume;
		this.pressure = pressure;
		this.temperature = temperature;
	}


	public boolean suggest() throws InterruptedException, IOException{
		String badParamString = "";
		if (!Conf.inSafeRange(volume, VOLUME_STANDARD))
			System.out.println("剩余油量偏低，请添加！");
		if (!Conf.inSafeRange(pressure, PRESSURE_STANDARD))
			badParamString += "油压";
		if (!Conf.inSafeRange(temperature, TEMPERATURE_STANDARD))
			badParamString += ",油温";
			
		boolean status = true;
		if (badParamString.isEmpty())
			System.out.println("机油参数正常");
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
		parametersMap.put("8", String.valueOf(volume));
		parametersMap.put("9", String.valueOf(pressure));
		parametersMap.put("10", String.valueOf(temperature));
		return parametersMap;
	}
	
	
	public double getErrorProb(){
		double[] paramsErrorProbArr = new double[4];
		paramsErrorProbArr[0] = Conf.getErrorProb(volume, VOLUME_STANDARD);
		paramsErrorProbArr[1] = Conf.getErrorProb(pressure, PRESSURE_STANDARD);
		paramsErrorProbArr[2] = Conf.getErrorProb(temperature, TEMPERATURE_STANDARD);
		return ArrayHelper.max(paramsErrorProbArr);
	}
	
	
	
}
