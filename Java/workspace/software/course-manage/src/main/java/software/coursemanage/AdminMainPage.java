package software.coursemanage;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class AdminMainPage {

	protected Shell shellAdminMainPage;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			AdminMainPage window = new AdminMainPage();
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
		shellAdminMainPage.open();
		shellAdminMainPage.layout();
		while (!shellAdminMainPage.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellAdminMainPage = new Shell();
		shellAdminMainPage.setSize(570, 395);
		shellAdminMainPage.setText("课程管理系统-管理员");
		
		Button btnModifyCourse = new Button(shellAdminMainPage, SWT.NONE);
		btnModifyCourse.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				AdminModifyCourse adminModifyCourseWindow=new AdminModifyCourse();
				shellAdminMainPage.dispose();
				adminModifyCourseWindow.open();
			}
		});
		btnModifyCourse.setBounds(200, 75, 150, 150);
		btnModifyCourse.setText("修改课程信息");
		
		Button btnBack = new Button(shellAdminMainPage, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				Login loginWindow=new Login();
				shellAdminMainPage.dispose();
				loginWindow.open();
			}
		});
		btnBack.setBounds(132, 275, 98, 30);
		btnBack.setText("返回");
		
		Button btnExit = new Button(shellAdminMainPage, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellAdminMainPage.dispose();
			}
		});
		btnExit.setBounds(317, 275, 98, 30);
		btnExit.setText("退出");
	}
}
