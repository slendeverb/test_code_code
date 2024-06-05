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

//背景故事模块
public class Story {

	protected Shell shell;
	private LocalResourceManager localResourceManager;
	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			Story window = new Story();
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
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(),shell);
		shell.setSize(1048, 1206);
		shell.setText("SWT Application");
		
		Button btn_back = new Button(shell, SWT.NONE);
		btn_back.setFont((Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 10, SWT.BOLD)));
		btn_back.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				HomePage window=new HomePage();
				window.open();
			}
		});
		btn_back.setBounds(875, 917, 132, 44);
		btn_back.setText("返回上一页面");
		btn_back.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(204, 153, 255))));
		Label lbl_bg = new Label(shell, SWT.NONE);
		lbl_bg.setBounds(0, 0, 1413, 1160);
		lbl_bg.setImage(
				(Image)localResourceManager.create(ImageDescriptor.createFromFile(getClass(), "story.png"))
				
				);

	}

}
