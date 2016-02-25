package hadoop;
import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class WordCount {
	public static class TokenizerMapper
	extends Mapper<Object, Text, Text, IntWritable>{
		private final static IntWritable one = new IntWritable(1);
		private Text word = new Text();
		/*
		 * LongWritable 为输入的key的类型
		 * Text 为输入value的类型
		 * Text-IntWritable 为输出key-value键值对的类型
		 */
		public void map(Object key, Text value, Context context
				) throws IOException, InterruptedException {
			StringTokenizer itr = new StringTokenizer(value.toString());  // 将TextInputFormat生成的键值对转换成字符串类型
			while (itr.hasMoreTokens()) {
				word.set(itr.nextToken());
				context.write(word, one);
			}
		}
	}
	
	public static class IntSumReducer
	extends Reducer<Text,IntWritable,Text,IntWritable> {
		private IntWritable result = new IntWritable();
		/*
		 * Text-IntWritable 来自map的输入key-value键值对的类型
		 * Text-IntWritable 输出key-value 单词-词频键值对
		 */
		public void reduce(Text key, Iterable<IntWritable> values,
				Context context
				) throws IOException, InterruptedException {
			int sum = 0;
			for (IntWritable val : values) {
				sum += val.get();
			}
			result.set(sum);
			context.write(key, result);
		}
	}
	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration();  // job的配置
		Job job = new Job(conf, "word count");  // 初始化Job
		job.setJarByClass(WordCount.class);
		job.setMapperClass(TokenizerMapper.class);
		job.setCombinerClass(IntSumReducer.class);
		job.setReducerClass(IntSumReducer.class);  
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		FileInputFormat.addInputPath(job, new Path(args[0]));  // 设置输入路径
		FileOutputFormat.setOutputPath(job, new Path(args[1]));  // 设置输出路径
		System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
}