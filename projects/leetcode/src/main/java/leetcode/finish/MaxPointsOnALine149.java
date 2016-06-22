package leetcode.finish;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
public class MaxPointsOnALine149 {
	 static class Point {
	      int x;
	      int y;
	      Point() { x = 0; y = 0; }
	      Point(int a, int b) { x = a; y = b; }
	      Point(String withoutBracket){
	    	  x = Integer.parseInt(withoutBracket.split(",")[0]);
	    	  y = Integer.parseInt(withoutBracket.split(",")[1]);
	      }
	      @Override
	      public String toString(){
	    	  return "(" + x + "," + y + ")";
	      }
	  }
	 
	 public static boolean isColinear(Point p1, Point p2, Point p3){
		 return (p1.x-p2.x)*(p2.y-p3.y) - (p1.y-p2.y)*(p2.x-p3.x) == 0?true:false;
	 }

	 public static int getMaxPointsOnALine(Point[] points){
		 if (points.length <= 2 || onlyOnePoint(points))
			 return points.length;
		 
		 
		 int maxPointsOnALine = 2;
		 @SuppressWarnings("unused")
		List<Integer> maxIndexListOnALine = null;
//		 List<Point> maxPointsListOnALine = new ArrayList<Point>();
		 List<Point> pointList = Arrays.asList(points);
		 for (int index1 = 0; index1 < pointList.size() -1 ; index1 ++){
			 Point p1 = pointList.get(index1);
			 for (int index2 = index1 + 1; index2 < pointList.size(); index2 ++){
				 Point p2 = pointList.get(index2);
				 if (p1.x == p2.x && p1.y == p2.y)
					 continue;
				 List<Integer> indexListThisLine = new ArrayList<Integer>(Arrays.asList(index1, index2));
				 for (int index3 = 0; index3 < pointList.size(); index3 ++){
					 Point p3 = pointList.get(index3);
					 if ((p1.x-p2.x)*(p2.y-p3.y) - (p1.y-p2.y)*(p2.x-p3.x) == 0
							 && index1 != index3 && index2 != index3){
						 indexListThisLine.add(index3);
					 }
				 }
				 if (indexListThisLine.size() > maxPointsOnALine){
					 maxPointsOnALine = indexListThisLine.size();
					 maxIndexListOnALine = indexListThisLine;
				 }
			 }
		 }
		 return maxPointsOnALine;
	 }
	 
	 private static boolean onlyOnePoint(Point[] points) {
		 for (int i = 1; i < points.length ; i ++){
			 if (points[i].x != points[0].x || points[i].y != points[0].y)
				 return false;
		 }
		return true;
	}

	 
	 public static int maxPoints(Point[] points) {
	    	int finalX = 0;
	    	int finalY = 0;
//	    	Map<Integer, Integer> finalMap = new HashMap<Integer, Integer>();
	        if (points==null) return 0;
	        if (points.length<=2) return points.length;
	        Map<Integer,Map<Integer,Integer>> map = new HashMap<Integer,Map<Integer,Integer>>();
	        int result=0;
	        for (int i=0;i<points.length;i++){ 
	            map.clear();
	            int overlap=0,max=0;
	            for (int j=i+1;j<points.length;j++){
	                int x=points[j].x-points[i].x;
	                int y=points[j].y-points[i].y;
	                if (x==0&&y==0){
	                    overlap++;
	                    continue;
	                }
	                int gcd=generateGCD(x,y);
	                if (gcd!=0){
	                    x/=gcd;
	                    y/=gcd;
	                }
	                if (x == -5 && y == 53){
	                	System.out.println(i + "\t" + j + "\t" + overlap);
	                }
	                
	                if (map.containsKey(x)){
	                    if (map.get(x).containsKey(y)){
	                        map.get(x).put(y, map.get(x).get(y)+1);
	                    }else{
	                        map.get(x).put(y, 1);
	                    }                       
	                }else{
	                    Map<Integer,Integer> m = new HashMap<Integer,Integer>();
	                    m.put(y, 1);
	                    map.put(x, m);
	                }
	                
	                if (map.get(x).get(y) > max){
	                	max = map.get(x).get(y);
	                	finalX = x;
	                	finalY = y;
	                }
	                	
	            }
	            result=Math.max(result, max+overlap+1);
	        }
	    	System.out.println(finalX + "\t" + finalY);
	        return result;


	    }
	    public static int generateGCD(int a,int b){
	        if (b==0) return a;
	        else return generateGCD(b,a%b);

	    }
	public static void main(String[] args) {
//		 String inputLine = "[[40,-23],[9,138],[429,115],[50,-17],[-3,80],[-10,33],[5,-21],[-3,80],[-6,-65],[-18,26],[-6,-65],[5,72],[0,77],[-9,86],[10,-2],[-8,85],[21,130],[18,-6],[-18,26],[-1,-15],[10,-2],[8,69],[-4,63],[0,3],[-4,40],[-7,84],[-8,7],[30,154],[16,-5],[6,90],[18,-6],[5,77],[-4,77],[7,-13],[-1,-45],[16,-5],[-9,86],[-16,11],[-7,84],[1,76],[3,77],[10,67],[1,-37],[-10,-81],[4,-11],[-20,13],[-10,77],[6,-17],[-27,2],[-10,-81],[10,-1],[-9,1],[-8,43],[2,2],[2,-21],[3,82],[8,-1],[10,-1],[-9,1],[-12,42],[16,-5],[-5,-61],[20,-7],[9,-35],[10,6],[12,106],[5,-21],[-5,82],[6,71],[-15,34],[-10,87],[-14,-12],[12,106],[-5,82],[-46,-45],[-4,63],[16,-5],[4,1],[-3,-53],[0,-17],[9,98],[-18,26],[-9,86],[2,77],[-2,-49],[1,76],[-3,-38],[-8,7],[-17,-37],[5,72],[10,-37],[-4,-57],[-3,-53],[3,74],[-3,-11],[-8,7],[1,88],[-12,42],[1,-37],[2,77],[-6,77],[5,72],[-4,-57],[-18,-33],[-12,42],[-9,86],[2,77],[-8,77],[-3,77],[9,-42],[16,41],[-29,-37],[0,-41],[-21,18],[-27,-34],[0,77],[3,74],[-7,-69],[-21,18],[27,146],[-20,13],[21,130],[-6,-65],[14,-4],[0,3],[9,-5],[6,-29],[-2,73],[-1,-15],[1,76],[-4,77],[6,-29]]";
		 String inputLine2 = "[[1,1],[1,1],[1,1]]";
		 String[] pointStrArr = inputLine2.split("]");
		 Point[] originPoints = new Point[pointStrArr.length];
		 for (int i = 0; i < pointStrArr.length; i ++){
			 originPoints[i] = new Point(pointStrArr[i].substring(2));
		 }
		 System.out.println(getMaxPointsOnALine(originPoints));
	}
	 
}

