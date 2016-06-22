package mysound;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileHelper {
	public static BufferedReader readFile(String filePath){
		BufferedReader br = null;
		try {
			br = new BufferedReader(new FileReader(filePath));
		} catch (IOException e) {
			e.printStackTrace();
		} 
		return br;
	}
	
	public static BufferedWriter writeFile(String filePath, boolean append){
		BufferedWriter bw = null;
		try {
			bw = new BufferedWriter(new FileWriter(filePath, append));
		} catch (IOException e) {
			e.printStackTrace();
		}
		return bw;
	}
	
	public static BufferedWriter writerFile(String filePath){
		return writeFile(filePath, true);
	}
}
