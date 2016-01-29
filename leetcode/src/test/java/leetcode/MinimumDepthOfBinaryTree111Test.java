package leetcode;

import tree.Tree;
import junit.framework.TestCase;
import leetcode.finish.MinimumDepthOfBinaryTree111;

public class MinimumDepthOfBinaryTree111Test extends TestCase {
	MinimumDepthOfBinaryTree111 tree = new MinimumDepthOfBinaryTree111();
	
	public void testMinDepth() {
		Tree tree = new Tree(3);
		tree.insertPair(9, 20);
		tree.insertPair(null, null);
		tree.insertPair(15, 17);
		
		assertEquals(2, this.tree.minDepth(tree.root));
	}

}
