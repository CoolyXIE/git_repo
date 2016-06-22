package cc.kingsee.dynamo.model;

import java.util.HashMap;
import java.util.Map;

import cc.kingsee.dynamo.Conf;
import cc.kingsee.dynamo.util.ArrayHelper;

public class Climate {
	public static final double[] TEMPERATURE_STANDARD = {-20, 0, 25, 35, 55};
	public static final double[] HUMIDITY_STANDARD = {0, 0.35, 0.5, 0.80, 1.0};
	public static final double[] PRESSURE_STANDARD = {500, 980, 1000, 1050, 1500};
	
	private double temperature;
	private double humidity;
	private double pressure;
	
	public Climate(double temperature, double humidity, double pressure) {
		super();
		this.temperature = temperature;
		this.humidity = humidity;
		this.pressure = pressure;
	}
	
	public void suggest(){
		String badParamString = "";
		if (!Conf.inSafeRange(temperature, TEMPERATURE_STANDARD))
			badParamString += "温度";
		if (!Conf.inSafeRange(humidity, HUMIDITY_STANDARD))
			badParamString += ",湿度";
		if (!Conf.inSafeRange(pressure, PRESSURE_STANDARD))
			badParamString += ",压力";
		
		if (badParamString.isEmpty())
			System.out.println("气象参数正常");
		else 
			System.out.println(badParamString + "比较危险，可能会造成机器故障，请多加以注意！");
	}

	public Map<String, String> getParametersMap(){
		Map<String, String> parametersMap = new HashMap<String, String>();
		parametersMap.put("1", String.valueOf(temperature));
		parametersMap.put("2", String.valueOf(humidity));
		parametersMap.put("3", String.valueOf(pressure));
		return parametersMap;
	}

	public double getErrorProb(){
		double[] paramsErrorProbArr = new double[3];
		paramsErrorProbArr[0] = Conf.getErrorProb(temperature, TEMPERATURE_STANDARD);
		paramsErrorProbArr[1] = Conf.getErrorProb(humidity, HUMIDITY_STANDARD);
		paramsErrorProbArr[2] = Conf.getErrorProb(pressure, PRESSURE_STANDARD);
		return ArrayHelper.max(paramsErrorProbArr);
	}
	
}
