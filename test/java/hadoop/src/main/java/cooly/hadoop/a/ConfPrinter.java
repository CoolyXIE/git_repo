package cooly.hadoop.a;


import java.util.Map.Entry;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;


public class ConfPrinter extends Configured implements Tool {

	public int run(String[] arg0) throws Exception {
		Configuration conf = getConf();
		
		for(Entry<String, String> entry:conf){
			System.out.printf("%s = %s \n", entry.getKey(), entry.getValue());
		}
		
		return 0;
	}

	public static void main(String[] args) throws Exception {
		int exitCode = ToolRunner.run(new ConfPrinter(), args);
		System.exit(exitCode);
	}
}
