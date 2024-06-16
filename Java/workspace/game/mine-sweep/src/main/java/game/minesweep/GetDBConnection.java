package game.minesweep;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

//数据库连接的统一操作
public class GetDBConnection {
	public static Connection connectDB(String DBname, String userid, String password) {
		Connection con = null;

		String driver = "com.mysql.cj.jdbc.Driver";// JDBC驱动
		String uri = "jdbc:mysql://localhost:3306/" + DBname
				+ "?useUnicode=true&characterEncoding=UTF-8&useSSL=false&serverTimezone=UTC";

		try {
			Class.forName(driver);// ①注册驱动
			con = DriverManager.getConnection(uri, userid, password);// ②建立连接
			if (!con.isClosed()) {
				System.out.println("数据库连接成功");
			}
		} catch (ClassNotFoundException e) {
			System.out.println("数据库驱动未安装");
		} catch (SQLException e) {
			e.printStackTrace();
			System.out.println("数据库连接失败");
		}
		return con;

	}
}
