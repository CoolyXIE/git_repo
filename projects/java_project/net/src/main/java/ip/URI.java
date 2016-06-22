package ip;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;


public class URI {
	
	public static void f1() throws IOException{
		URL url = new URL("http://news.163.com/16/0225/01/BGKOO2B20001124J.html");
		System.out.println(url.getProtocol());
		System.out.println(url.getHost());
		System.out.println(url.getFile());
		InputStream in = url.openConnection().getInputStream();
		OutputStream out = new FileOutputStream("F:/news.html", false);
		byte[] bytes = new byte[1024];
		while(true){
			int size = in.read(bytes);
			if (size == -1)
				break;
			out.write(bytes, 0, size);
		}
		in.close();
		out.close();
	}
	
	
	public static void main(String[] args) throws IOException {
		f1();
	}
}
