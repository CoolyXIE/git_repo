package people;

public class Postgraduate extends Student{
	private Integer professorId;
	private String studyField;
	
	public Postgraduate(String name, String id, int age, String tel, int grade,
			String[] coursesToTake, Integer professorId, String studyField) {
		super(name, id, age, tel, grade, coursesToTake);
		this.professorId = professorId;
		this.studyField = studyField;
	}

	public Integer getProfessorId() {
		return professorId;
	}

	public String getStudyField() {
		return studyField;
	}

	public void setProfessorId(Integer professorId) {
		this.professorId = professorId;
	}

	public void setStudyField(String studyField) {
		this.studyField = studyField;
	}
}
