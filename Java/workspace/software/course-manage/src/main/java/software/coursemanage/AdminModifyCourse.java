package software.coursemanage;

import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.TableEditor;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.graphics.Rectangle;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.events.FocusEvent;
import org.eclipse.swt.events.FocusListener;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;

public class AdminModifyCourse {
	
	private AdminDao adminDao=new AdminDao();

	protected Shell shellModifyCourse;

	private Table table;
	private Text textCourseID;
	private Text textCourseName;
	private Text textHours;
	private Text textCredits;
	private Text textDept;

	/**
	 * Launch the application.
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			AdminModifyCourse window = new AdminModifyCourse();
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
		shellModifyCourse.open();
		shellModifyCourse.layout();
		while (!shellModifyCourse.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
	}

	/**
	 * Create contents of the window.
	 */
	protected void createContents() {
		shellModifyCourse = new Shell();
		shellModifyCourse.setSize(984, 469);
		shellModifyCourse.setText("课程管理系统-管理员");
		
		String[] tableHeader= {"课程编号","课程名","学时","学分","开设学院"};
		String[] columnDB= {"CourseID","CourseName","Hours","Credits","DeptName"};
		
		table = new Table(shellModifyCourse, SWT.BORDER | SWT.FULL_SELECTION);
		table.addListener(SWT.MouseDoubleClick,new Listener() {
			int editColumn=-1;
			@Override
			public void handleEvent(Event e) {
				Point point=new Point(e.x,e.y);
				TableItem tableItem=table.getItem(point);
				if(tableItem==null) {
					return;
				}
				String courseID=tableItem.getText(0);
				for(int i=0;i<tableHeader.length;i++) {
					Rectangle r=tableItem.getBounds(i);
					if(r.contains(point)) {
						editColumn=i;
						break;
					}
				}
				TableEditor editor=new TableEditor(table);
				Control oldEditor=editor.getEditor();
				if(oldEditor!=null) {
					oldEditor.dispose();
				}
				Text text=new Text(table,SWT.NONE);
				text.computeSize(SWT.DEFAULT, table.getItemHeight());
				editor.grabHorizontal = true;
				editor.minimumHeight = text.getSize().y;
				editor.minimumWidth = text.getSize().x;
				editor.setEditor(text, tableItem, editColumn);
				text.setText(tableItem.getText(editColumn));
				text.forceFocus();
				text.addModifyListener(new ModifyListener() {
					@Override
					public void modifyText(final ModifyEvent e) {
						editor.getItem().setText(editColumn, text.getText());
					}
				});
				text.addFocusListener(new FocusListener() {
					@Override
					public void focusGained(final FocusEvent e) {}

					@Override
					public void focusLost(final FocusEvent e) {
						Control defaultEditor=editor.getEditor();
						editor.setEditor(defaultEditor, tableItem, editColumn);
						tableItem.setText(editColumn,text.getText());
						adminDao.updateCourse(courseID,text.getText(),columnDB[editColumn]);
						text.dispose();
					}
				});
			}
		});
		table.setBounds(41, 77, 684, 270);
		table.setHeaderVisible(true);
		table.setLinesVisible(true);

		for(int i=0;i<tableHeader.length;i++) {
			TableColumn tableColumn=new TableColumn(table,SWT.NONE);
			tableColumn.setText(tableHeader[i]);
			tableColumn.setMoveable(true);
		}
		ArrayList<Course> courses=adminDao.getCourse();
		for(Course course:courses) {
			TableItem item=new TableItem(table,SWT.NONE);
			item.setText(new String[] {course.getID(),course.getName(),String.valueOf(course.getHours()),String.valueOf(course.getCredits()),course.getDeptName()});
		}
		for (int i = 0; i < tableHeader.length; i++) {  
		    table.getColumn(i).pack();  
		}
		
		Label lblCourse = new Label(shellModifyCourse, SWT.NONE);
		lblCourse.setBounds(20, 20, 76, 20);
		lblCourse.setText("所有课程: ");
		
		Button btnBack = new Button(shellModifyCourse, SWT.NONE);
		btnBack.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				AdminMainPage adminWindow=new AdminMainPage();
				shellModifyCourse.dispose();
				adminWindow.open();
			}
		});
		btnBack.setBounds(166, 371, 98, 30);
		btnBack.setText("返回");
		
		Button btnExit = new Button(shellModifyCourse, SWT.NONE);
		btnExit.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shellModifyCourse.dispose();
			}
		});
		btnExit.setBounds(460, 371, 98, 30);
		btnExit.setText("退出");
		
		Label lblCourseID = new Label(shellModifyCourse, SWT.NONE);
		lblCourseID.setBounds(741, 39, 68, 20);
		lblCourseID.setText("课程编号: ");
		
		textCourseID = new Text(shellModifyCourse, SWT.BORDER);
		textCourseID.setBounds(812, 36, 144, 26);
		
		Label lblCourseName = new Label(shellModifyCourse, SWT.NONE);
		lblCourseName.setBounds(741, 101, 68, 20);
		lblCourseName.setText("课程名: ");
		
		textCourseName = new Text(shellModifyCourse, SWT.BORDER);
		textCourseName.setBounds(812, 98, 144, 26);
		
		Label lblHours = new Label(shellModifyCourse, SWT.NONE);
		lblHours.setBounds(741, 165, 68, 20);
		lblHours.setText("学时: ");
		
		textHours = new Text(shellModifyCourse, SWT.BORDER);
		textHours.setBounds(812, 162, 144, 26);
		
		Label lblCredits = new Label(shellModifyCourse, SWT.NONE);
		lblCredits.setBounds(741, 226, 68, 20);
		lblCredits.setText("学分: ");
		
		textCredits = new Text(shellModifyCourse, SWT.BORDER);
		textCredits.setBounds(812, 223, 144, 26);
		
		Label lblDept = new Label(shellModifyCourse, SWT.NONE);
		lblDept.setBounds(741, 286, 68, 20);
		lblDept.setText("开设学院: ");
		
		textDept = new Text(shellModifyCourse, SWT.BORDER);
		textDept.setBounds(812, 283, 144, 26);
		
		Button btnAdd = new Button(shellModifyCourse, SWT.NONE);
		btnAdd.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				String courseID=textCourseID.getText();
				String courseName=textCourseName.getText();
				int hours=Integer.valueOf(textHours.getText());
				int credits=Integer.valueOf(textCredits.getText());
				String deptName=textDept.getText();
				Course course=new Course(courseID,courseName,hours,credits,deptName);
				adminDao.addCourse(course);
			}
		});
		btnAdd.setBounds(800, 350, 98, 30);
		btnAdd.setText("添加");
	}

}
