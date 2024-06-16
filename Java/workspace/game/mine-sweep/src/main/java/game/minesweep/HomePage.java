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
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Image;

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
		shell.setImage((Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "logo.png")));
		shell.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(153, 50, 204))));
		shell.setSize(1410, 1054);
		shell.setMinimumSize(800, 600);
		shell.setText("耐炸王");

		Label lab_begin = new Label(shell, SWT.NONE);
		lab_begin.setBounds(881, 204, 280, 73);
		lab_begin.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(153, 50, 204))));
		lab_begin.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "btn_begin.png")));

		lab_begin.addListener(SWT.MouseDown, event -> {

			shell.dispose();
			GameStart game = new GameStart();
			game.open();

		});

		Label lab_history = new Label(shell, SWT.NONE);
		lab_history.setBounds(811, 576, 309, 125);
		lab_history
				.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(153, 50, 204))));
		lab_history.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "btn_history.png")));

		lab_history.addListener(SWT.MouseDown, event -> {

			shell.dispose();
			History history = new History();
			history.open();

		});

		Label lab_story = new Label(shell, SWT.NONE);
		lab_story.setBounds(846, 351, 338, 125);

		lab_story.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "btn_story.png")));

		lab_story.addListener(SWT.MouseDown, event -> {

			shell.dispose();
			Story story = new Story();
			story.open();

		});

		Label lab_exit = new Label(shell, SWT.NONE);
		lab_exit.setBounds(826, 801, 309, 109);

		lab_exit.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "btn_exit.png")));

		lab_exit.addListener(SWT.MouseDown, event -> {

			shell.dispose();
			Exit exit = new Exit();
			exit.open();
		});
		// button组件达不到预期效果 故放弃该组件 使用label加监听器的方式实现原功能

		Label lbl_bg = new Label(shell, SWT.NONE);
		lbl_bg.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "homepage.png")));
		lbl_bg.setBounds(0, 0, 1392, 1007);
		//

	}

	private void createResourceManager() {
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(), shell);
	}
}
