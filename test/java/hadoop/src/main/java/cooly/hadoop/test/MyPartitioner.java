package cooly.hadoop.test;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Partitioner;

public class MyPartitioner extends Partitioner {

	public int getPartition(LongWritable key, Text value, int numPartitions) {
		// TODO Auto-generated method stub
		if(key.get() % 2 == 0){
			key.set(1);
			return 1;
		}
		else {
			key.set(0);
			return 0;
		}
	}

	@Override
	public int getPartition(Object arg0, Object arg1, int arg2) {
		// TODO Auto-generated method stub
		return 0;
	}

}