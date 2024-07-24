package software.coursemanage;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;

import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

public class StudentCourse {

	private Student student;
	private StudentDao studentDao=new StudentDao();
	
	public StudentCourse(Student student) {
		this.student=student;
	}
	
	protected Shell shellStudentCourse;
	private Table table;
	private Text textTotalCredits;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			StudentCourse window = new StudentCourse(new Student());
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
		shellStudentCourse.open();
		shellStudentCourse.layout();
		while (!shellStudentCourse.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellStudentCourse = new Shell();
		shellStudentCourse.setSize(786, 469);
		shellStudentCourse.setText("课程管理系统-学生");
		
		table = new Table(shellStudentCourse, SWT.BORDER | SWT.FULL_SELECTION);
		table.setBounds(41, 77, 684, 270);
		table.setHeaderVisible(true);
		table.setLinesVisible(true);
		String[] tableHeader= {"课程编号","课程名","学时","学分","开设学院"};
		for(int i=0;i<tableHeader.length;i++) {
			TableColumn tableColumn=new TableColumn(table,SWT.NONE|SWT.READ_ONLY);
			tableColumn.setText(tableHeader[i]);
			tableColumn.setMoveable(true);
		}
		ArrayList<Course> courses=studentDao.getCourse(student.getID());
		for(Course course:courses) {
			TableItem item=new TableItem(table,SWT.NONE|SWT.READ_ONLY);
			item.setText(new String[] {course.getID(),course.getName(),String.valueOf(course.getHours()),String.valueOf(course.getCredits()),course.getDeptName()});
		}
		for (int i = 0; i < tableHeader.length; i++) {  
		    table.getColumn(i).pack();  
		}
		
		Label lblCourse = new Label(shellStudentCourse, SWT.NONE);
		lblCourse.setBounds(20, 20, 76, 20);
		lblCourse.setText("所学课程: ");
		
		Label lblTotalCredits = new Label(shellStudentCourse, SWT.NONE);
		lblTotalCredits.setBounds(515, 20, 76, 20);
		lblTotalCredits.setText("总学分: ");
		
		textTotalCredits = new Text(shellStudentCourse, SWT.BORDER | SWT.READ_ONLY);
		textTotalCredits.setBounds(600, 17, 73, 26);
		textTotalCredits.setText(String.valueOf(studentDao.getTotalCredits(student.getID())));
		
		Button btnBack = new Button(shellStudentCourse, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				StudentMainPage studentWindow=new StudentMainPage(student);
				shellStudentCourse.dispose();
				studentWindow.open();
			}
		});
		btnBack.setBounds(166, 371, 98, 30);
		btnBack.setText("返回");
		
		Button btnExit = new Button(shellStudentCourse, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellStudentCourse.dispose();
			}
		});
		btnExit.setBounds(460, 371, 98, 30);
		btnExit.setText("退出");
	}
}
