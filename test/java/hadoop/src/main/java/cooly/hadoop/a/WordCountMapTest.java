package cooly.hadoop.a;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.OutputCollector;
import org.junit.Test;

public class WordCountMapTest{
	@Test
	public void test() throws IOException, InterruptedException{
		WordCountMap wc = new WordCountMap();
		OutputCollector<Text, IntWritable> output = mock(OutputCollector.class);
		wc.map(null, new Text("hello world"), output);
		verify(output).collect(new Text("hello"), WordCountMap.one);

	}
}