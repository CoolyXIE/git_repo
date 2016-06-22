package cooly.hadoop.test;

import java.io.IOException;

import org.apache.commons.collections.keyvalue.MultiKey;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
/**
 * 自定义输入文件读取类
 * @author cooly
 *
 */
public class MyInputFormat extends FileInputFormat<Text, Text> {

	@Override
	public RecordReader<Text, Text> createRecordReader(InputSplit split, TaskAttemptContext context)
			throws IOException, InterruptedException {

		// TODO Auto-generated method stub
		return null;
	}

//	public static class MyRecordReader() extends RecordReader<K, V>{
//		public LineReader in;
//		public MultiKey key;
//
//	}

}