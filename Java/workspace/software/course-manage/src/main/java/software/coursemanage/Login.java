package software.coursemanage;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

import java.util.Optional;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class Login {

	protected Shell shellLogin;
	private Text textUsername;
	private Text textPassword;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			Login window = new Login();
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
		shellLogin.open();
		shellLogin.layout();
		while (!shellLogin.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellLogin = new Shell();
		shellLogin.setSize(450, 300);
		shellLogin.setText("课程管理系统");
		shellLogin.setLayout(null);
		
		Label lblInfo = new Label(shellLogin, SWT.NONE);
		lblInfo.setBounds(10, 10, 312, 20);
		
		Label lblUsername = new Label(shellLogin, SWT.NONE);
		lblUsername.setBounds(60, 101, 76, 20);
		lblUsername.setText("用户名: ");
		
		textUsername = new Text(shellLogin, SWT.BORDER);
		textUsername.setBounds(142, 98, 204, 26);
		
		Label lblPassword = new Label(shellLogin, SWT.NONE);
		lblPassword.setBounds(60, 150, 76, 20);
		lblPassword.setText("密码: ");
		
		textPassword = new Text(shellLogin, SWT.BORDER);
		textPassword.setBounds(142, 147, 204, 26);
		
		Label lblChooseRole = new Label(shellLogin, SWT.NONE);
		lblChooseRole.setBounds(60, 50, 99, 20);
		lblChooseRole.setText("请选择身份: ");
		
		Combo comboChooseRole = new Combo(shellLogin, SWT.READ_ONLY);
		comboChooseRole.setBounds(192, 47, 92, 28);
		comboChooseRole.setItems(new String[] {"管理员","教师","学生"});
		
		Button btnLogin = new Button(shellLogin, SWT.NONE);
		btnLogin.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				String username=textUsername.getText();
				String password=textPassword.getText();
				String userType=comboChooseRole.getText();
				if(username.isEmpty()||password.isEmpty()) {
					lblInfo.setText("用户名和密码不能为空");
				}
				else if(userType.isEmpty()) {
					lblInfo.setText("请选择身份");
				}
				else {
					if(userType.equals(comboChooseRole.getItem(0))) {
						AdminDao adminDao=new AdminDao();
						String passwordDB=adminDao.getPassword(username);
						String userTypeDB=adminDao.getUserType(username);
						if(password==null||!userTypeDB.equals(userType)) {
							lblInfo.setText("用户不存在");
						}
						else if(!passwordDB.equals(password)) {
							lblInfo.setText("密码错误");
						}
						else {
							AdminMainPage adminWindow=new AdminMainPage();
							shellLogin.dispose();
							adminWindow.open();
						}
					}
					else if(userType.equals(comboChooseRole.getItem(1))) {
						TeacherDao teacherDao=new TeacherDao();
						Optional<Teacher> teacher=teacherDao.findTeacher(username);
						String userTypeDB=teacherDao.getUserType(username);
						if(teacher.isEmpty()||!userTypeDB.equals(userType)) {
							lblInfo.setText("用户不存在");
						}
						else {
							String passwordDB=teacherDao.getPassword(username);
							if(!passwordDB.equals(password)) {
								lblInfo.setText("密码错误");
							}
							else {
								TeacherMainPage teacherWindow=new TeacherMainPage(teacher.get());
								shellLogin.dispose();
								teacherWindow.open();
							}
						}
					}
					else if(userType.equals(comboChooseRole.getItem(2))) {
						StudentDao studentDao=new StudentDao();
						Optional<Student> student=studentDao.findStudent(username);
						String userTypeDB=studentDao.getUserType(username);
						if(student.isEmpty()||!userTypeDB.equals(userType)) {
							lblInfo.setText("用户不存在");
						}
						else {
							String passwordDB=studentDao.getPassword(username);
							if(!passwordDB.equals(password)) {
								lblInfo.setText("密码错误");
							}
							else {
								StudentMainPage studentWindow=new StudentMainPage(student.get());
								shellLogin.dispose();
								studentWindow.open();
							}
						}
					}
				}
			}
		});

		btnLogin.setBounds(60, 195, 98, 30);
		btnLogin.setText("登录");
		
		Button btnExit = new Button(shellLogin, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellLogin.dispose();
			}
		});
		btnExit.setBounds(248, 195, 98, 30);
		btnExit.setText("退出");
	}
}
