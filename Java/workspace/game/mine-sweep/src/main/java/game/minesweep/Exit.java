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

//退出游戏选项  
public class Exit {

	protected Shell shell;
	private LocalResourceManager localResourceManager;

	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			Exit window = new Exit();
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
		shell.setSize(750, 900);
		shell.setText("耐炸王");
		shell.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 215, 0))));
		shell.setImage((Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "logo.png")));

		Label lbl_bg = new Label(shell, SWT.NONE);
		lbl_bg.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 215, 0))));
		lbl_bg.setBounds(-14, -33, 731, 860);
		lbl_bg.setImage(
				(Image) localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "exit.png"))

		);

	}

}
