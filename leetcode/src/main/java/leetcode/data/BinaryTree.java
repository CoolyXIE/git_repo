package leetcode.data;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BinaryTree {
	private TreeNode root;


	//constructor
	public BinaryTree(int[] vals) {
		super();
		buildTree(vals);
	}

	//build a tree by order of values given
	public void buildTree(int[] vals) {
		int len = vals.length;



		Map<Integer, List<Integer>> depthIndexMap = new HashMap<Integer, List<Integer>>();
		int depth = 0;
		for (int i = 0; i < len; i ++){
			if (i < Math.pow(2, depth + 1) - 1){
				List<Integer> indexs = new ArrayList<Integer>();
				indexs.add(i);
				if (depthIndexMap.containsKey(depth))
					depthIndexMap.get(depth).addAll(indexs);
				else
					depthIndexMap.put(depth, indexs);
			} else {
				depth ++;
				List<Integer> indexs = new ArrayList<Integer>();
				indexs.add(i);
				if (depthIndexMap.containsKey(depth))
					depthIndexMap.get(depth).addAll(indexs);
				else
					depthIndexMap.put(depth, indexs);
			}
		}
		
		this.root = new TreeNode(vals[0]);
		List<TreeNode> roots = Arrays.asList(root);
		
		for (int h = 0; h < depth; h ++){
			List<Integer> nodeIndexs = depthIndexMap.get(depth);
			for (int i = 0; i < nodeIndexs.size(); i += 2){
				roots.get(0).left = new TreeNode(vals[nodeIndexs.get(i)]);
				roots.add(roots.get(0).left);
				if (i + 1 < nodeIndexs.size()){
					roots.get(0).right = new TreeNode(vals[nodeIndexs.get(i+1)]);
					roots.add(roots.get(0).left);
				}
				roots.remove(0);
			}
		}	
	}

	//getter
	public TreeNode getRoot() {
		return root;
	}
	
	//display a tree
	@Override
	public String toString() {
		return root.getVal() + "\t" + root.getLeft().getVal() + "\t" + root.getRight().getVal();
	}
	
	
	public static void main(String[] args) {
		int[] vals = {1,2,3,4,5,6,7,8,9};
		BinaryTree tree = new BinaryTree(vals);
		System.out.println(tree.getRoot().getLeft().getLeft().getVal());
	}	
}
