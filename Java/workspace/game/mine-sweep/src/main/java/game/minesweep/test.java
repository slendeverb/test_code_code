package game.minesweep;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Text;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.ColorDescriptor;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.jface.resource.FontDescriptor;

public class test {

	protected Shell shell;
	private Text text;
	private LocalResourceManager localResourceManager;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			test window = new test();
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
		shell.setBackground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 228, 181))));
		shell.setSize(450, 300);
		shell.setText("SWT Application");
		
		Canvas canvas = new Canvas(shell, SWT.NONE);
		canvas.setForeground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(135, 206, 250))));
		canvas.setBounds(68, 96, 191, 64);
		
		text = new Text(shell, SWT.BORDER);
		text.setBounds(95, 24, 73, 30);
		
		Button btnNewButton = new Button(shell, SWT.NONE);
		btnNewButton.setFont((Font) localResourceManager.create(FontDescriptor.createFrom("Microsoft YaHei UI", 9, SWT.BOLD)));
		btnNewButton.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
			}
		});
		btnNewButton.setForeground((Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(245, 255, 250))));
		btnNewButton.setBounds(105, 37, 114, 34);
		btnNewButton.setText("New Button");

	}
	private void createResourceManager() {
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(),shell);
	}
}
