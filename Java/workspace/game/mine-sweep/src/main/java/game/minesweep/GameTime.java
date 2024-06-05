package game.minesweep;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;


//添加计时器

public class GameTime {
	private int timeCounter;
	private Label timerLabel;
	private boolean running;

	public GameTime(Label timerLabel) {
		this.timeCounter = 0;
		this.timerLabel = timerLabel;
		this.running = false;
	}

	public void start() {
		if (running) {
			return;
		}
		running = true;
		Display display = Display.getCurrent();
		Runnable timer = new Runnable() {
			@Override
			public void run() {
				if (running && !timerLabel.isDisposed()) {
					timeCounter++;
					timerLabel.setText("时间: " + timeCounter);
					display.timerExec(1000, this); 
				}
			}
		};
		display.timerExec(1000, timer); 
	}

	public void stop() {
		running = false;
	}

	public void reset() {
		timeCounter = 0;
		timerLabel.setText("时间: 0");
	}
	
	public int showTime() {
		return timeCounter;
	}
}
