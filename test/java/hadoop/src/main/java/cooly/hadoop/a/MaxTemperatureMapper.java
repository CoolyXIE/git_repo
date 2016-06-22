package cooly.hadoop.a;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;
import org.apache.hadoop.mapreduce.Mapper;


public class MaxTemperatureMapper extends Mapper<LongWritable, Text, Text, IntWritable> {
	public void map(LongWritable key, Text value, OutputCollector<Text, IntWritable> output,
			Reporter reporter) throws IOException, InterruptedException {
		String line = value.toString();
		String year = line.substring(15,  19);  //从行中抽取出年份
		int airTemperature = Integer.parseInt(line.substring(87,92)); //抽取温度
		output.collect(new Text(year), new IntWritable(airTemperature));
	}
}
