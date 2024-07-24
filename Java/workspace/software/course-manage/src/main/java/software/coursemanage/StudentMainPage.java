package software.coursemanage;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class StudentMainPage {
	
	private Student student;
	
	public StudentMainPage(Student student) {
		this.student=student;
	}

	protected Shell shellStudentMainPage;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			StudentMainPage window = new StudentMainPage(new Student());
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
		shellStudentMainPage.open();
		shellStudentMainPage.layout();
		while (!shellStudentMainPage.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellStudentMainPage = new Shell();
		shellStudentMainPage.setSize(570, 395);
		shellStudentMainPage.setText("课程管理系统-学生");
		
		Button btnSelfInfo = new Button(shellStudentMainPage, SWT.NONE);
		btnSelfInfo.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				StudentSelfInfo studentSelfInfoWindow=new StudentSelfInfo(student);
				shellStudentMainPage.dispose();
				studentSelfInfoWindow.open();
			}
		});
		btnSelfInfo.setBounds(80, 75, 150, 150);
		btnSelfInfo.setText("查看个人信息");
		
		Button btnCourse = new Button(shellStudentMainPage, SWT.NONE);
		btnCourse.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				StudentCourse studentCourseWindow=new StudentCourse(student);
				shellStudentMainPage.dispose();
				studentCourseWindow.open();
			}
		});
		btnCourse.setText("查询课程和成绩");
		btnCourse.setBounds(317, 75, 150, 150);
		
		Button btnExit = new Button(shellStudentMainPage, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellStudentMainPage.dispose();
			}
		});
		btnExit.setBounds(317, 275, 98, 30);
		btnExit.setText("退出");
		
		Button btnBack = new Button(shellStudentMainPage, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				Login loginWindow=new Login();
				shellStudentMainPage.dispose();
				loginWindow.open();
			}
		});
		btnBack.setBounds(132, 275, 98, 30);
		btnBack.setText("返回");
	}
}
