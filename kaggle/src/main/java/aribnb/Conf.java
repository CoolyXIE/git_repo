package aribnb;

import java.text.ParseException;
import java.text.SimpleDateFormat;

public class Conf {
	static final String BASIC_DIR = "E:/data/kaggle/airbnb/";
	
	static SimpleDateFormat shortDateFormat = new SimpleDateFormat("yyyy/MM/dd");
	static SimpleDateFormat longDateFormat = new SimpleDateFormat("yyyyMMddhhmmss");
	
	public static void main(String[] args) throws ParseException {
		System.out.println(longDateFormat.parse("20151106102223"));
	}
	
}
