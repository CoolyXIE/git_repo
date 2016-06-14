package tree;

/**
 * 树的结点
 * @author	xieke
 * @version	1.0
 * @since	1.6
 * @see	Tree
 * 
 */
public class TreeNode {
	public int val;
	public TreeNode left ;
	public TreeNode right ;

	//constructor
	public TreeNode(int val){
		this.val = val;
	}
	
	/**
	 * 判断该结点是否有左孩子结点
	 * @return 布尔值，左孩子结点为空则返回True，否则返回False
	 */
	public boolean isNullLeft(){
		return (left==null)?true:false;
	}
	
	/**
	 * 判断该结点是否有右孩子结点
	 * @return 布尔值，右孩子结点为空则返回True，否则返回False
	 */
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
