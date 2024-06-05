package game.minesweep;

import java.io.Serializable;

//用于保存记录 目前未实现
public class GameRecord implements Serializable{

	
	private int length;
	private int mineNum;
	private int time;
	private boolean isWon;
	private int score;
	private int mode;

	public GameRecord(int length, int mineNum, int time, boolean isWon, int mode) {
		this.length = length;
		this.mineNum = mineNum;
		this.time = time;
		this.isWon = isWon;
		this.mode = mode;
		if (isWon == true) {
			score = length * length * 10 + mineNum * 15 - time * 2;
		} else {
			score = 0;
		}//根据输赢和相应数据给出得分  目前的得分公式仅作示意
	}

	//根据得分区间获得称号
	String showAchievement() {
		if (isWon) {
			if (score >= 0 && score <= 1700) {
				return "安全着陆";
			} else if (score > 1700 && score <= 2000) {
				return "传奇机长";
			} else if (score > 2000) {
				return "耐炸王";
			}
		}
		else{return "坠机";}
		return "错误";

	}
    String showWon() {
    	if(isWon) {
    		return "成功";
    	}
    	else {
    		return "失败";
    	}
    }
	String showMode() {
		if (mode == 0) {
			return " 简单";
		} else if (mode == 1) {
			return " 一般";
		} else if (mode == 2) {
			return " 困难";
		} else {
			return "自定义";
		}
	}

	@Override
	public String toString() {
		return "模式: " + showMode() +"   用时: "+ time+"秒"+ "   游戏结果： " + showWon()
				  + "   得分: " + score + "   获得成就: "+showAchievement();
	}

}
