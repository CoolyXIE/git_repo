package util;

import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Arrays;

public class IO {
	public static void testRead() throws IOException{
		int size;
		String filePath = "F:/sf.txt";
		InputStream in = new FileInputStream(filePath);
		size = in.available();
		System.out.println("字节数：" + size);
		char[] text = new char[size];
		for(int i = 0; i < size; i ++)
			text[i] = (char)in.read();
		in.close();
		System.out.println(Arrays.toString(text));
	}

	public static void testWrite() throws IOException{
		String filePath = "F:/b.txt";
		OutputStream out = new FileOutputStream(filePath);
		String word = "hello world!";
		out.write(word.getBytes());
		out.close();
	}
	
	public static void testDataOutputStream() throws FileNotFoundException{
	}
	
	public static void main(String[] args) throws IOException {
		testWrite();
	}
}
