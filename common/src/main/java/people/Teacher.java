package people;

public class Teacher extends People{
	private String school;
	private String[] coursesToTeach;

	public Teacher(String name, String id, int age, String tel, String school,
			String[] courses) {
		super(name, id, age, tel);
		this.school = school;
		this.coursesToTeach = courses;
	}

	public String getSchool() {
		return school;
	}

	public String[] getCourses() {
		return coursesToTeach;
	}

	public void setSchool(String school) {
		this.school = school;
	}

	public void setCourses(String[] courses) {
		this.coursesToTeach = courses;
	}
	
	


}
