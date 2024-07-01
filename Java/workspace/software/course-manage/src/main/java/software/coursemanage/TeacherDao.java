package software.coursemanage;

import java.sql.*;
import java.util.ArrayList;
import java.util.Optional;

public class TeacherDao extends AdminDao{
	public Optional<Teacher> findTeacher(String teacherID){		
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		Teacher teacher=null;
		try {
			String sql="select * from Teacher where TeacherID=?";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, teacherID);
			pstm.addBatch();
			rs=pstm.executeQuery();
			String id=null;
			String name=null;
			char gender=0;
			String title=null;
			String major=null;
			String deptName=null;
			while(rs.next()) {
				id=rs.getString("TeacherID");
				name=rs.getString("Name");
				gender=rs.getString("Gender").charAt(0);
				title=rs.getString("Title");
				major=rs.getString("Major");
				deptName=rs.getString("DeptName");
			}
			if(id!=null) {
				teacher=new Teacher(id,name,gender,title,major,deptName);
			}
		}catch(Exception e) {
			e.printStackTrace();
		}finally {
			databaseConnection.close(rs, pstm, conn);
		}
		return Optional.ofNullable(teacher);
	}
	
	public ArrayList<Course> getCourse(String teacherID){
		conn=databaseConnection.getConnection();
		PreparedStatement pstm=null;
		ResultSet rs=null;
		ArrayList<Course> courses=new ArrayList<Course>();
		try {
			String sql="select * from Course "
					+ "where CourseID= "
					+ "(select CourseID from Teaches "
					+ "where TeacherID=?)";
			pstm=conn.prepareStatement(sql);
			pstm.setString(1, teacherID);
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
