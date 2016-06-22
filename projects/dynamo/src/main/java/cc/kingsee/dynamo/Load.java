package cc.kingsee.dynamo;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import cc.kingsee.dynamo.util.DateHelper;
import redis.clients.jedis.Jedis;

/*
 * 生成指定数字的N条安全记录，存入Redis内存数据库
 */
public class Load {
	public static void load(int num){
		Jedis jedis = new Jedis();
		Date date = DateHelper.addDays(new Date(), 1 - num);
		for(int i = 0; i < num; i ++){
			double[] paramArr = Conf.generateOneRandRecord();
			Map<String, String> parametersMap = new HashMap<String, String>();
			for(int j = 0; j < paramArr.length; j ++)
				parametersMap.put((j + 1) + "", String.valueOf(paramArr[j]));
			parametersMap.put("0", String.valueOf(true));
			String key = DateHelper.getShortDateString(date);
			date = DateHelper.addDays(date, 1);
			jedis.hmset(key, parametersMap);
		}
		jedis.close();
	}
	
	public static void main(String[] args) {
		int num = 0;
		try {
			num = Integer.parseInt(args[0]);
		} catch (Exception e) {
			System.err.println("usage: <num of records>");
			System.exit(1);
		}
		load(num);
		System.exit(0);
	}
}
