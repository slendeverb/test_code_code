package game.minesweep;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.jface.resource.LocalResourceManager;
import org.eclipse.jface.resource.JFaceResources;
import org.eclipse.jface.resource.ColorDescriptor;
import org.eclipse.swt.graphics.RGB;
import org.eclipse.swt.widgets.Text;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.jface.resource.FontDescriptor;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Image;
import java.time.LocalDateTime;

//最重要的算法部分  设置鼠标监听器来根据左右键的不同进行不同处理 

//！！！！！！！！！该算法目前仍有bug  出错情况为当生成地雷图极小时发生错误自动退出  可能与地雷图生成算法有关
//初步测试 认为该bug的出现是和地雷生成算法中在首次左击九宫格内不生成雷有关  如果更改的话  可能也会出现无解情况  目前想法是保留地雷生成算法  在自定义模式中细化数据合法规则

@SuppressWarnings("unused")
public class MouseClick implements MouseListener {

	private LocalResourceManager localResourceManager;
	protected Shell shell;

	Button button;
	Button[][] minediagram;
	MineGenerating mineGen;
	boolean[] firstClick;
	int posX;
	int posY;
	GameTime gameTimer;
	Label mineNum;
	int[] restNum;
	int[] restNonNum;
	int totalNum;
	Label tishi;
	int mode;
	String modeRecord;
	AudioPlayer bgm;

	public MouseClick(Button button, Button[][] minediagram, MineGenerating mineGen, boolean[] firstClick, int posX,
			int posY, GameTime gameTimer, Label mineNum, int[] restNum, int[] restNonNum, Label tishi, int mode,
			AudioPlayer bgm) {
		this.button = button;
		this.minediagram = minediagram;
		this.mineGen = mineGen;
		this.firstClick = firstClick;// 设置标记用来记录第一次左击
		this.posX = posX;
		this.posY = posY;
		this.gameTimer = gameTimer;// 计时器
		this.mineNum = mineNum;
		this.restNum = restNum;// 剩余地雷数，为玩家提供地雷计数
		this.totalNum = restNum[0];
		this.restNonNum = restNonNum;// 剩余非地雷的地块数，用来判断游戏是否过关
		this.tishi = tishi;
		this.mode = mode;
		this.bgm = bgm;
		shell = new Shell();
		localResourceManager = new LocalResourceManager(JFaceResources.getResources(), shell);

		if (mode == 0) {
			modeRecord = "简单";
		} else if (mode == 1) {
			modeRecord = "一般";
		} else if (mode == 2) {
			modeRecord = "困难";
		} else {
			modeRecord = "自定义";
		}
	}// 目前传入参数过多，之后应该能精简

	@Override
	public void mouseDoubleClick(MouseEvent e) {
		// 不需要实现
	}

	AudioPlayer man = new AudioPlayer("src/main/java/game/minesweep/man.wav");
	AudioPlayer manbaOut = new AudioPlayer("src/main/java/game/minesweep/manba out.wav");
	AudioPlayer whatcanic = new AudioPlayer("src/main/java/game/minesweep/what can i say.wav");
	AudioPlayer win = new AudioPlayer("src/main/java/game/minesweep/win.wav");

