import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class GarbledEmail {

    private static Set<String> dict;
    private static ArrayList<String> wlist;
    private static int[][] memo;
    private static String str;

    public static void main(String[] args) {
        wlist = new ArrayList<>();
        try (Scanner fin = new Scanner(new File("garbled_email_dictionary.txt"))) {
            while (fin.hasNext()) {
                String word = fin.next();
                wlist.add(word);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        dict = new HashSet<>(wlist);

        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        scanner.nextLine();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void process(Scanner scanner) {
        memo = new int[5000][10];
        for (int[] row : memo) {
            for (int j = 0; j < row.length; j++) {
                row[j] = -1;
            }
        }
        str = scanner.nextLine();
        System.out.println(go(0, 0));
    }

    private static int go(int a, int dist) {
        if (a == str.length()) {
            return 0;
        }

        if (memo[a][dist] != -1) {
            return memo[a][dist];
        }
        String tt = str.substring(a);

        int ret = -2;
        for (String w : wlist) {
            if (w.length() > tt.length()) {
                continue;
            }

            int tmp = 0;
            int dd = dist;
            for (int j = 0; j < w.length(); j++) {
                if (tt.charAt(j) != w.charAt(j)) {
                    tmp++;
                    if (dd > 0) {
                        dd = -1;
                        break;
                    } else {
                        dd = 5;
                    }
                }
                if (dd > 0) {
                    dd--;
                }
            }
            if (dd == -1) {
                continue;
            }

            int tmp2 = go(a + w.length(), dd);
            if (tmp2 < 0) {
                continue;
            }

            tmp += tmp2;
            if (ret == -2 || ret > tmp) {
                ret = tmp;
            }
        }
        memo[a][dist] = ret;
        return ret;
    }
}
