package tree;


public class TreeNode {
	int index;
	double val;
	TreeNode left ;
	TreeNode right ;

	//constructor
	public TreeNode(int index, double val){
		this.index = index;
		this.val = val;
	}
	
	public TreeNode(double val){
		this(0, val);
	}
	
	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return super.toString();
	}
	
}
