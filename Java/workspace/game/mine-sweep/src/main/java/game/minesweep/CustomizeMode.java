package game.minesweep;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

//用户可自定义的模式
public class CustomizeMode {

	protected Shell shell;
	private Text text;
	private Text text_length;
	private Text text_num;

	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			CustomizeMode window = new CustomizeMode();
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
		shell.setSize(1450, 1000);
		shell.setText("SWT Application");
		text = new Text(shell, SWT.BORDER);
		text.setText("开始游戏模块");
		text.setBounds(500, 800, 150, 30);

		Button btn_back = new Button(shell, SWT.NONE);
		btn_back.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				GameStart window = new GameStart();
				window.open();
			}
		});
		btn_back.setBounds(1214, 213, 114, 34);
		btn_back.setText("返回上一页面");
		// 提供返回上一级页面的途径

		Label label_length = new Label(shell, SWT.NONE);
		label_length.setBounds(940, 182, 90, 24);
		label_length.setText("输入长度");
		label_length.setFocus();

		Label label_num = new Label(shell, SWT.NONE);
		label_num.setBounds(940, 240, 90, 24);
		label_num.setText("输入雷数");

		text_length = new Text(shell, SWT.BORDER);
		text_length.setBounds(1063, 182, 73, 30);

		text_num = new Text(shell, SWT.BORDER);
		text_num.setBounds(1063, 240, 73, 30);
		// 用户输入自定义规格

		Label label_tishi = new Label(shell, SWT.NONE);
		label_tishi.setBounds(940, 100, 200, 100);
		// 设置一个用于提示用户的标签

		Button confirm = new Button(shell, SWT.NONE);
		confirm.setBounds(963, 342, 114, 34);
		confirm.setText("确认");
		confirm.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				int length = Integer.parseInt(text_length.getText());
				int num = Integer.parseInt(text_num.getText());
				// 接收用户自定义参数

				if (length * length >= num) {
					label_tishi.setText("自定义成功");
					int[] restNum = { num };
					int[] restNonNum = { length * length - num };
					// 用户定义参数合法 参数传入 关于参数合法的判断之后可能还需细化

					Label mineNum = new Label(shell, SWT.NONE);
					mineNum.setBounds(600, 100, 130, 50);
					mineNum.setText("剩余雷数： " + restNum[0]);

					Label timerLabel = new Label(shell, SWT.NONE);
					timerLabel.setBounds(600, 150, 90, 24);
					timerLabel.setText("Time: 0");

					GameTime gameTimer = new GameTime(timerLabel);

					MineGenerating minegen = new MineGenerating(length, length, num);

					boolean[] firstClick = { true };
					Button[][] minediagram = new Button[length][length];
					for (int i = 0; i < length; i++) {
						for (int j = 0; j < length; j++) {
							minediagram[i][j] = new Button(shell, SWT.NONE);
							minediagram[i][j].setBounds(150 + i * 30, 200 + j * 30, 30, 30);
							MouseClick click = new MouseClick(minediagram[i][j], minediagram, minegen, firstClick, i, j,
									gameTimer,
									mineNum, restNum, restNonNum);
							minediagram[i][j].addMouseListener(click);
						}
					}
				} // 剩余部分见NormalMode
				else {

					label_tishi.setText("输入有误，请重新输入");

				}

			}
		});

	}

}
