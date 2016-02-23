package tree;

import java.util.ArrayList;
import java.util.List;
import tree.TreeNode;

/**
 * 树的原型
 * 主要用于构造已定义好的树
 * @author	xieke
 * @version 1.0
 * @since	1.6
 * @see	TreeNode
 */

public class Tree {
	public TreeNode root;
	List<TreeNode> list;
	
	//constructor
	public Tree(Integer val) {
		if (val == null)
			root = null;
		this.root = new TreeNode(val);
		list = new ArrayList<TreeNode>();
		list.add(root);
	}
	
	/**
	 * 从上到下，从左到右，一对一对地插入结点
	 * @param leftVal	左子结点的值，不插入则置为null
	 * @param rightVal	右子结点的值，不插入则置为null
	 */
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

