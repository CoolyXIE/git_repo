package util;


public class Test extends A{
	public Test(int x, int y) {
		super(x, y);
	}
	
	public static void main(String[] args) {
		Test test = new Test(1, 2);
		test.test2();
	}
}

class A{
	private Integer x = 0;
	Integer y = 1;
	
	public A(int x, int y){
		this.x = x;
		this.y = y;
	}
	
	public void test1(){
		System.out.println("1");
	}
	
	void test2(){
		System.out.println(x);
	}
	
	private void test3(){
		System.out.println("3");
	}
}