	@Override
	public void mouseDown(MouseEvent e) {
		if (e.button == 1 && !button.getBackground()
				.equals(localResourceManager.create(ColorDescriptor.createFrom(new RGB(147, 112, 219))))) { // 左键点击
			if (firstClick[0]) {
				bgm.loopPlay();
				mineGen.MineSetting(posX, posY);
				firstClick[0] = false;
				gameTimer.start();

			}

			// 首次左击后，根据该坐标生成地雷图，关闭标记，启动计时器，打开背景音乐并设为循环播放

			if (mineGen.ShowMine(posX, posY) == -1) {
				showAllMines();
				disableAllButtons();
				manbaOut.play();
				gameTimer.stop();
				// 左击到地雷，游戏失败，展示所有地雷的位置，禁用所有按钮，计时器停止
				tishi.setText("你不小心触碰了雷区，老大还是坠机了");
				// 游戏结算 记录数据
				GameRecord record = new GameRecord(mineGen.ShowMaxi(), totalNum, gameTimer.showTime(), false,
						modeRecord);
				new GameRecordDAO(record).insert();

			} else {
				man.play();
				LeftClick(posX, posY);
				if (restNonNum[0] == 0 && restNum[0] == 0) {
					gameTimer.stop();
					disableAllButtons();
					bgm.pause();
					win.play();
					// 所有地块均已正确标识 游戏通关 计时器停止 播放胜利结算音效 禁用所有按钮
					tishi.setText("你已清除空中雷区，成功拯救了老大！");
					// 游戏结算 记录数据
					GameRecord record = new GameRecord(mineGen.ShowMaxi(), totalNum, gameTimer.showTime(), true,
							modeRecord);
					new GameRecordDAO(record).insert();

				}

			}
		} else if (e.button == 3) { // 右键点击
			whatcanic.play();
			if (button.getBackground()
					.equals(localResourceManager.create(ColorDescriptor.createFrom(new RGB(147, 112, 219))))) {
				button.setBackground(
						(Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(255, 153, 102))));
				restNum[0]++;
				mineNum.setText("雷数： " + restNum[0]);// 提供撤回操作
			} else {
				button.setBackground(
						(Color) localResourceManager.create(ColorDescriptor.createFrom(new RGB(147, 112, 219))));
				restNum[0]--;
				mineNum.setText("雷数： " + restNum[0]);// 标记该地块有地雷 并将剩余地雷数打印
				if (restNonNum[0] == 0 && restNum[0] == 0) {
					gameTimer.stop();
					disableAllButtons();
					bgm.pause();
					win.play();
					// 所有地块均已正确标识 游戏通关 计时器停止 播放胜利结算音效 禁用所有按钮
					tishi.setText("你已清除空中雷区，成功拯救了老大！");
					// 游戏结算 记录数据
					GameRecord record = new GameRecord(mineGen.ShowMaxi(), totalNum, gameTimer.showTime(), true,
							modeRecord);
					new GameRecordDAO(record).insert();

				}
			}
		}
	}

	@Override
	public void mouseUp(MouseEvent e) {
		// 如果需要处理鼠标松开事件
	}

	private void LeftClick(int posX, int posY) {
		Button currentButton = minediagram[posX][posY];
		currentButton
				.setFont((Font) localResourceManager
						.create(FontDescriptor.createFrom("Microsoft YaHei UI", 9, SWT.BOLD)));
		if (!currentButton.isEnabled())
			return; // 防止重复点击

		currentButton.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_TITLE_INACTIVE_BACKGROUND));
		int mineCount = mineGen.ShowMine(posX, posY);

		if (mineCount != 0) {
			currentButton.setText(Integer.toString(mineCount));

			currentButton.setEnabled(false); // 禁用按钮，防止重复点击
			restNonNum[0]--; // 剩余空地块减一

			return;
		} else {
			currentButton.setEnabled(false); // 禁用按钮，防止重复点击
			restNonNum[0]--; // 剩余空地块减一

		}

		for (int m = Math.max(0, posX - 1); m <= Math.min(mineGen.ShowMaxi() - 1, posX + 1); m++) {
			for (int n = Math.max(0, posY - 1); n <= Math.min(mineGen.ShowMaxj() - 1, posY + 1); n++) {
				if (m != posX || n != posY) {
					LeftClick(m, n);
				}
			}
		}
		// 通过递归实现如下操作：如果左击的地块的九宫格中都没有雷，则自动打开周围地块
	}

	private void showAllMines() {
		for (int i = 0; i < mineGen.ShowMaxi(); i++) {
			for (int j = 0; j < mineGen.ShowMaxj(); j++) {
				if (mineGen.ShowMine(i, j) == -1) {
					minediagram[i][j].setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_GREEN));
				}
			}
		}
	}// 显示所有地雷所在地块

	private void disableAllButtons() {
		for (int i = 0; i < mineGen.ShowMaxi(); i++) {
			for (int j = 0; j < mineGen.ShowMaxj(); j++) {
				minediagram[i][j].setEnabled(false);
			}
		}
	}
}// 禁用所有按钮 游戏结束
