package software.coursemanage;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class StudentSelfInfo {

	private Student student;
	
	public StudentSelfInfo(Student student) {
		this.student=student;
	}
	
	protected Shell shellStudentSelfInfo;
	private Text textStudentID;
	private Label lblSelfInfo;
	private Label lblName;
	private Text textName;
	private Label lblGender;
	private Text textGender;
	private Label lblAge;
	private Text textAge;
	private Text textMajor;
	private Text textDept;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			StudentSelfInfo window = new StudentSelfInfo(new Student());
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
		shellStudentSelfInfo.open();
		shellStudentSelfInfo.layout();
		while (!shellStudentSelfInfo.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellStudentSelfInfo = new Shell();
		shellStudentSelfInfo.setSize(450, 345);
		shellStudentSelfInfo.setText("课程管理系统-学生");
		
		Label lblStudentID = new Label(shellStudentSelfInfo, SWT.NONE);
		lblStudentID.setBounds(62, 30, 45, 20);
		lblStudentID.setText("学号: ");
		
		textStudentID = new Text(shellStudentSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textStudentID.setBounds(128, 27, 250, 26);
		textStudentID.setText(student.getID());
		
		lblSelfInfo = new Label(shellStudentSelfInfo, SWT.NONE);
		lblSelfInfo.setBounds(10, 4, 76, 20);
		lblSelfInfo.setText("个人信息: ");
		
		lblName = new Label(shellStudentSelfInfo, SWT.NONE);
		lblName.setBounds(62, 66, 45, 20);
		lblName.setText("姓名: ");
		
		textName = new Text(shellStudentSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textName.setBounds(128, 63, 250, 26);
		textName.setText(student.getName());
		
		lblGender = new Label(shellStudentSelfInfo, SWT.NONE);
		lblGender.setBounds(62, 105, 45, 20);
		lblGender.setText("性别: ");
		
		textGender = new Text(shellStudentSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textGender.setBounds(128, 102, 250, 26);
		textGender.setText((student.getGender()=='1')?"男":"女");
		
		lblAge = new Label(shellStudentSelfInfo, SWT.NONE);
		lblAge.setBounds(62, 143, 45, 20);
		lblAge.setText("年龄: ");
		
		textAge = new Text(shellStudentSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textAge.setBounds(128, 140, 250, 26);
		textAge.setText(String.valueOf(student.getAge()));
		
		Label lblMajor = new Label(shellStudentSelfInfo, SWT.NONE);
		lblMajor.setBounds(62, 179, 45, 20);
		lblMajor.setText("专业: ");
		
		textMajor = new Text(shellStudentSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textMajor.setBounds(128, 176, 250, 26);
		textMajor.setText(student.getMajor());
		
		Label lblDept = new Label(shellStudentSelfInfo, SWT.NONE);
		lblDept.setBounds(62, 217, 45, 20);
		lblDept.setText("学院: ");
		
		textDept = new Text(shellStudentSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textDept.setBounds(128, 214, 250, 26);
		textDept.setText(student.getDeptName());
		
		Button btnBack = new Button(shellStudentSelfInfo, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				StudentMainPage studentWindow=new StudentMainPage(student);
				shellStudentSelfInfo.dispose();
				studentWindow.open();
			}
		});
		btnBack.setBounds(78, 258, 98, 30);
		btnBack.setText("返回");
		
		Button btnExit = new Button(shellStudentSelfInfo, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellStudentSelfInfo.dispose();
			}
		});
		btnExit.setBounds(250, 258, 98, 30);
		btnExit.setText("退出");
	}
}
