package ip;

import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Arrays;

public class IPAddress {
	

	public static void f1(){
		try {
			InetAddress[] baiduAddress = InetAddress.getAllByName("www.baidu.com");
//			System.out.println(Arrays.toString(baiduAddress));
			InetAddress localAddress = InetAddress.getLocalHost();
			System.out.println(localAddress);
			InetAddress loopAddress = InetAddress.getLoopbackAddress();
			System.out.println(loopAddress);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}
	}
	
	public static void f2() throws IOException{
		byte[] bytes = {(byte)192, 12, (byte) 216, (byte) 222};
		InetAddress address = InetAddress.getByAddress(bytes);
		System.out.println(address.isReachable(10000));
	}
	
	public static void f3() throws SocketException{
		NetworkInterface ni = NetworkInterface.getByName("ELX100");
		System.out.println(ni);
	}
	
	public static void f4(String[] addressArr) throws UnknownHostException{
		for(String address:addressArr){
			if (isSpamAddress(address))
				System.out.println(address + "is a spam address");
			else 
				System.out.println(address + "is not a spam address");
		}
	}
	
	private static final String BLACKHOLE = "sbl.spamhaus.org";
	private static boolean isSpamAddress(String address) throws UnknownHostException {
		try {
			InetAddress add = InetAddress.getByName(address);
			byte[] bytes = add.getAddress();
			String query = BLACKHOLE;
			for (byte b:bytes){
				int unsignedByte = b < 0? b + 256: b;
				query = unsignedByte + "." + query;
			}
			InetAddress.getByName(query);
			return true;
		} catch (UnknownHostException e) {
			return false;
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
	}

	public static void main(String[] args) throws IOException {
		InetAddress address = InetAddress.getByName("207.34.56.23");
		System.out.println(Arrays.toString(address.getAddress()));
	}
}
