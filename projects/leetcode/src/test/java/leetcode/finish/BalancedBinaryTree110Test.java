package leetcode.finish;

import junit.framework.TestCase;

public class BalancedBinaryTree110Test extends TestCase {

	public static BalancedBinaryTree110 tree = new BalancedBinaryTree110();
	
	public void testIsBalanced() {
		tree.insert(10);
		tree.insert(7);
		tree.insert(12);
		tree.insert(4);
		tree.insert(8);
		tree.insert(11);
		tree.insert(10);
		
		assertEquals(true, tree.isBalanced(tree.root));
	}
	

}
