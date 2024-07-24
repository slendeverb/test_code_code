package software.coursemanage;

public class Student {
	private String id;
	private String name;
	private char gender;
	private int age;
	private String major;
	private String deptName;
	
	public Student() {}
	public Student(String studentID,String name,char gender,int age,String major,String deptName) {
		this.id=studentID;
		this.name=name;
		this.gender=gender;
		this.age=age;
		this.major=major;
		this.deptName=deptName;
	}
	
	public String getID() {
		return this.id;
	}
	public String getName() {
		return this.name;
	}
	public char getGender() {
		return this.gender;
	}
	public int getAge() {
		return this.age;
	}
	public String getMajor() {
		return this.major;
	}
	public String getDeptName() {
		return this.deptName;
	}
}
