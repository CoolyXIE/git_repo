package cooly.hadoop.a;
import java.io.IOException;
 
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;
 
 
public class MaxTemperatureReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
 
    public void reduce(Text _key, Iterable<IntWritable> values, Context context)
            throws IOException, InterruptedException {
        // process values
        int maxValue  = Integer.MIN_VALUE;
        for (IntWritable val : values) {
            System.err.println(val.get());
            maxValue = Math.max(maxValue, val.get());
        }
        context.write(_key, new IntWritable(maxValue));
    }
 
}