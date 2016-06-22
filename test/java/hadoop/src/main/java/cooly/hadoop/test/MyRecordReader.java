package cooly.hadoop.test;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.util.LineReader;

public class MyRecordReader extends RecordReader {
	
	private long start;
	private long end;
	private long pos;
	private FSDataInputStream fin = null;
	private LongWritable key = null;
	private Text value = null;
	private LineReader reader = null;
	
	@Override
	public void close() throws IOException {
		// TODO Auto-generated method stub
		fin.close();
	}

	@Override
	public LongWritable getCurrentKey() throws IOException,
	InterruptedException {
		// TODO Auto-generated method stub
		return key;
	}

	@Override
	public Text getCurrentValue() throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		return value;
	}

	@Override
	public float getProgress() throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void initialize(InputSplit inputSplit, TaskAttemptContext context)
			throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		FileSplit fileSplit = (FileSplit)inputSplit;
		start = fileSplit.getStart();
		end = start + fileSplit.getLength();
		Configuration conf = context.getConfiguration();
		Path path = fileSplit.getPath();
		FileSystem fs = path.getFileSystem(conf);
		fin = fs.open(path);
		fin.seek(start);
		reader = new LineReader(fin);
		pos = 1;
	}

	@Override
	public boolean nextKeyValue() throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		if(key == null)
			key = new LongWritable();
		key.set(pos);
		if(value == null)
			value = new Text();
		if(reader.readLine(value) == 0)
			return false;
		pos++;
		return true;
	}

}