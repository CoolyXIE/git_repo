package ip;

import java.net.URL;
import java.net.URLConnection;

public class MyURLConnection {
	public static void viewHeader(String url){
		try {
			URL u = new URL(url);
			URLConnection uc = u.openConnection();
			String contentType = uc.getContentType();
			System.out.println("Content-type: " + contentType);
			if (uc.getContentLength() != -1)
				System.out.println("Content-length: " + uc.getContentLength());
			String encoding;
			if ((encoding = uc.getContentEncoding()) != null)
				System.out.println("Content-encoding: " + encoding);
			long time;
			if ((time = uc.getDate()) != 0)
				System.out.println("Date in ms: " + time);
			if ((time = uc.getExpiration()) != 0)
				System.out.println("Expiration in ms: " + time);
			if ((time = uc.getLastModified()) != 0)
				System.out.println("Last modified in ms: " + time);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	public static void main(String[] args) {
		viewHeader("http://bubkoo.com/2014/04/21/http-cookies-explained/");
	}
}
