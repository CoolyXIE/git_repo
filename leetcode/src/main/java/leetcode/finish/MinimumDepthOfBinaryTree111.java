package leetcode.finish;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;

import tree.Tree;
import tree.TreeNode;

public class MinimumDepthOfBinaryTree111 {
	static Map<TreeNode, Integer> treeNodeCountMap = new HashMap<TreeNode, Integer>();
	
	public static int minDepth3(TreeNode root) {
	    if (root == null)
	        return 0;
	    if (root.left != null && root.right != null)
	        return Math.min(minDepth(root.left), minDepth(root.right))+1;
	    else
	        return Math.max(minDepth(root.left), minDepth(root.right))+1;
	}
	/*
	 * 别人算法的高明之处:
	 * 	无需Map存储计数，每次过一个level高度自增
	 *	每次level的size都是下一次再变  
	 */
	public static int minDepth2(TreeNode root) {
	    if(root == null) return 0;
	    int depth = 1;
	    Queue<TreeNode> q = new LinkedList<TreeNode>();
	    q.offer(root);
	    while(!q.isEmpty()){
	        int size = q.size();
	        // for each level
	        for(int i=0;i<size;i++){
	            TreeNode node = q.poll();
	            if(node.left == null && node.right == null){
	                return depth;
	            }
	            if(node.left != null){
	                q.offer(node.left);
	            }
	            if(node.right != null){
	                q.offer(node.right);
	            }
	        }
	        depth++;
	    }
	    return depth;
	}
	
	public static int minDepth(TreeNode root) {
		if (root == null)
			return 0;
		List<TreeNode> list = new ArrayList<TreeNode>();
		list.add(root);
		treeNodeCountMap.put(root, 1);
		while(true){
			TreeNode parent = list.get(0);
			list.remove(0);
			if (parent == null)
				continue;
			int count = treeNodeCountMap.get(parent);
			
			if (parent.left == null && parent.right == null)
				return count;
			else{
				list.add(parent.left);
				treeNodeCountMap.put(parent.left, count+1);
				list.add(parent.right);
				treeNodeCountMap.put(parent.right, count+1);
			}
		}
	}

	public static void main(String[] args) {
		Tree tree = new Tree(3);
		tree.insertPair(9, 20);
		tree.insertPair(null, null);
		tree.insertPair(15, 17);
		long begin = System.currentTimeMillis();
		for (int i = 0; i < 10000; i ++)
			minDepth(tree.root);
		System.out.println(System.currentTimeMillis() - begin);
		begin = System.currentTimeMillis();
		for (int i = 0; i < 10000; i ++)
			minDepth2(tree.root);
		System.out.println(System.currentTimeMillis() - begin);
		begin = System.currentTimeMillis();
		for (int i = 0; i < 10000; i ++)
			minDepth3(tree.root);
		System.out.println(System.currentTimeMillis() - begin);
	}
}
