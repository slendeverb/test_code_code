package software.coursemanage;

public class Course {
	private String id;
	private String name;
	private int hours;
	private int credits;
	private String deptName;
	
	public Course() {}
	public Course(String courseID,String courseName,int hours,int credits,String deptName) {
		this.id=courseID;
		this.name=courseName;
		this.hours=hours;
		this.credits=credits;
		this.deptName=deptName;
	}
	
	public String getID() {
		return this.id;
	}
	public String getName() {
		return this.name;
	}
	public int getHours() {
		return this.hours;
	}
	public int getCredits() {
		return this.credits;
	}
	public String getDeptName() {
		return this.deptName;
	}
}
