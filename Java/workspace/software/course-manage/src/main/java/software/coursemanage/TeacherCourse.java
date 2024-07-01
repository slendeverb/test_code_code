package software.coursemanage;

import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;

public class TeacherCourse {

	private Teacher teacher;
	private TeacherDao teacherDao=new TeacherDao();
	
	public TeacherCourse(Teacher teacher) {
		this.teacher=teacher;
	}
	
	protected Shell shellTeacherCourse;
	private Table table;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			TeacherCourse window = new TeacherCourse(new Teacher());
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
		shellTeacherCourse.open();
		shellTeacherCourse.layout();
		while (!shellTeacherCourse.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellTeacherCourse = new Shell();
		shellTeacherCourse.setSize(786, 469);
		shellTeacherCourse.setText("课程管理系统-教师");

		table = new Table(shellTeacherCourse, SWT.BORDER | SWT.FULL_SELECTION);
		table.setBounds(41, 77, 684, 270);
		table.setHeaderVisible(true);
		table.setLinesVisible(true);
		String[] tableHeader= {"课程编号","课程名","学时","学分","开设学院"};
		for(int i=0;i<tableHeader.length;i++) {
			TableColumn tableColumn=new TableColumn(table,SWT.NONE|SWT.READ_ONLY);
			tableColumn.setText(tableHeader[i]);
			tableColumn.setMoveable(true);
		}
		ArrayList<Course> courses=teacherDao.getCourse(teacher.getID());
		for(Course course:courses) {
			TableItem item=new TableItem(table,SWT.NONE|SWT.READ_ONLY);
			item.setText(new String[] {course.getID(),course.getName(),String.valueOf(course.getHours()),String.valueOf(course.getCredits()),course.getDeptName()});
		}
		for (int i = 0; i < tableHeader.length; i++) {  
		    table.getColumn(i).pack();  
		}
		
		Label lblCourse = new Label(shellTeacherCourse, SWT.NONE);
		lblCourse.setBounds(20, 20, 76, 20);
		lblCourse.setText("所教课程: ");
		
		Button btnBack = new Button(shellTeacherCourse, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				TeacherMainPage teacherWindow=new TeacherMainPage(teacher);
				shellTeacherCourse.dispose();
				teacherWindow.open();
			}
		});
		btnBack.setBounds(166, 371, 98, 30);
		btnBack.setText("返回");
		
		Button btnExit = new Button(shellTeacherCourse, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellTeacherCourse.dispose();
			}
		});
		btnExit.setBounds(460, 371, 98, 30);
		btnExit.setText("退出");
	}
}
