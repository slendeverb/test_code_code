package game.minesweep;

import java.util.Random;
import java.util.ArrayList;
import java.util.Collections;

//扫雷地块的生成与地雷的安放  目前的安放方式为首次左击的九宫格内都不会设置地雷

public class MineGenerating {
	int maxi;
	int maxj;
	int maxnum;
	int[][] MineSaving;

	MineGenerating(int i, int j, int num) {
		maxi = i;
		maxj = j;
		maxnum = num;// 地雷数
		MineSaving = new int[maxi][maxj];
		for (int m = 0; m < maxi; m++) {
			for (int n = 0; n < maxj; n++) {
				MineSaving[m][n] = 0;
			}
		}
	}

	void MineSetting(int excludeX, int excludeY) {
		Random random = new Random();
		ArrayList<int[]> positions = new ArrayList<>();
		for (int i = 0; i < maxi; i++) {
			for (int j = 0; j < maxj; j++) {
				if (i >= Math.max(0, excludeX - 1) && i <= Math.min(maxi - 1, excludeX + 1)
						&& j >= Math.max(0, excludeY - 1) && j <= Math.min(maxj - 1, excludeY + 1)) {
					continue;
				} // 如果生成数位于首次左击的九宫格内则本次循环直接跳转到下次循环
				positions.add(new int[] { i, j });
			}
		}

		// 打乱列表以随机选择位置
		Collections.shuffle(positions, random);

		// 选择前 maxMines 个位置赋值为 -1 表示地雷
		for (int i = 0; i < maxnum; i++) {
			int[] pos = positions.get(i);
			MineSaving[pos[0]][pos[1]] = -1;
		}
		for (int i = 0; i < maxi; i++) {
			for (int j = 0; j < maxj; j++) {
				if (MineSaving[i][j] == -1) {
					continue;
				}
				int mineCount = 0;
				// 遍历九宫格
				for (int x = Math.max(0, i - 1); x <= Math.min(maxi - 1, i + 1); x++) {
					for (int y = Math.max(0, j - 1); y <= Math.min(maxj - 1, j + 1); y++) {
						if (MineSaving[x][y] == -1) {
							mineCount++;
						}
					}
				}
				MineSaving[i][j] = mineCount;
			}
		} // 对MineSaving数组进行如下更新：若该地块有雷，则维持-1不变 否则数值更新为该地块九宫格中的总地雷数

	}

	int ShowMine(int x, int y) {
		return MineSaving[x][y];
	}// 显示该地块的地雷情况

	int ShowMaxi() {
		return maxi;
	}

	int ShowMaxj() {
		return maxj;
	}
}
