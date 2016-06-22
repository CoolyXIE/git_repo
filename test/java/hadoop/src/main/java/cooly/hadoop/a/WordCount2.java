package cooly.hadoop.a;

import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

/**
 * 笔记
 * 
 * 新版API vs. 旧版API
 * 
 * 新版pacakge: org.apache.hadoop.mapreduce
 * 旧版package: org.apache.hadoop.mapred
 * 
 * 新版API使用的是虚类，旧版APi使用的是接口
 * 
 * @author Cooly
 *
 */

public class WordCount2 {
	//Mapper类
	public static class WordCountMap extends Mapper<LongWritable, Text, Text, IntWritable> {
		private final IntWritable one = new IntWritable(1);
		private Text word = new Text();
		//map函数
		/*
		 * @see org.apache.hadoop.mapreduce.Mapper#map(KEYIN, VALUEIN, org.apache.hadoop.mapreduce.Mapper.Context)
		 * 笔记 
		 * public void map(Object key, Text value, Context context) throws IOException, InterruptedException {}
		 * 
		 * context是用来记录输出的key的value, 语法为context.write(key, value)
		 */
		public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
			String line = value.toString();
			StringTokenizer token = new StringTokenizer(line);
			while (token.hasMoreTokens()) {
				word.set(token.nextToken());
				context.write(word, one);
			}
		}
	}

	//Reducer类
	public static class WordCountReduce extends Reducer<Text, IntWritable, Text, IntWritable> {
		//reduce函数
		/*
		 * @see org.apache.hadoop.mapreduce.Reducer#reduce(KEYIN, java.lang.Iterable, org.apache.hadoop.mapreduce.Reducer.Context)
		 */
		public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
			int sum = 0;
			//values是以迭代器的形式给出的
			for (IntWritable val : values) {
				sum += val.get();
			}
			context.write(key, new IntWritable(sum));
		}
	}

	//Main函数
	public static void main(String[] args) throws Exception {
		/*
		 * 初始化Configuration
		 * 读取Hadoop系统配置信息：core-site.xml, hdfs-site.xml, mapred-site.xml等
		 * 
		 */
		Configuration conf = new Configuration();
		
		/*
		 * 定义程序输入的两个参数
		 * 另外还有种使用ToolRunner的方法
		 * 
		 * 为什么叫otherArgs，不能直接使用main函数的args吗？
		 */
		
//		
		String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
		if (otherArgs.length != 2){
			System.err.println("Usage: wordcount <in> <out>");
			System.exit(2);;
		}
		
		//构建一个Job，使用conf配置
		Job job = new Job(conf);
				
		//装载编写好的程序
		job.setJarByClass(WordCount2.class);  //装载MapReduce程序类
		job.setJobName("word count");	//给Job命名

		job.setInputFormatClass(TextInputFormat.class);	//确定InputFormat类
		job.setOutputFormatClass(TextOutputFormat.class);	//确定OutputFormat类
		
		job.setOutputKeyClass(Text.class);	//确定输出的Key的类
		job.setOutputValueClass(IntWritable.class);	//确定输出的Value的类

		job.setMapperClass(WordCountMap.class);	//装载map的实现类
		job.setReducerClass(WordCountReduce.class);	//装载reduce的实现类
		
		
		//构建输入输出的数据文件
		FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
		FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));

		if (job.waitForCompletion(true))
			System.exit(0);
		else {
			System.out.println("Job Failed!");
			System.exit(1);
		}
	}
}
