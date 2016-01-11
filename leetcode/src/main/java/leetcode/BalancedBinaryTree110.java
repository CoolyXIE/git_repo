package leetcode;

public class BalancedBinaryTree110 {
	/*
	 * Given a binary tree, 
	 * determine if it is height-balanced.
	 * 
	 * For this problem, 
	 * a height-balanced binary tree 
	 * is defined as a binary tree 
	 * in which the depth of the two subtrees 
	 * of every node never differ by more than 1.
	 */






	public boolean isBalanced(TreeNode root) {

		return false;
	}
	
	
	public static void main(String[] args) {
		TreeNode node1 = new TreeNode(10);
		TreeNode node2 = new TreeNode(20);
		TreeNode node3 = new TreeNode(30);
		node1.setLeft(node2);
		node1.setRight(node3);
		System.out.println(node1);
	}
}

/**
 * Definition for a binary tree node.
 */
class TreeNode {
	int val;
	TreeNode left;
	TreeNode right;
	TreeNode(int x) {
		val = x; 
	}

	@Override
	public String toString() {
		return val + " left: " + left + "\t" + "right: " + right;
	}

	public void setLeft(TreeNode left) {
		this.left = left;
	}

	public void setRight(TreeNode right) {
		this.right = right;
	}

}