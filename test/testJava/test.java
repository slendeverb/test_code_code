import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;

public class test {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner in = new Scanner(new File("C:/Users/slendeverb/Documents/code_code/test/in.txt"));
        PrintStream printStream = new PrintStream(new File("C:/Users/slendeverb/Documents/code_code/test/out.txt"));
        PrintStream oldPrintStream = System.out;
        System.setOut(printStream);
        int T = in.nextInt();
        while (T-- != 0) {
            solve(in);
        }
        in.close();
        printStream.flush();
        printStream.close();
        System.setOut(oldPrintStream);
    }

    private static void solve(Scanner in) {
        int n = in.nextInt();
        ArrayList<Integer> arrayListOfN = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            arrayListOfN.add(in.nextInt());
        }
        for (Integer integer : arrayListOfN) {
            System.out.print(integer.toString() + " ");
        }
        System.out.println();

        int m = in.nextInt();
        ArrayList<Integer> arrayListOfM = new ArrayList<>();
        for (int i = 1; i <= m; i++) {
            arrayListOfM.add(in.nextInt());
        }
        for (Integer integer : arrayListOfM) {
            System.out.print(integer.toString() + " ");
        }
        System.out.println();
    }
}