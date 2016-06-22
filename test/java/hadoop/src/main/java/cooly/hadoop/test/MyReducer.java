package cooly.hadoop.test;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class MyReducer extends Reducer {

	protected void reduce(LongWritable key, Iterable<Text> value,Context context)
			throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		int sum = 0;
		for(Text val: value){
			sum += Integer.parseInt(val.toString());
		}
		Text write_key = new Text();
		IntWritable write_value = new IntWritable();
		if(key.get() == 0)
			write_key.set("odd:");
		else 
			write_key.set("even:");
		write_value.set(sum);
		context.write(write_key, write_value);
	}

}