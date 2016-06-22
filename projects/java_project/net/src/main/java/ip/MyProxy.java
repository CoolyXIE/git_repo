package ip;

import java.net.InetSocketAddress;
import java.net.Proxy;
import java.net.SocketAddress;

public class MyProxy {
	public static void f1(){
		SocketAddress address = new InetSocketAddress("proxy.example.com", 80);
		Proxy proxy = new Proxy(Proxy.Type.HTTP, address);
	}
	
	
	
	
	public static void main(String[] args) {
		
	}
}
