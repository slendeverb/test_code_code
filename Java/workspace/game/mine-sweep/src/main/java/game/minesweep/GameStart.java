package game.minesweep;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;

//开始游戏选项  仅用作指南  具体游戏在NormalNode和CustomizeMode中实现

public class GameStart {

	protected Shell shell;
	private Text text;
	private Text text_length;
	private Text text_num;
	private Text text_mode;

	/**
	 * Launch the application.
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			GameStart window = new GameStart();
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
		shell.setSize(1450, 1000);
		shell.setText("SWT Application");

		text = new Text(shell, SWT.BORDER);
		text.setText("开始游戏模块");
		text.setBounds(500, 800, 150, 30);

		Button btn_back = new Button(shell, SWT.NONE);
		btn_back.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				HomePage window = new HomePage();
				window.open();
			}
		});
		btn_back.setBounds(1101, 217, 114, 34);
		btn_back.setText("返回上一页面");
		// 提供返回上级页面的途径

		text_mode = new Text(shell, SWT.BORDER);
		text_mode.setText("选择模式");
		text_mode.setBounds(592, 191, 94, 30);

		Button btn_easy = new Button(shell, SWT.NONE);
		btn_easy.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				NormalMode window = new NormalMode(9, 10);
				window.open();
			}
		});
		btn_easy.setBounds(282, 298, 114, 34);
		btn_easy.setText("简单");
		// 转向简单模式

		Button btn_middle = new Button(shell, SWT.NONE);
		btn_middle.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				NormalMode window = new NormalMode(16, 40);
				window.open();
			}
		});
		btn_middle.setText("一般");
		btn_middle.setBounds(496, 298, 114, 34);
		// 转向一般模式

		Button btn_hard = new Button(shell, SWT.NONE);
		btn_hard.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				NormalMode window = new NormalMode(22, 100);
				window.open();
			}
		});
		btn_hard.setText("困难");
		btn_hard.setBounds(684, 298, 114, 34);
		// 转向困难模式

		Button btn_customize = new Button(shell, SWT.NONE);
		btn_customize.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
				shell.dispose();
				CustomizeMode window = new CustomizeMode();
				window.open();
			}
		});
		btn_customize.setText("自定义");
		btn_customize.setBounds(891, 298, 114, 34);
		// 转向自定义模式

	}
}
