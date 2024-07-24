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

//根据难度的不同提供不同的游戏模式

//更改后  自定义模式也在此处实现
public class NormalMode {
	private LocalResourceManager localResourceManager;
	protected Shell shell;
	int length;
	int num;
	int mode;// 判断属于哪种模式
	AudioPlayer bgm = new AudioPlayer("src/main/java/game/minesweep/bgm.wav");

	NormalMode(int length, int num, int mode) {
		this.length = length;
		this.num = num;
		this.mode = mode;
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
	 * NormalMode window = new NormalMode(4, 1, 0);
	 * window.open();
	 * } catch (Exception e) {
	 * e.printStackTrace();
	 * }
	 * }
	 */
	// 出于安全考虑 通常情况下不可直接打开该类

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
		createResourceManager();
		shell.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_INFO_BACKGROUND));
		shell.setSize(1460, 1070);
		shell.setText("耐炸王");
		shell.setImage((Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "logo.png")));

		Button btn_back = new Button(shell, SWT.NONE);
		btn_back.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_back.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				if (mode == 3) {
					bgm.pause();// 返回上级菜单时，bgm播放停止
					CustomizeMode window = new CustomizeMode();
					window.open();

				} else {
					bgm.pause();
					GameStart window = new GameStart();
					window.open();

				}

			}
		});
		btn_back.setBounds(612, 783, 132, 44);
		btn_back.setText("返回上一页面");
		btn_back.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(204, 153, 255))));

		// 提供返回上一级页面的途径 根据模式的不同 返回的上级菜单也不同

		int[] restNum = { num };
		int[] restNonNum = { length * length - num };
		// 记录剩余雷数和剩余非雷地块数 用于游戏逻辑判断

		Label mineNum = new Label(shell, SWT.NONE);
		mineNum.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		mineNum.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_LIST_SELECTION_TEXT));
		mineNum.setBounds(1053, 390, 111, 34);
		mineNum.setText("雷数： " + restNum[0]);

		Label timerLabel = new Label(shell, SWT.NONE);
		timerLabel.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		timerLabel.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_LIST_SELECTION_TEXT));
		timerLabel.setBounds(1081, 488, 90, 25);
		timerLabel.setText("时间: 0");

		if (length * length >= num) {

			GameTime gameTimer = new GameTime(timerLabel);

			MineGenerating minegen = new MineGenerating(length, length, num);

			boolean[] firstClick = { true };// 初始化标记 声明为数组类型是为了其在作为参数传入后能更新值
			Button[][] minediagram = new Button[length][length];// 声明button数组用来铺设地块 注：该写法在design界面不能可视化

			Label tishi = new Label(shell, SWT.NONE);
			tishi.setBounds(100, 800, 200, 20);
			tishi.setText("MANBA NEVER DIE");
			tishi.setFont(
					(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 15, SWT.BOLD)));
			tishi.setAlignment(SWT.CENTER);
			tishi.setForeground(
					(Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(245, 255, 250))));
			tishi.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 0, 0))));
			tishi.setBounds(405, 720, 578, 40);
			// 设置一行提示栏 用于向用户展示当前游戏状态

			for (int i = 0; i < length; i++) {
				for (int j = 0; j < length; j++) {
					minediagram[i][j] = new Button(shell, SWT.NONE);
					if (length >= 18) {

						minediagram[i][j].setBounds(50 + i * 30, 50 + j * 30, 30, 30);

					} else if (length >= 10 && length < 18) {
						minediagram[i][j].setBounds(150 + i * 30, 150 + j * 30, 30, 30);
					} else {
						minediagram[i][j].setBounds(380 + i * 30, 280 + j * 30, 30, 30);
					}
					minediagram[i][j].setBackground(
							(Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 153, 102))));
					MouseClick click = new MouseClick(minediagram[i][j], minediagram, minegen, firstClick, i, j,
							gameTimer, mineNum, restNum, restNonNum, tishi, mode, bgm);
					minediagram[i][j].addMouseListener(click);
				}
			} // 铺设地雷图 同时实现了根据地图大小进行位置上的微调

			Label lbl_bg = new Label(shell, SWT.NONE);
			lbl_bg.setSize(0, 0);
			lbl_bg.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(0, 206, 209))));
			if (length >= 18) {
				lbl_bg.setBounds(40, 40, 30 * length + 20, 30 * length + 20);
			} else if (length < 18 && length >= 10) {
				lbl_bg.setBounds(140, 140, 30 * length + 20, 30 * length + 20);
			} else {
				lbl_bg.setBounds(370, 270, 30 * length + 20, 30 * length + 20);
			}

		} // 此处为地雷图加上边框 同样根据生成图大小进行位置微调

		Label showData = new Label(shell, SWT.NONE);
		showData.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_INFO_BACKGROUND));
		showData.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "showData.png"))

		);
		showData.setBounds(927, 120, 349, 458);
	}// 设置提示器 显示剩余雷数和用时

	private void createResourceManager() {
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(), shell);
	}
}