package tree;

public class TreeNode {
	public int val;
	public TreeNode left ;
	public TreeNode right ;

	//constructor
	public TreeNode(int val){
		this.val = val;
	}
	
	public boolean isNullLeft(){
		return (left==null)?true:false;
	}
	public boolean isNullRight(){
		return (right==null)?true:false;
	}
	
	@Override
	public String toString() {
		String l = (isNullLeft())?"null":String.valueOf(left.val);
		String r = (isNullRight())?"null":String.valueOf(right.val);
		return "val:"+val+"\t" + l + ","+ r;
	}
	
}
