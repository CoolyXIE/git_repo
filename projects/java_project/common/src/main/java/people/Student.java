package people;

public class Student extends People{
	private int grade;
	private String[] coursesToTake;
	
	public Student(String name, String id, int age, String tel, int grade,
			String[] coursesToTake) {
		super(name, id, age, tel);
		this.grade = grade;
		this.coursesToTake = coursesToTake;
	}

	public int getGrade() {
		return grade;
	}

	public String[] getCoursesToTake() {
		return coursesToTake;
	}

	public void setGrade(int grade) {
		this.grade = grade;
	}

	public void setCoursesToTake(String[] coursesToTake) {
		this.coursesToTake = coursesToTake;
	}
}
