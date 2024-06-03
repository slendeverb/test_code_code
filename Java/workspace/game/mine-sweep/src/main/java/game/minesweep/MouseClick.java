package game.minesweep;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.MouseListener;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Display;

//最重要的算法部分  设置鼠标监听器来根据左右键的不同进行不同处理 
public class MouseClick implements MouseListener {
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

	public MouseClick(Button button, Button[][] minediagram, MineGenerating mineGen, boolean[] firstClick, int posX,
			int posY, GameTime gameTimer, Label mineNum, int[] restNum, int[] restNonNum) {
		this.button = button;
		this.minediagram = minediagram;
		this.mineGen = mineGen;
		this.firstClick = firstClick;// 设置标记用来记录第一次左击
		this.posX = posX;
		this.posY = posY;
		this.gameTimer = gameTimer;// 计时器
		this.mineNum = mineNum;
		this.restNum = restNum;// 剩余地雷数，为玩家提供地雷计数
		this.restNonNum = restNonNum;// 剩余非地雷的地块数，用来判断游戏是否过关
	}// 目前传入参数过多，之后应该能精简

	@Override
	public void mouseDoubleClick(MouseEvent e) {
		// 不需要实现
	}

	@Override
	public void mouseDown(MouseEvent e) {
		if (e.button == 1 && !button.getBackground().equals(Display.getCurrent().getSystemColor(SWT.COLOR_BLUE))) { // 左键点击
			if (firstClick[0]) {
				mineGen.MineSetting(posX, posY);
				firstClick[0] = false;
				gameTimer.start();
			}
			// 首次左击后，根据该坐标生成地雷图，关闭标记，启动计时器
			if (mineGen.ShowMine(posX, posY) == -1) {
				showAllMines();
				disableAllButtons();
				gameTimer.stop();
				// 左击到地雷，游戏失败，展示所有地雷的位置，禁用所有按钮，计时器停止
			} else {
				LeftClick(posX, posY);
				if (restNonNum[0] == 0) {
					gameTimer.stop();
					disableAllButtons();
					// 剩余空地块已经全部标出 游戏通关 计时器停止 禁用所有按钮
				}
			}
		} else if (e.button == 3) { // 右键点击
			if (button.getBackground().equals(Display.getCurrent().getSystemColor(SWT.COLOR_BLUE))) {
				button.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_WHITE));
				restNum[0]++;
				mineNum.setText("剩余雷数： " + restNum[0]);// 提供撤回操作
			} else {
				button.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_BLUE));
				restNum[0]--;
				mineNum.setText("剩余雷数： " + restNum[0]);// 标记该地块有地雷 并将剩余地雷数打印
			}
		}
	}

	@Override
	public void mouseUp(MouseEvent e) {
		// 如果需要处理鼠标松开事件
	}

	private void LeftClick(int posX, int posY) {
		Button currentButton = minediagram[posX][posY];
		if (!currentButton.isEnabled())
			return; // 防止重复点击

		currentButton.setBackground(Display.getCurrent().getSystemColor(SWT.COLOR_GRAY));
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
