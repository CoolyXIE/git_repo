package leetcode.finish;

import junit.framework.TestCase;

public class UglyNumber263Test extends TestCase {
	
	public void testIsUgly() {
		UglyNumber263 ugly = new UglyNumber263();
		assertEquals(true, ugly.isUgly(4));
		assertEquals(false, ugly.isUgly(14));
	}

}
