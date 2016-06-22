package leetcode.finish;




public class ValidNumber65 {
	
	public static boolean isNumber(String s) {
		
		for (int i = 0; i < s.length(); i ++) {
			if (Character.isLetter(s.charAt(i)) && s.charAt(i) != 'e')
				return false;
		}
		
		try {
			Integer intNum = Integer.parseInt(s);
			System.out.println(intNum + " is a integer number!");
			return true;
		} catch (NumberFormatException e) {
			try {
				Double doubleNum = Double.parseDouble(s);
				System.out.println(doubleNum + " is a double number!");
				return true;
			} catch (NumberFormatException e2) {
				
			}
		}
		
		return false;
    }
	
	public static void main(String[] args) {
	}
}
