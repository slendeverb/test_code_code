package game.minesweep;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.ColorDescriptor;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.widgets.Text;
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

//自定义模块 用户输入数据 合法后跳转正式游戏界面
public class CustomizeMode {
	private LocalResourceManager localResourceManager;
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
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(), shell);
		shell.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(245, 245, 220))));
		shell.setSize(773, 500);
		shell.setText("耐炸王");
		text = new Text(shell, SWT.BORDER);
		text.setText("开始游戏模块");
		text.setBounds(500, 800, 150, 30);

		Button btn_back = new Button(shell, SWT.NONE);
		btn_back.setFont((Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_back.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				GameStart window=new GameStart();
				window.open();
			}
		});
		btn_back.setBounds(401, 390, 132, 44);
		btn_back.setText("返回上一页面");
		btn_back.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(204, 153, 255))));
				

		Label label_length = new Label(shell, SWT.NONE);
		label_length.setAlignment(SWT.CENTER);
		label_length.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(153, 50, 204))));
		label_length.setForeground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 255, 255))));
		label_length.setFont((Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		label_length.setBounds(247, 160, 101, 30);
		label_length.setText("阵图长度");
		label_length.setFocus();

		Label label_num = new Label(shell, SWT.NONE);
		label_num.setAlignment(SWT.CENTER);
		label_num.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 255, 0))));
		label_num.setForeground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(0, 0, 0))));
		label_num.setFont((Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		label_num.setBounds(247, 248, 101, 30);
		label_num.setText("地雷数");

		text_length = new Text(shell, SWT.BORDER);
		text_length.setBounds(401, 159, 90, 30);

		text_num = new Text(shell, SWT.BORDER);
		text_num.setBounds(401, 247, 90, 30);
		
		
		Label tishi1 = new Label(shell, SWT.NONE);
		tishi1.setForeground(Display.getCurrent().getSystemColor(SWT.COLOR_RED));
		tishi1.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(245, 245, 220))));
		tishi1.setAlignment(SWT.CENTER);
		tishi1.setFont((Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		tishi1.setBounds(275, 58, 200, 44);
		// 设置一个用于提示用户的标签

		
		Button confirm = new Button(shell, SWT.NONE);
		confirm.setFont((Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		confirm.setBounds(216, 390, 132, 44);
		confirm.setText("确认");
		confirm.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 228, 181))));
		// 用户输入自定义规格  ！！！！！注：目前存在bug 表现为 当用户未输入数据直接点击确认时会闪退  应该比较容易解决  

		Label lbl_picture = new Label(shell, SWT.NONE);
		lbl_picture.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "laoda.png")));
		lbl_picture.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(245, 245, 220))));
		lbl_picture.setBounds(10, 151, 310, 259);
		
		Label lbl_input_bg = new Label(shell, SWT.NONE);
		lbl_input_bg.setBounds(996, 227, 234, 228);
		lbl_input_bg.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(152, 251, 152))));
		confirm.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				int length = Integer.parseInt(text_length.getText());
				int num = Integer.parseInt(text_num.getText());
				// 接收用户自定义参数

				
				
				//用户数据合法性判断
				if (length * length >= num&&length<=25&&length>=5) {
					//tishi1.setText("自定义成功");
					shell.dispose();
					NormalMode customize =new NormalMode(length,num,3);
					customize.open();
				} 
				
				else if(length * length >= num&&length<5) {
					tishi1.setText("生成地块数量过少");
				}
				else if(length * length >= num&&length>25) {
					tishi1.setText("生成地块数量超过上限");
				}
				else {

					tishi1.setText("输入有误，请重新输入");

				}
				/*int[] restNum = { num };
				int[] restNonNum = { length * length - num };
				// 用户定义参数合法 参数传入     ！！！！！关于参数合法的判断之后还需细化

				Label tishi2 = new Label(shell, SWT.NONE);
				tishi2.setBounds(100, 800, 200, 20);
				tishi2.setText("MANBA NEVER DIE");
				tishi2.setFont(localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 13, SWT.BOLD)));
				tishi2.setAlignment(SWT.CENTER);
				tishi2.setForeground(localResourceManager.create(ColorDescriptor.createFrom(new RGB(245, 255, 250))));
				tishi2.setBackground(localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 0, 0))));
				tishi2.setBounds(405, 720, 578, 34);
				
				
				
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
						if (length >= 18) {

							minediagram[i][j].setBounds(50 + i * 30, 50 + j * 30, 30, 30);

						} else if (length >= 10 && length < 18) {
							minediagram[i][j].setBounds(150 + i * 30, 150 + j * 30, 30, 30);
						} else {
							minediagram[i][j].setBounds(200 + i * 30, 250 + j * 30, 30, 30);
						}
						MouseClick click = new MouseClick(minediagram[i][j], minediagram, minegen, firstClick, i, j,
								gameTimer, mineNum, restNum, restNonNum, tishi2);
						minediagram[i][j].addMouseListener(click);
					}
				}
				Label showData = new Label(shell, SWT.NONE);
				showData.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_INFO_BACKGROUND));
				showData.setImage((Image) localResourceManager
						.create(ImageDescriptor.createFromFile(getClass(), "showData.png"))

				);
				showData.setBounds(927, 120, 349, 458);
				*/
				//以上注释部分为最初思路，为了降低内聚故改写成目前模式

			}
		});

	}

}
