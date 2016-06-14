package util;

import java.util.regex.Pattern;

public class Regex {
	/**
	 * 匹配19，20开头年份的日期，考虑到了每个月天数的不同，但没有考虑闰年
	 */
	public static final Pattern datePattern = Pattern.compile("(19|20)\\d{2}-((0?2-(0?[1-9]|1\\d|2[0-8]))|(0?[469]|11)-(0?[1-9]|[12]\\d|30)|(0?[13578]|1[02])-(0?[1-9]|[12]\\d|3[01]))");

}
