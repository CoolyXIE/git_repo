package cc.kingsee.dynamo.model;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import cc.kingsee.dynamo.Conf;
import cc.kingsee.dynamo.util.ArrayHelper;

public class Electric {
	public static final double[] CURRENT_STANDARD = {0, 361, 362, 363, 600};
	public static final double[] VOLTAGE_STANDARD = {0, 229, 230, 231, 400};
	public static final double[] POWER_STANDARD = {0, 180, 200, 210, 400};
	public static final double[] HERTZ_STANDARD = {0, 49.9, 50, 50.1, 100};
	
	private double current;
	private double voltage;
	private double power;
	private double hertz;
	
	public Electric(double current, double voltage, double power, double hertz) {
		super();
		this.current = current;
		this.voltage = voltage;
		this.power = power;
		this.hertz = hertz;
	}
	
	public boolean suggest() throws InterruptedException, IOException{
		String badParamString = "";
		if (!Conf.inSafeRange(current, CURRENT_STANDARD))
			badParamString += "电流";
		if (!Conf.inSafeRange(voltage, VOLTAGE_STANDARD))
			badParamString += ",电压";
		if (!Conf.inSafeRange(power, POWER_STANDARD))
			badParamString += ",功率";
		if (!Conf.inSafeRange(hertz, HERTZ_STANDARD))
			badParamString += ",赫兹";
		
		boolean status = true;
		if (badParamString.isEmpty())
			System.out.println("电力参数正常");
		else {
			System.out.println(badParamString + "参数异常，可能会造成机器故障，请即刻前往检查机器状态！");
			Thread.sleep(3000);
			System.out.println("机器是否正常？Y/N");
			status = new Scanner(System.in).nextLine().equals("Y");
		}
		return status;
	}

	public Map<String, String> getParametersMap(){
		Map<String, String> parametersMap = new HashMap<String, String>();
		parametersMap.put("4", String.valueOf(current));
		parametersMap.put("5", String.valueOf(voltage));
		parametersMap.put("6", String.valueOf(power));
		parametersMap.put("7", String.valueOf(hertz));
		return parametersMap;
	}
	
	public double getErrorProb(){
		double[] paramsErrorProbArr = new double[4];
		paramsErrorProbArr[0] = Conf.getErrorProb(current, CURRENT_STANDARD);
		paramsErrorProbArr[1] = Conf.getErrorProb(voltage, VOLTAGE_STANDARD);
		paramsErrorProbArr[2] = Conf.getErrorProb(power, POWER_STANDARD);
		paramsErrorProbArr[3] = Conf.getErrorProb(hertz, HERTZ_STANDARD);
		return ArrayHelper.max(paramsErrorProbArr);
	}
}
