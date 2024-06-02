package game.minesweep;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.ColorDescriptor;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Button;
import org.eclipse.jface.resource.FontDescriptor;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

//主页面 用作菜单 向其他部分跳转
public class HomePage {

	protected Shell shell;
	private LocalResourceManager localResourceManager;

	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			HomePage window = new HomePage();
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
		createResourceManager();
		shell.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(153, 50, 204))));
		shell.setSize(1450, 1000);
		shell.setText("我也干了");

		Button btn_begin = new Button(shell, SWT.NONE);
		btn_begin.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				GameStart game = new GameStart();
				game.open();
			}
		});
		btn_begin.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 14, SWT.BOLD)));
		btn_begin
				.setForeground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 255, 255))));
		btn_begin.setBounds(595, 538, 250, 50);
		btn_begin.setText("开始游戏");
		btn_begin.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 215, 0))));

		Button btn_history = new Button(shell, SWT.NONE);
		btn_history.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				History history = new History();
				history.open();
			}
		});
		btn_history.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 14, SWT.BOLD)));
		btn_history.setText("历史记录");
		btn_history.setBounds(595, 634, 250, 50);
		btn_history
				.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 215, 0))));

		Button btn_story = new Button(shell, SWT.NONE);
		btn_story.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				Story story = new Story();
				story.open();
			}
		});
		btn_story
				.setForeground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 255, 255))));
		btn_story.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 14, SWT.BOLD)));
		btn_story.setText("背景介绍");
		btn_story.setBounds(595, 724, 250, 50);
		btn_story.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(153, 50, 204))));

		Button btn_exit = new Button(shell, SWT.NONE);
		btn_exit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				Exit exit = new Exit();
				exit.open();
			}
		});
		btn_exit.setFont(
				(Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 14, SWT.BOLD)));
		btn_exit.setText("退出游戏");
		btn_exit.setBounds(595, 815, 250, 50);
		btn_exit.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(153, 50, 204))));

		Label lbl_bg = new Label(shell, SWT.NONE);
		lbl_bg.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "homepage.png")));
		lbl_bg.setBounds(0, 0, 1433, 1017);

	}

	private void createResourceManager() {
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(), shell);
	}
}
