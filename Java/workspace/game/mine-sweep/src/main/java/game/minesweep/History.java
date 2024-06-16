package game.minesweep;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.ColorDescriptor;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Label;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.widgets.Button;
import org.eclipse.jface.resource.FontDescriptor;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Image;
import java.util.ArrayList;
import java.util.List;
import java.sql.*;

//存放历史记录   

public class History {

	protected Shell shell;
	private LocalResourceManager localResourceManager;
	String[] data;

	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			History window = new History();
			window.open();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Open the window.
	 */
	public void open() {
		Display display = Display.getDefault();
		createContents();
		shell.open();

		shell.layout();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shell = new Shell();
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(), shell);
		shell.setSize(802, 1000);
		shell.setText("耐炸王");
		shell.setImage((Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "logo.png")));

		DataSet();
		Button btn_back = new Button(shell, SWT.NONE);
		btn_back.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_back.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				HomePage window = new HomePage();
				window.open();
			}
		});
		btn_back.setBounds(325, 750, 132, 44);
		btn_back.setText("返回上一页面");
		btn_back.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(204, 153, 255))));

		Label[] showData = new Label[data.length];
		int color = 0;
		for (int i = 0; i < data.length; i++) {
			showData[i] = new Label(shell, SWT.NONE);
			showData[i].setFont(
					(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 8, SWT.BOLD)));
			showData[i].setBounds(37, 155 + i * 40, 700, 25);
			showData[i].setText(data[i]);
			if (color % 2 == 0) {
				showData[i].setBackground(
						(Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(204, 153, 255))));
			} else {
				showData[i].setBackground(
						(Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 215, 0))));
			}
			color++;
		} // 显示记录

		Label lbl_bg = new Label(shell, SWT.NONE);
		lbl_bg.setBounds(-29, -126, 819, 1083);
		lbl_bg.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "history.png"))

		);

	}

	// 访问数据库 将数据按行存入数组中
	public void DataSet() {
		Connection dbcon;
		dbcon = GetDBConnection.connectDB("minesweeperdb", "root", "040629");
		if (dbcon == null) {
			System.out.println("连接失败");
			return;
		}

		String sql = "select * from GameRecords";
		PreparedStatement ps = null;
		ResultSet rs = null;
		List<String> tempList = new ArrayList<>();

		try {
			ps = dbcon.prepareStatement(sql);
			rs = ps.executeQuery();

			while (rs.next()) {
				String record = "阵图长度：" + rs.getInt(2) + "   " +
						"地雷数：" + rs.getInt(3) + "   " +
						"用时：" + rs.getInt(4) + "   " +
						"游戏结果：" + rs.getBoolean(5) + "   " +
						"得分：" + rs.getInt(6) + "   " +
						"模式：" + rs.getString(7) + "   " +
						"成就：" + rs.getString(8);
				tempList.add(record);
			}

			data = tempList.toArray(new String[0]);

		} catch (SQLException throwables) {
			throwables.printStackTrace();
		} finally {
			try {
				if (rs != null) {
					rs.close();
				}
				if (ps != null) {
					ps.close();
				}
				dbcon.close();
			} catch (SQLException throwables) {
				throwables.printStackTrace();
			}
		}
	}
}
