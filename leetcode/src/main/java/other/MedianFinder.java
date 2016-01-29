//可以优化，中位数只会越来越往后找，前面的数都要舍去的


package other;

import java.util.ArrayList;
import java.util.List;

public class MedianFinder {
	List<Integer> sortNumList;
	int pos = -1;
	
	//constructor
	public MedianFinder() {
		super();
		this.sortNumList = new ArrayList<Integer>();
	}
	
	
	// Adds a number into the data structure.
	//in the same time, update the median value
	
    public void addNum(int num) {
    	if (this.sortNumList.isEmpty()){
    		sortNumList.add(num);
    		this.pos = 0;
    		return ;
    	}
    	
    	int newPos = 0;
        for (Integer sortNum : sortNumList) {
        	if (num <= sortNum) {
        		sortNumList.add(newPos, num);
        		newPos ++;
        		break;
        	} 
        	newPos ++;
        }
        if (num > sortNumList.get(sortNumList.size() -1 ))
        	sortNumList.add(num);
        
		if (sortNumList.size()%2 == 1)
			pos ++;
    }
    
	// Returns the median of current data stream
    public double findMedian() {
    	return (this.sortNumList.size()%2 == 1)?1.0*sortNumList.get(pos):
    			0.5*(sortNumList.get(pos) + sortNumList.get(pos+1));
    }
    public static void main(String[] args) {
	}
    
}
//Your MedianFinder object will be instantiated and called as such:
//MedianFinder mf = new MedianFinder();
//mf.addNum(1);
//mf.findMedian();








