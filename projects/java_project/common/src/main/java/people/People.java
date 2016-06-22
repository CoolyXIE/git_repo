package people;

public class People {
	private String name;
	private String Id;
	private int age;
	private String tel;
	
	public People(String name, String id, int age, String tel) {
		super();
		this.name = name;
		Id = id;
		this.age = age;
		this.tel = tel;
	}

	public String getName() {
		return name;
	}

	public String getId() {
		return Id;
	}

	public int getAge() {
		return age;
	}

	public String getTel() {
		return tel;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setId(String id) {
		Id = id;
	}

	public void setAge(int age) {
		this.age = age;
	}

	public void setTel(String tel) {
		this.tel = tel;
	}
}
