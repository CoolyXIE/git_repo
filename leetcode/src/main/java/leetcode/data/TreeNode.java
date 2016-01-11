package leetcode.data;

public class TreeNode {
	int val;
	TreeNode left;
	TreeNode right;

	//constructor
	public TreeNode() {
		val = 0;
	}
	
	public TreeNode(int x) {
		val = x; 
	}

	public TreeNode(int val, TreeNode left, TreeNode right) {
		super();
		this.val = val;
		this.left = left;
		this.right = right;
	}
	
	//getters & setter
	public int getVal() {
		return val;
	}

	public TreeNode getLeft() {
		return left;
	}

	public TreeNode getRight() {
		return right;
	}

	public void setVal(int val) {
		this.val = val;
	}

	public void setLeft(TreeNode left) {
		this.left = left;
	}

	public void setRight(TreeNode right) {
		this.right = right;
	}

	@Override
	public String toString() {
		String output = "hash: " + this.hashCode() + " val = " + this.val
				+ " left-hash: " + left.hashCode() + " right-hash: " + right.hashCode();
		return output;
	}
	
}
