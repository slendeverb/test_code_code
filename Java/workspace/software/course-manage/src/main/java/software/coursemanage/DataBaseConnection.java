package software.coursemanage;

import java.sql.*;

public class DataBaseConnection {
	private String className="com.microsoft.sqlserver.jdbc.SQLServerDriver";
	private String url="jdbc:sqlserver://localhost:1433;databaseName=CourseManagement;trustServerCertificate=true";
	private String username="sa";
	private String password="040629";
	
	public Connection getConnection() {
		Connection conn;
		try {
			Class.forName(className);
			conn=DriverManager.getConnection(url,username,password);
		}catch(Exception e) {
			System.out.println("数据库连接失败");
			conn=null;
			e.printStackTrace();
		}
		return conn;
	}
	
	public void close(ResultSet rs,PreparedStatement pstm,Connection conn) {
		try {
			if(pstm!=null) {
				pstm.close();
			}
		}catch(SQLException e) {
			System.out.println("关闭PreparedStatement对象pstm失败");
			e.printStackTrace();
		}
		
		try {
			if(conn!=null) {
				conn.close();
			}
		}catch(SQLException e) {
			System.out.println("关闭Connection对象conn失败");
			e.printStackTrace();
		}
	}
}
