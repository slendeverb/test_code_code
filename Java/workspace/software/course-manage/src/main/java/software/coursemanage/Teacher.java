package software.coursemanage;

public class Teacher {
	private String id;
	private String name;
	private char gender;
	private String title;
	private String major;
	private String deptName;
	
	public Teacher() {}
	public Teacher(String teacherID,String name,char gender,String title,String major,String deptName) {
		this.id=teacherID;
		this.name=name;
		this.gender=gender;
		this.title=title;
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
	public String getTitle() {
		return this.title;
	}
	public String getMajor() {
		return this.major;
	}
	public String getDeptName() {
		return this.deptName;
	}
}
