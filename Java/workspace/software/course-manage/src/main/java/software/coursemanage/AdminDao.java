package software.coursemanage;

import java.sql.*;
import java.util.ArrayList;

public class AdminDao {
	protected DataBaseConnection databaseConnection=new DataBaseConnection();
	protected Connection conn=null;
	
	public String getPassword(String userID) {
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		String password=null;
		try {
			String sql="select Password from UserAccount where UserID=?";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, userID);
			pstm.addBatch();
			rs=pstm.executeQuery();
			while(rs.next()) {
				password=rs.getString("Password");
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
		return password;
	}
	
	public String getUserType(String userID) {
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		String userType=null;
		try {
			String sql="select UserType from UserAccount where UserID=?";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, userID);
			pstm.addBatch();
			rs=pstm.executeQuery();
			while(rs.next()) {
				userType=rs.getString("UserType");
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
		return userType;
	}
	
	public ArrayList<Course> getCourse(){
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		ArrayList<Course> courses=new ArrayList<Course>();
		try {
			String sql="select * from Course";
			pstm=conn.prepareStatement(sql);
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
	
	public void addCourse(Course course) {
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		try {
			String sql="insert into Course values(?,?,?,?,?)";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, course.getID());
			pstm.setString(2, course.getName());
			pstm.setInt(3, course.getHours());
			pstm.setInt(4, course.getCredits());
			pstm.setString(5, course.getDeptName());
			pstm.addBatch();
			pstm.executeUpdate();
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
	}
	
	public void updateCourse(String courseID,String updateValue,String columnName) {
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		try {
			String sql="update Course "
					+ "set "+columnName+"="+updateValue+" "
					+ "where CourseID="+courseID;
			pstm=conn.prepareStatement(sql);
			pstm.addBatch();
			pstm.executeUpdate();
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
	}
}
