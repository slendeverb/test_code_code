package software.coursemanage;

import java.sql.*;
import java.util.ArrayList;
import java.util.Optional;

public class StudentDao extends AdminDao {
	public Optional<Student> findStudent(String studentID){
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		Student student=null;
		try {
			String sql="select * from Student where StudentID=?";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, studentID);
			pstm.addBatch();
			rs=pstm.executeQuery();
			String id=null;
			String name=null;
			char gender=0;
			int age=-1;
			String major=null;
			String deptName=null;
			while(rs.next()) {
				id=rs.getString("StudentID");
				name=rs.getString("Name");
				gender=rs.getString("Gender").charAt(0);
				age=rs.getInt("Age");
				major=rs.getString("Major");
				deptName=rs.getString("DeptName");
			}
			if(id!=null) {
				student=new Student(id,name,gender,age,major,deptName);
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
		return Optional.ofNullable(student);
	}
	
	public int getTotalCredits(String studentID) {
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		int credits=0;
		try {
			String sql="select sum(Credits) as Credits from Course "
					+ "where CourseID= "
					+ "(select CourseID from Enroll "
					+ "where StudentID=?)";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, studentID);
			pstm.addBatch();
			rs=pstm.executeQuery();
			while(rs.next()) {
				credits=rs.getInt("Credits");
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
		return credits;
	}
	
	public ArrayList<Course> getCourse(String studentID){
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		ArrayList<Course> courses=new ArrayList<Course>();
		try {
			String sql="select * from Course "
					+ "where CourseID= "
					+ "(select CourseID from Enroll "
					+ "where StudentID=?)";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, studentID);
			pstm.addBatch();
			rs=pstm.executeQuery();
			while(rs.next()) {
				String courseID=rs.getString("CourseID");
				String courseName=rs.getString("CourseName");
				int hours=rs.getInt("Hours");
				int credits=rs.getInt("Credits");
				String deptName=rs.getString("DeptName");
				courses.add(new Course(courseID,courseName,hours,credits,deptName));
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
		return courses;
	}
}
