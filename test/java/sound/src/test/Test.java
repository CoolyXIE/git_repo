package test;

import java.io.BufferedReader;
import java.io.IOException;

import mysound.FileHelper;

public class Test {
	public static void main(String[] args) throws IOException {
		BufferedReader br = FileHelper.readFile("C:\\Users\\Cooly\\Desktop\\1.txt");
		String[] arr = br.readLine().split(" ");
		br.close();
		System.out.println(arr.length);
		
	}
}