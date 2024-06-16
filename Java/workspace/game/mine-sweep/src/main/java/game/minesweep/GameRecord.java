package game.minesweep;

import java.io.Serializable;

//用于初步设置需要存入的数据内容
public class GameRecord implements Serializable {

	private int length;
	private int mineNum;
	private int time;
	private boolean isWon;
	private int score;
	private String mode;
	private String achievement;

	public GameRecord(int length, int mineNum, int time, boolean isWon, String mode) {
		this.length = length;
		this.mineNum = mineNum;
		this.time = time;
		this.isWon = isWon;
		this.mode = mode;
		if (isWon == true) {
			score = length * length * 10 + mineNum * 15 - time * 2;
		} else {
			score = 0;
		} // 根据输赢和相应数据给出得分 目前的得分公式仅作示意
		achievement = getAchievement();
	}

	public GameRecord() {
		// TODO 自动生成的构造函数存根
	}

	public int getLength() {
		return length;
	}

	public int getMineNum() {
		return mineNum;
	}

	public int getTime() {
		return time;
	}

	public Boolean isWon() {
		return isWon;
	}

	public int getScore() {
		return score;
	}

	public String getMode() {
		return mode;
	}

	public String getAchievement() {
		if (achievement == null) {
			if (isWon) {
				if (score >= 0 && score <= 1700) {
					return "安全着陆";
				} else if (score > 1700 && score <= 2000) {
					return "传奇机长";
				} else if (score > 2000) {
					return "耐炸王";
				}
			}
			return "坠机";
		}

		return achievement;
	}

	// Setters

	public void setLength(int length) {
		this.length = length;
	}

	public void setMineNum(int mineNum) {
		this.mineNum = mineNum;
	}

	public void setTime(int time) {
		this.time = time;
	}

	public void setWon(boolean isWon) {
		this.isWon = isWon;
	}

	public void setScore(int score) {
		this.score = score;
	}

	public void setMode(String mode) {
		this.mode = mode;
	}

	public void setAchievement(String achievement) {
		this.achievement = achievement;
	}

	@Override
	public String toString() {
		return "模式: " + getMode() + "   用时: " + getTime() + "秒" + "   游戏结果： " + isWon() + "   得分: " + score
				+ "   获得成就: " + getAchievement();
	}

}
