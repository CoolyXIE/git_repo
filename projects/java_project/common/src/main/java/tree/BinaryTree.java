//package tree;
//
//import java.util.HashMap;
//import java.util.Map;
//import java.util.Map.Entry;
//
//
//public class BinaryTree
//{
//	TreeNode root;
//	Map<Integer, Double> indexValMap; //不会有重复的val
//	
//	//constructor
//	public BinaryTree(){
//		this.indexValMap = new HashMap<Integer, Double>();
//	}
//	
//	public BinaryTree(double rootVal){
//		this();
//		this.root = new TreeNode(rootVal);
//	}
//	
//	public BinaryTree(TreeNode root){
//		this();
//		this.root = root;
//	}
//
//	//method
//	public boolean isEmpty(){
//		return (root == null);
//	}
//	
//	public int height(){
//		return height(root);
//	}
//	
//	private int height(TreeNode subNode){
//		if (subNode == null)
//			return 0;
//		else {
//			return 1 + Math.max(height(subNode.left), height(subNode.right));
//		}
//	}
//	
//	public int size(){
//		return size(root);
//	}
//	
//	private int size(TreeNode subNode) {
//		if (subNode == null)
//			return 0;
//		else 
//			return 1 + size(subNode.left) + size(subNode.right);
//	}
//
//	public void insert(int index, double val){
//		indexValMap.put(index, val); //exception index?
//		TreeNode newTreeNode = new TreeNode(index, val);
//		if (root == null)
//			root = new TreeNode(index, val);
//		else {
//			TreeNode current = root;
//			TreeNode parent;
//			while(true){
//				parent = current;
//				if (val < parent.val){
//					current = current.left; 
//					if (current == null){
////						current = newTreeNode  //why it doesn't work
//						parent.left = newTreeNode; 
//						return ;
//					}
//				} else {
//					current = current.right;  
//					if (current == null){
//						parent.right = newTreeNode;
//						return ;
//					}
//				}
//			}
//		}
//
//	}
//	
//	public int indexOf(double val){
//		for(Entry<Integer, Double> entry:indexValMap.entrySet()){
//			if (entry.getValue() == val)
//				return entry.getKey();
//		}
//		return -1;
////		TreeNode current = root;
////		while(current != null){
////			if (current.val == val)
////				return current.index;
////			else if (current.val > val) {
////				current = current.left;
////			} else {
////				current = current.right;
////			}
////		}
////		return -1;
//	}
//	
//	public void delete(){
//		
//	}
//	
//	public static void main(String[] args) {
//		BinaryTree tree = new BinaryTree();
//		/*			 10
//		 * 		   /    \
//		 * 		  07    12
//		 * 	     / \   /
//		 *		4  8  11
//		 */
//		tree.insert(1, 10);
//		tree.insert(2, 7);
//		tree.insert(3, 12);
//		tree.insert(4, 4);
//		tree.insert(5, 8);
//		tree.insert(6, 11);
//		
//		
//	}
//
//
//	public void displayTreeGUI() {
//		// TODO Auto-generated method stub
//	}
//
//
//
//	
//	
//	
////	public void displayTree(){
////		List<TreeNode> childrens = new ArrayList<TreeNode>();
////		List<TreeNode> currents = new ArrayList<TreeNode>();
////		
////		Map<Integer, List<Float>> lineTreeNodesMap = new HashMap<Integer, List<Float>>();
////		currents.add(root);
////		int lineNum = 0;
////		while(!currents.isEmpty()){
////			List<Float> LineTreeNodes = new ArrayList<Float>();
////			for(TreeNode current : currents){
////				LineTreeNodes.add(current.val);
////				if (current.left != null)
////					childrens.add(current.left);
////				if (current.right != null)
////					childrens.add(current.right);
////			}
////			lineTreeNodesMap.put(lineNum++, LineTreeNodes);
////			currents = new ArrayList<TreeNode>(childrens);
////			childrens.clear();
////		}
////		
////		System.out.println(lineTreeNodesMap);
////	}
//}
