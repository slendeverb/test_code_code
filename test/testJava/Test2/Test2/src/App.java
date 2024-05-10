import java.io.*;
import java.util.regex.*;

public class App {
    public static void main(String[] args) {
        try {
            BufferedReader br = new BufferedReader(new FileReader("test\\testJava\\Test2\\Test2\\src\\App.java"));
            String line = "";
            while ((line = br.readLine()) != null) {
                parse(line);
            }
            br.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void parse(String line) {
        Pattern p = Pattern.compile("\"[\\w[ -~`!@#$%^&*()=+{}:;''<>,.?/]]*\"");
        Matcher m = p.matcher(line);
        while (m.find()) {
            System.out.println(m.group());
        }
    }
}
