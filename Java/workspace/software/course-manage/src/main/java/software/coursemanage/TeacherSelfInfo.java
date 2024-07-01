package software.coursemanage;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

public class TeacherSelfInfo {
	
	private Teacher teacher;
	
	public TeacherSelfInfo(Teacher teacher) {
		this.teacher=teacher;
	}

	protected Shell shellTeacherSelfInfo;
	private Text textTeacherID;
	private Label lblSelfInfo;
	private Label lblName;
	private Text textName;
	private Label lblGender;
	private Text textGender;
	private Label lblTitle;
	private Text textTitle;
	private Text textMajor;
	private Text textDept;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			TeacherSelfInfo window = new TeacherSelfInfo(new Teacher());
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
		shellTeacherSelfInfo.open();
		shellTeacherSelfInfo.layout();
		while (!shellTeacherSelfInfo.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellTeacherSelfInfo = new Shell();
		shellTeacherSelfInfo.setSize(450, 345);
		shellTeacherSelfInfo.setText("课程管理系统-教师");
		
		Label lblTeacherID = new Label(shellTeacherSelfInfo, SWT.NONE);
		lblTeacherID.setBounds(62, 30, 45, 20);
		lblTeacherID.setText("工号: ");
		
		textTeacherID = new Text(shellTeacherSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textTeacherID.setBounds(128, 27, 250, 26);
		textTeacherID.setText(teacher.getID());
		
		lblSelfInfo = new Label(shellTeacherSelfInfo, SWT.NONE);
		lblSelfInfo.setBounds(10, 4, 76, 20);
		lblSelfInfo.setText("个人信息: ");
		
		lblName = new Label(shellTeacherSelfInfo, SWT.NONE);
		lblName.setBounds(62, 66, 45, 20);
		lblName.setText("姓名: ");
		
		textName = new Text(shellTeacherSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textName.setBounds(128, 63, 250, 26);
		textName.setText(teacher.getName());
		
		lblGender = new Label(shellTeacherSelfInfo, SWT.NONE);
		lblGender.setBounds(62, 105, 45, 20);
		lblGender.setText("性别: ");
		
		textGender = new Text(shellTeacherSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textGender.setBounds(128, 102, 250, 26);
		textGender.setText((teacher.getGender()=='1')?"男":"女");
		
		lblTitle = new Label(shellTeacherSelfInfo, SWT.NONE);
		lblTitle.setBounds(62, 143, 45, 20);
		lblTitle.setText("职称: ");
		
		textTitle = new Text(shellTeacherSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textTitle.setBounds(128, 140, 250, 26);
		textTitle.setText(String.valueOf(teacher.getTitle()));
		
		Label lblMajor = new Label(shellTeacherSelfInfo, SWT.NONE);
		lblMajor.setBounds(62, 179, 45, 20);
		lblMajor.setText("专业: ");
		
		textMajor = new Text(shellTeacherSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textMajor.setBounds(128, 176, 250, 26);
		textMajor.setText(teacher.getMajor());
		
		Label lblDept = new Label(shellTeacherSelfInfo, SWT.NONE);
		lblDept.setBounds(62, 217, 45, 20);
		lblDept.setText("学院: ");
		
		textDept = new Text(shellTeacherSelfInfo, SWT.BORDER | SWT.READ_ONLY);
		textDept.setBounds(128, 214, 250, 26);
		textDept.setText(teacher.getDeptName());
		
		Button btnBack = new Button(shellTeacherSelfInfo, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				TeacherMainPage teacherWindow=new TeacherMainPage(teacher);
				shellTeacherSelfInfo.dispose();
				teacherWindow.open();
			}
		});
		btnBack.setBounds(78, 258, 98, 30);
		btnBack.setText("返回");
		
		Button btnExit = new Button(shellTeacherSelfInfo, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellTeacherSelfInfo.dispose();
			}
		});
		btnExit.setBounds(250, 258, 98, 30);
		btnExit.setText("退出");
	}
}
