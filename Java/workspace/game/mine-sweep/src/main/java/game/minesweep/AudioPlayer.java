package game.minesweep;
import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;
//用于播放音效
public class AudioPlayer {
	 private Clip clip;
	    private boolean isPaused;
	    private int pausePosition;
	    public AudioPlayer(String filePath) {
	        try {
	            AudioInputStream audioStream = AudioSystem.getAudioInputStream(new File(filePath));
	            clip = AudioSystem.getClip();
	            clip.open(audioStream);
	        } catch (UnsupportedAudioFileException | IOException | LineUnavailableException e) {
	            e.printStackTrace();
	        }
	    }

	    public void play() {
	        if (isPaused) {
	            clip.setFramePosition(pausePosition);
	            isPaused = false;
	        } else {
	            clip.setFramePosition(0);
	        }
	        clip.start();
	    }
	    
	    public void loopPlay() {
	        if (isPaused) {
	            clip.setFramePosition(pausePosition);
	            isPaused = false;
	        } else {
	            clip.setFramePosition(0);
	        }
	        clip.loop(Clip.LOOP_CONTINUOUSLY); 
	    }//循环播放

	    public void pause() {
	        if (clip.isRunning()) {
	            pausePosition = clip.getFramePosition();
	            clip.stop();
	            isPaused = true;
	        }
	    }

	    public void stop() {
	        clip.stop();
	        clip.setFramePosition(0);
	        isPaused = false;
	    }
}
