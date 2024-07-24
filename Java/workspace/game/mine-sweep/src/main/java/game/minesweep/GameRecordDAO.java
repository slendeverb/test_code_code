package game.minesweep;

import java.net.Socket;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

//数据库操作，数据库用来保存游戏记录
@SuppressWarnings("unused")
public class GameRecordDAO {

	private GameRecord gameRecord;
	public String[] data;

	public GameRecordDAO(GameRecord gameRecord) {
		this.gameRecord = gameRecord;
	}

	public GameRecordDAO() {}

	public static void main(String[] args) {
	}

	/*
	 * 数据库名：minesweeperdb 数据库表：GameRecords
	 * id INT AUTO_INCREMENT PRIMARY KEY, -- 唯一标识符，自增
	 * length INT NOT NULL, -- 游戏板的大小（长度）
	 * mineNum INT NOT NULL, -- 地雷数量
	 * time INT NOT NULL, -- 完成游戏所用的时间（秒）
	 * isWon BOOLEAN NOT NULL, -- 游戏是否成功（赢或输）
	 * score INT NOT NULL, -- 得分
	 * mode VARCHAR(10) NOT NULL, -- 游戏模式（简单、一般、困难、自定义）
	 * achievement VARCHAR(255) NOT NULL -- 获得的成就
	 */

	// 数据库建立连接
	private static Connection getConnection() {
		Connection dbcon; // 连接对象dbcon
		dbcon = GetDBConnection.connectDB("minesweeperdb", "root", "040629");// 参数分别是数据库名，用户名，数据库密码
		return dbcon;
	}

	// 数据库插入操作
	public void insert() {
		Connection dbcon = getConnection();
		if (dbcon == null)
			System.out.println("连接失败");

		// 这里的sql语句可以直接拼接成最终的sql语句，把参数用？占位符代替，等会再传入。
		String sql = "insert into GameRecords values (null, ?, ?, ?, ?, ?, ?, ?)";
		PreparedStatement preparedStatement = null;
		try {
			preparedStatement = dbcon.prepareStatement(sql);
			preparedStatement.setInt(1, gameRecord.getLength());
			preparedStatement.setInt(2, gameRecord.getMineNum());
			preparedStatement.setInt(3, gameRecord.getTime());
			preparedStatement.setBoolean(4, gameRecord.isWon());
			preparedStatement.setInt(5, gameRecord.getScore());
			preparedStatement.setString(6, gameRecord.getMode());
			preparedStatement.setString(7, gameRecord.getAchievement());
			int i = preparedStatement.executeUpdate();
			if (i > 0) {
				System.out.println("添加成功");
			} else {
				System.out.println("添加失败");
			}
		} catch (SQLException throwables) {
			throwables.printStackTrace();
		} finally {
			try {
				dbcon.close();
				preparedStatement.close();
			} catch (SQLException throwables) {
				throwables.printStackTrace();
			}
		}

	}

}
