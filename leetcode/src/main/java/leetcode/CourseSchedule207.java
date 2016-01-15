package leetcode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Node2 {
	int courseId;
	Node2 parentNode;
	List<Node2> childrenNodes = new ArrayList<Node2>();

	public Node2(int courseId, Node2 parentNode) {
		super();
		this.courseId = courseId;
		this.parentNode = parentNode;
	}

	public static boolean setChildTree(Node2 pNode, int[][] pre) {
		List<Integer> cidListHasPre = new ArrayList<Integer>();
		int[] preCoursesId = null;
		System.out.print("set course: " + pNode.courseId + "\t preCourses:");
		for (int i = 0; i < pre.length; i++) {
			cidListHasPre.add(pre[i][0]);
			if (pre[i][0] == pNode.courseId) {
				preCoursesId = pre[i]; // first is itself id
				System.out.print("\t" + Arrays.toString(pre[i]));
			}
		}
		System.out.println();

		for (int i = 1; i < preCoursesId.length; i++) {
			Node2 cNode = new Node2(preCoursesId[i], pNode);
			System.out.println("cNode: " + cNode);
			List<Integer> list = new ArrayList<Integer>();
			for (Node2 node : pNode.getAncestorNodes())
				list.add(node.courseId);
			System.out.println("ancestorNodes:" + list);
			if (list.contains(cNode.courseId)){
				System.err.println("ERROE: " + cNode + "==>" + pNode + "==>"+ cNode);
				return false;
			}
			if (cidListHasPre.contains(cNode.courseId)) {
				if (!setChildTree(cNode, pre))
					return false; 
			} else {
				cNode.childrenNodes = null;
			}
			pNode.addChildNode(cNode);
		}
		
		return true;
	}

	@Override
	public String toString() {
		return String.valueOf(courseId);
	}

	public List<Node2> getAncestorNodes() {
		List<Node2> ancestorNodes = new ArrayList<Node2>();
		ancestorNodes.add(this);
		Node2 pNode = this.parentNode;
		if (pNode == null)
			return ancestorNodes;
		else
			ancestorNodes.addAll(pNode.getAncestorNodes());
		return ancestorNodes;
	}

	public void setParentNode(Node2 parentNode) {
		this.parentNode = parentNode;
	}

	public void addChildNode(Node2 node) {
		if (this.childrenNodes == null) {
			this.childrenNodes = new ArrayList<Node2>();
		}
		this.childrenNodes.add(node);
	}

	public void setChildrenNodes(List<Node2> childrenNodes) {
		this.childrenNodes = childrenNodes;
	}

}

public class CourseSchedule207 {

	public static void main(String[] args) {
		int[][] pre = { { 0, 1, 2, 3 }, { 1, 5, 4 }, { 2, 4 }, { 3, 4 }, { 4, 1 },
				{ 5, 6 } };
		System.out.println(canFinish(7, pre));
	}

	public static boolean canFinish(int numCourses, int[][] prerequisites) 
	{
		Node2 node1 = new Node2(0, null);
		return Node2.setChildTree(node1, prerequisites);
	}
}
