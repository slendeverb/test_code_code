package game.minesweep;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.ColorDescriptor;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.resource.FontDescriptor;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Image;

//开始游戏选项  仅用作指南  具体游戏流程在NormalNode和CustomizeMode中实现

public class GameStart {

	protected Shell shell;
	private LocalResourceManager localResourceManager;

	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			GameStart window = new GameStart();
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
		shell.setSize(804, 531);
		shell.setText("耐炸王");
		shell.setImage((Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "logo.png")));

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
		btn_back.setBounds(304, 325, 132, 44);
		btn_back.setText("返回上一页面");
		btn_back.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(204, 153, 255))));
		// 返回上级菜单选项

		Button btn_easy = new Button(shell, SWT.NONE);
		btn_easy.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_easy.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				NormalMode window = new NormalMode(9, 10, 0);
				window.open();
			}
		});
		btn_easy.setBounds(43, 207, 114, 34);
		btn_easy.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(0, 255, 0))));
		btn_easy.setText("简单");
		// 转向简单模式

		Button btn_middle = new Button(shell, SWT.NONE);
		btn_middle.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_middle.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				NormalMode window = new NormalMode(16, 40, 1);
				window.open();
			}
		});
		btn_middle.setText("一般");
		btn_middle.setBounds(223, 207, 114, 34);
		btn_middle.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 215, 0))));
		// 转向一般模式

		Button btn_hard = new Button(shell, SWT.NONE);
		btn_hard.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_hard.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				NormalMode window = new NormalMode(22, 100, 2);
				window.open();
			}
		});
		btn_hard.setText("困难");
		btn_hard.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 69, 0))));
		btn_hard.setBounds(408, 207, 114, 34);
		// 转向困难模式

		Button btn_customize = new Button(shell, SWT.NONE);
		btn_customize.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_customize.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				CustomizeMode window = new CustomizeMode();
				window.open();
			}
		});// 转向自定义模式
		btn_customize.setText("自定义");
		btn_customize.setBounds(588, 207, 114, 34);
		btn_customize
				.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(148, 0, 211))));

		Label lbl_mode = new Label(shell, SWT.NONE);
		lbl_mode.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 15, SWT.BOLD)));
		lbl_mode.setAlignment(SWT.CENTER);
		lbl_mode.setBounds(304, 98, 143, 44);
		lbl_mode.setText("选择模式");
		lbl_mode.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(135, 206, 250))));

		Label lbl_picture = new Label(shell, SWT.NONE);
		lbl_picture.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "laoda.png")));
		lbl_picture
				.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(245, 245, 220))));
		lbl_picture.setBounds(392, 81, 310, 259);

	}
}
