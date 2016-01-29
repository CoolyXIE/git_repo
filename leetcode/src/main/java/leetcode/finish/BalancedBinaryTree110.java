package leetcode.finish;

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
	
	public TreeNode root;
	public boolean isBalanced(TreeNode root) {
		if (root == null)
			return true;
		else if (Math.abs(height(root.left) - height(root.right)) <= 1){
			if (isBalanced(root.left) && isBalanced(root.right))
				return true;
		} 
		return false;
	}

	public int height(TreeNode node){
		if (node == null)
			return 0;
		else {
			return 1 + Math.max(height(node.left), height(node.right));
		}
	}

	public void insert(int val){
		TreeNode newTreeNode = new TreeNode(val);
		if (root == null)
			root = new TreeNode(val);
		else {
			TreeNode current = root;
			TreeNode parent;
			while(true){
				parent = current;
				if (val < parent.val){
					current = current.left; 
					if (current == null){
						parent.left = newTreeNode; 
						return ;
					}
				} else {
					current = current.right;  
					if (current == null){
						parent.right = newTreeNode;
						return ;
					}
				}
			}
		}

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