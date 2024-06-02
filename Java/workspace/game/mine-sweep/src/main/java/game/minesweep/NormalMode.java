package game.minesweep;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;

//系统给定的模式，根据难度的不同提供不同的地雷图  用户不可自定义
public class NormalMode {

	protected Shell shell;
	int length;
	int num;

	NormalMode(int length, int num) {
		this.length = length;
		this.num = num;
	}
	// 对原构造方法进行改写 让其可以接受不同规格
	/**
	 * Launch the application.
	 * 
	 * @param args
	 */

	/*
	 * public static void main(String[] args) {
	 * try {
	 * NormalMode window = new NormalMode(length,num);
	 * window.open();
	 * } catch (Exception e) {
	 * e.printStackTrace();
	 * }
	 * }
	 */
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

		Button btn_back = new Button(shell, SWT.NONE);
		btn_back.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				GameStart window = new GameStart();
				window.open();
			}
		});
		btn_back.setBounds(1101, 217, 114, 34);
		btn_back.setText("返回上一页面");
		// 提供返回上一级页面的途径

		if (length * length >= num) {

			int[] restNum = { num };
			int[] restNonNum = { length * length - num };
			Label mineNum = new Label(shell, SWT.NONE);
			mineNum.setBounds(600, 100, 130, 50);
			mineNum.setText("剩余雷数： " + restNum[0]);

			Label timerLabel = new Label(shell, SWT.NONE);
			timerLabel.setBounds(600, 227, 90, 24);
			timerLabel.setText("Time: 0");

			GameTime gameTimer = new GameTime(timerLabel);

			MineGenerating minegen = new MineGenerating(length, length, num);

			boolean[] firstClick = { true };// 初始化标记 声明为数组类型是为了其在作为参数传入后能更新值
			Button[][] minediagram = new Button[length][length];// 声明button数组用来铺设地块 注：该写法在design界面不能可视化
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

		}

	}
}