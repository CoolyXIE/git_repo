package cc.kingsee.dynamo.util;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DateHelper {
	public static SimpleDateFormat shortDateFormat = new SimpleDateFormat("yyyy-MM-dd");
	public static SimpleDateFormat longDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	
	public static String getShortDateString(Date date){
		return shortDateFormat.format(date);
	}
	
	public static String getLongDateString(Date date){
		return longDateFormat.format(date);
	}

	public static Date parseShortDate(String shortDateString) throws ParseException{
		return shortDateFormat.parse(shortDateString);
	}
	
	public static Date parseLongDate(String longDateString) throws ParseException{
		return longDateFormat.parse(longDateString);
	}
	
	public static Date addDays(Date date, int days){
		return new Date(date.getTime() + ((long)days * 24 * 60 * 60 * 1000));
	}
	
	public static Date addHours(Date date, int hours){
		return new Date(date.getTime() + ((long)hours * 60 * 60 * 1000));
	}
	
	public static Date addMinutes(Date date, int minutes){
		return new Date(date.getTime() + ((long)minutes * 60 * 1000));
	}
	
	public static Date addSeconds(Date date, int seconds){
		return new Date(date.getTime() + ((long)seconds * 1000));
	}

	public static void main(String[] args) {
		Date date = new Date();
		System.out.println(DateHelper.getLongDateString(date));
		System.out.println(DateHelper.getLongDateString(DateHelper.addDays(date, 30)));
	}
}
