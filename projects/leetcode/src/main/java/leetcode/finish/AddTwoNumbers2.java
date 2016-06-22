package leetcode.finish;

public class AddTwoNumbers2 {
	public static class ListNode{
		int val;
		ListNode next = null ;
		
		public ListNode(int x) {
			val = x;
		}
		
		@Override
		public String toString() {
			if (next == null)
				return Integer.toString(val);
			else 
				return val + " -> " + next.toString();
		}
		
		public static ListNode parse(String nodeString) {
			String[] nodeValArr = nodeString.split(" -> ");
			ListNode[] listNodeArr = new ListNode[nodeValArr.length];
			for (int i = 0; i < nodeValArr.length; i ++) {
				listNodeArr[i] = new ListNode(Integer.parseInt(nodeValArr[i]));
			}
			for (int i = listNodeArr.length -1; i > 0; i --) 
				listNodeArr[i-1].next = listNodeArr[i];
			
			return listNodeArr[0];
		}
	}

	public static ListNode myAddTwoNumbers(ListNode l1, ListNode l2) {
		String nodeString = "";
		boolean add = false;
		
		while (l1 != null && l2 != null) {
			int val = l1.val + l2.val;
			if (add) 
				val += 1;
			if (val >= 10) {
				add = true;
				val = val -10;
			}
			else
				add = false;
			
			l1 = l1.next;
			l2 = l2.next;
			nodeString += val + " -> ";
			
			if (l1 == null && l2 == null && add)
				nodeString += "1";
		}
		if (!nodeString.substring(nodeString.length() - 1, nodeString.length()).equals("1")) 
			nodeString = nodeString.substring(0, nodeString.length() - 4);
		ListNode l3 = ListNode.parse(nodeString);
		return l3;
	}
	
	public static ListNode hisAddTwoNumbers1(ListNode l1, ListNode l2) {
		ListNode c1 = l1;
		ListNode c2 = l2;
		ListNode sentinel = new ListNode(0);
		ListNode d = sentinel;
		int sum = 0;
		while (c1 != null || c2 != null) {
			sum /= 10;
			if (c1 != null) {
				sum += c1.val;
				c1 = c1.next;
			}
			if (c2 != null) {
				sum += c2.val;
				c2 = c2.next;
			}
			d.next = new ListNode(sum % 10);
			d = d.next;
		}
		if (sum / 10 == 1)
			d.next = new ListNode(1);
		return sentinel.next;
	}
	
	public static void main(String[] args) {
		ListNode l1 = new ListNode(9);
		l1.next = new ListNode(9);
		l1.next.next = new ListNode(9);
		ListNode l2 = new ListNode(9);
		l2.next = new ListNode(9);
		l2.next.next = new ListNode(9);
		System.out.println("listNode-1: " + l1);
		System.out.println("listNode-2: " + l2 + "\n");
		
		long start = System.currentTimeMillis();
		ListNode l3 = myAddTwoNumbers(l1, l2);
		long t1 = System.currentTimeMillis() - start;
		start = System.currentTimeMillis();
		ListNode l4 = hisAddTwoNumbers1(l1, l2);
		long t2 = System.currentTimeMillis() - start;
		System.out.println("my: " + l3 + "\ttime:" + t1);
		System.out.println("his: " + l4 + "\ttime: " + t2) ;
	}
}
