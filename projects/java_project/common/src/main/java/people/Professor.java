package people;

import java.util.Map;
import java.util.TreeMap;


public class Professor extends Teacher{
	private Integer[] students;
	private String researchField;
	
	public Professor(String name, String id, int age, String tel,
			String school, String[] courses, Integer[] students, String researchField) {
		super(name, id, age, tel, school, courses);
		this.students = students;
		this.researchField = researchField;
	}
	public Integer[] getStudents() {
		return students;
	}

	public void setStudents(Integer[] students) {
		this.students = students;
	}
	
	public static void main(String[] args) {
		Map<Fushu, Integer> x = new TreeMap<Fushu, Integer>();
		x.put(new Fushu(1.0, 3.0), 1);
		x.put(new Fushu(2.0, 2.2), 2);
		x.put(new Fushu(3.1, -1.2), 3);
		System.out.println(x);
		
	}
}

class Fushu implements Comparable<Fushu>{
	double x;
	double y;
	
	public Fushu(double x, double y) {
		super();
		this.x = x;
		this.y = y;
	}
	
	@Override
	public String toString() {
		return x + "+ i " + y;
	}

	public int compareTo(Fushu o) {
		return (int) (this.x * this.x + this.y * this.y - o.x * o.x - o.y *o.y);
	}
	
}