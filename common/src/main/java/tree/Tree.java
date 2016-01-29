package tree;


import java.util.ArrayList;
import java.util.List;

import tree.TreeNode;


public class Tree {
	public TreeNode root;
	List<TreeNode> list;
	
	public Tree(Integer val) {
		if (val == null)
			root = null;
		this.root = new TreeNode(val);
		list = new ArrayList<TreeNode>();
		list.add(root);
	}
	
	public void insertPair(Integer leftVal, Integer rightVal){
		TreeNode parent = list.get(0);
		list.remove(0);
		if (leftVal != null){
			parent.left = new TreeNode(leftVal);
			list.add(parent.left);
		}
		if (rightVal != null){
			parent.right = new TreeNode(rightVal);
			list.add(parent.right);
		}
	}
}

