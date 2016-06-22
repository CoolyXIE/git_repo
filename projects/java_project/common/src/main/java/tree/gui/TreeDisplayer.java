//package tree.gui;
//
//import java.awt.Graphics;
//
//import javax.swing.JPanel;
//
//import tree.TreeNode;
//
//
//
//public class TreeDisplayer extends JPanel{
//		private static final long serialVersionUID = 1L;
//		
//		private TreeNode root;
//		private int radius;
//		private int vGap;
//		
//		public TreeDisplayer(TreeNode root, int radius, int vGap) {
//			super();
//			this.root = root;
//			this.radius = radius;
//			this.vGap = vGap;
//		}
//		
//		public TreeDisplayer(TreeNode root){
//			this(root, 20, 50);
//		}
//
//		public void paintComponent(Graphics g){
//			if (root != null) {
//				diaplay(g , root, getWidth()/2,30,getWidth()/4);
//			}
//		}
//		
//		@SuppressWarnings("rawtypes")
//		private void diaplay(Graphics g, TreeNode root, int x, int y, int hGap) {
//			// TODO Auto-generated method stub
//			g.drawOval(x-radius, y-radius, 2*radius,  2*radius);
//			g.drawString(root.val+"", x-6, y+4);
//			if(root.left!=null){
//				connectLeftChild(g,x-hGap,y+vGap,x,y);
//				diaplay(g, root.left, x-hGap, y+vGap, hGap/2);
//			}
//			if (root.right!=null) {
//				connectRightChild(g,x+hGap,y+vGap,x,y);
//				diaplay(g, root.right, x+hGap, y+vGap, hGap/2);
//			}
//		}
//
//		private void connectRightChild(Graphics g, int x1, int y1, int x2, int y2) {
//			// TODO Auto-generated method stub
//			double d=Math.sqrt(vGap*vGap+(x2-x1)*(x2-x1));
//			int x11=(int)(x1-radius*(x1-x2)/d);
//			int y11=(int)(y1-radius*vGap/d);
//			int x21=(int)(x2+radius*(x1-x2)/d);
//			int y21=(int)(y2+radius*vGap/d);
//			g.drawLine(x11, y11, x21, y21);
//		}
//
//		private void connectLeftChild(Graphics g, int x1, int y1, int x2, int y2) {
//			// TODO Auto-generated method stub
//			double d=Math.sqrt(vGap*vGap+(x2-x1)*(x2-x1));
//			int x11=(int)(x1+radius*(x2-x1)/d);
//			int y11=(int)(y1-radius*vGap/d);
//			int x21=(int)(x2-radius*(x2-x1)/d);
//			int y21=(int)(y2+radius*vGap/d);
//			g.drawLine(x11, y11, x21, y21);
//		}
//	}