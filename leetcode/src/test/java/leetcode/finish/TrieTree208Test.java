package leetcode.finish;

import junit.framework.TestCase;

public class TrieTree208Test extends TestCase {
	private static TrieTree208 tree = new TrieTree208();
	

	public void testSearch() {
		tree.insert("happy");
		assertEquals('a', tree.root.children['h'-97].children['a'-97].letter);
		assertEquals('p', tree.root.children['h'-97].children['a'-97].children['p'-97].letter);

		assertEquals(true, tree.search("happy"));
		
		assertEquals(true, tree.startsWith("happy"));
//		
		tree.insert("cooly");
		tree.insert("coo");
		
		assertEquals(true, tree.startsWith("c"));
//		tree.insert("google");
//		
		assertEquals(true, tree.search("coo"));
	}

}
