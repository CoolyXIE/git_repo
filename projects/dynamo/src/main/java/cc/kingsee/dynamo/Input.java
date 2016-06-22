package cc.kingsee.dynamo;

import java.io.IOException;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import cc.kingsee.dynamo.model.Climate;
import cc.kingsee.dynamo.model.Electric;
import cc.kingsee.dynamo.model.Oil;
import cc.kingsee.dynamo.model.Other;
import cc.kingsee.dynamo.util.DateHelper;
import redis.clients.jedis.Jedis;


public class Input {
	public static void main(String[] args) throws IOException, InterruptedException {
		Date date = null;
		try {
			date = DateHelper.parseShortDate(args[0]);
		} catch (Exception e) {
			System.err.println("usage: <short date>");
			System.exit(1);
		}
		Scanner scanner = new Scanner(System.in);
		System.out.println("环境组数据录入，请输入气温(摄氏度)、湿度和压力数据(hPa)，以空格分隔：");
		String[] climateParamArr = scanner.nextLine().split(" ");
		Climate climate = new Climate(
				Double.parseDouble(climateParamArr[0]), 
				Double.parseDouble(climateParamArr[1]), 
				Double.parseDouble(climateParamArr[2]));
		System.out.println("机器因环境出现故障的几率为：" + climate.getErrorProb());
		climate.suggest();
		

		System.out.println("电力组数据录入，请输入电流(A)、电压(V)、功率(kW)和赫兹(Hz)，以空格分隔：");
		String[] electricParamArr = scanner.nextLine().split(" ");

		Electric electric = new Electric(
				Double.parseDouble(electricParamArr[0]), 
				Double.parseDouble(electricParamArr[1]), 
				Double.parseDouble(electricParamArr[2]), 
				Double.parseDouble(electricParamArr[3]));
		System.out.println("机器因电力出现故障的几率为：" + electric.getErrorProb());
		boolean electricStatus = electric.suggest();
		

		System.out.println("机油组数据录入，请输入剩余油量、油压(MPa)和油温(摄氏度)，以空格分隔：");
		String[] oilParamArr = scanner.nextLine().split(" ");
		Oil oil = new Oil(
				Double.parseDouble(oilParamArr[0]), 
				Double.parseDouble(oilParamArr[1]), 
				Double.parseDouble(oilParamArr[2]));
		System.out.println("机器因机油出现故障的几率为：" + oil.getErrorProb());
		boolean oilStatus = oil.suggest();
		
		System.out.println("其他数据录入，请输入噪音(dB)和转数(rpm)，以空格分隔：");
		String[] otherParamArr = scanner.nextLine().split(" ");
		Other other = new Other(
				Double.parseDouble(otherParamArr[0]), 
				Double.parseDouble(otherParamArr[1]));
		System.out.println("机器因其他出现故障的几率为：" + other.getErrorProb());
		boolean otherStatus = other.suggest();
		
		scanner.close();
		System.out.println("数据已录入，结束！");
		System.out.println("综合来说，机器出现故障的概率为：" + Conf.getErrorProb(climate, electric, oil, other));
		
		Map<String, String> parametersMap = new HashMap<String, String>();
		parametersMap.put("0", String.valueOf(electricStatus && oilStatus && otherStatus));
		parametersMap.putAll(climate.getParametersMap());
		parametersMap.putAll(electric.getParametersMap());
		parametersMap.putAll(oil.getParametersMap());
		parametersMap.putAll(other.getParametersMap());
		
		String key = DateHelper.getShortDateString(date);
		Jedis jedis = new Jedis();
		jedis.hmset(key, parametersMap);
		jedis.close();
	}
}
