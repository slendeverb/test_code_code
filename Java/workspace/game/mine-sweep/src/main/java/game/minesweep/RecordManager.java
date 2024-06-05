package game.minesweep;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

//用于记录游戏数据  未实现

public class RecordManager {
	private static final String FILE_NAME = "game_records.ser";

	public static void saveRecord(GameRecord record) {
		List<GameRecord> records = loadRecords();
		records.add(record);
		saveRecords(records);
	}

	public static List<GameRecord> loadRecords() {
		List<GameRecord> records = new ArrayList<>();
		try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(FILE_NAME))) {
			records = (List<GameRecord>) ois.readObject();
		} catch (FileNotFoundException e) {
			// Ignore, as this means no records yet.
		} catch (IOException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		return records;
	}

	private static void saveRecords(List<GameRecord> records) {
		try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_NAME))) {
			oos.writeObject(records);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
