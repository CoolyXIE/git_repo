package cooly.hadoop.a;

import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.OutputCollector;
import org.junit.Test;

public class MaxTemperatureMapperTest {

	@Test
	public void processesValidRecord() throws IOException, InterruptedException {
		MaxTemperatureMapper mapper = new MaxTemperatureMapper();
		Text value = new Text("0043011990999991911051518004+68750+023550FM-12+0382" +
		"99999V0203201N00261220001CN9999999N9-00191+99999999999");
		
		OutputCollector<Text, IntWritable> output = mock(OutputCollector.class);
		mapper.map(null, value, output, null);
		verify(output).collect(new Text("hello"), WordCountMap.one);
		verify(output).collect(new Text("world"), WordCountMap.one);	
	}

}
