package software.coursemanage;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class TeacherMainPage {

	private Teacher teacher;
	
	public TeacherMainPage(Teacher teacher) {
		this.teacher=teacher;
	}
	
	protected Shell shellTeacherMainPage;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			TeacherMainPage window = new TeacherMainPage(new Teacher());
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
		shellTeacherMainPage.open();
		shellTeacherMainPage.layout();
		while (!shellTeacherMainPage.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellTeacherMainPage = new Shell();
		shellTeacherMainPage.setSize(570, 395);
		shellTeacherMainPage.setText("课程管理系统-教师");
		
		Button btnSelfInfo = new Button(shellTeacherMainPage, SWT.NONE);
		btnSelfInfo.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				TeacherSelfInfo teacherSelfInfoWindow=new TeacherSelfInfo(teacher);
				shellTeacherMainPage.dispose();
				teacherSelfInfoWindow.open();
			}
		});
		btnSelfInfo.setBounds(80, 75, 150, 150);
		btnSelfInfo.setText("查看个人信息");
		
		Button btnCourse = new Button(shellTeacherMainPage, SWT.NONE);
		btnCourse.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				TeacherCourse teacherCourseWindow=new TeacherCourse(teacher);
				shellTeacherMainPage.dispose();
				teacherCourseWindow.open();
			}
		});
		btnCourse.setBounds(317, 75, 150, 150);
		btnCourse.setText("查询所教课程");
		
		Button btnBack = new Button(shellTeacherMainPage, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				Login loginWindow=new Login();
				shellTeacherMainPage.dispose();
				loginWindow.open();
			}
		});
		btnBack.setBounds(132, 275, 98, 30);
		btnBack.setText("返回");
		
		Button btnExit = new Button(shellTeacherMainPage, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellTeacherMainPage.dispose();
			}
		});
		btnExit.setBounds(317, 275, 98, 30);
		btnExit.setText("退出");
	}
}
