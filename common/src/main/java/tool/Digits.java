package tool;

public class Digits {
	private int[] digits;
	private int val;

	public Digits(int n) {
		digits = toDigits(n);
		this.val = n;
	}

	public Digits(int[] digits) {
		super();
		this.digits = digits;
		val = parseInt(digits);
	}
	

	public int[] getDigits() {
		return digits;
	}

	public int getVal() {
		return val;
	}

	@Override
	public String toString() {
		String output ="";
		for (int i = 31; i >= 0; i --)
			output += (digits[i]==0?"0":"1");
		return output;
	}

	public static int[] toDigits(int n) {
		int[] digits = new int[32];
		for (int i = 31; i >= 0; i--)
			digits[i] = (n >> i) % 2;
		return digits;
	}

	public static int parseInt(int[] digits) {
		if (digits[digits.length - 1] != 0)
			return parseNegativeInt(digits);
		else
			return parsePostiveInt(digits);
	}

	private static int parseNegativeInt(int[] digits) {
		int[] digits2 = new int[digits.length];
		boolean flag = true;
		for (int i = 0; i < 31; i++) {
			if (flag) {
				if (digits[i] == 0)
					digits2[i] = 0;
				else {
					digits2[i] = 1;
					flag = false;
				}
			} else
				digits2[i] = (digits[i] == 0) ? 1 : 0;
		}
		if (flag)
			return Integer.MIN_VALUE;
		return -parsePostiveInt(digits2);
	}

	private static int parsePostiveInt(int[] digits) {
		int result = 0;
		for (int i = 31; i >= 0; i--) {
			result = result << 1;
			if (digits[i] != 0)
				result += 1;
		}
		return result;
	}
}
