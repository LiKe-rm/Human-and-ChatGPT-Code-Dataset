import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(br);
        }
    }

    private static boolean type1(char a) {
        if (a >= 'a' && a <= 'z') return true;
        if (a == ' ' || a == ':') return true;
        return false;
    }

    private static void process(BufferedReader br) throws IOException {
        boolean[][] flag = new boolean[105][105];
        for (boolean[] row : flag) {
            java.util.Arrays.fill(row, false);
        }

        String str = br.readLine().trim();

        for (int j = 0; j < str.length(); j++) {
            flag[j][j] = true;
            flag[j][j + 1] = type1(str.charAt(j));
            if (str.charAt(j) == ':' && j + 1 < str.length()) {
                if (str.charAt(j + 1) == '(' || str.charAt(j + 1) == ')') {
                    flag[j][j + 2] = true;
                }
            }
        }

        for (int i = 2; i <= str.length(); i++) {
            for (int j = 0; j + i <= str.length(); j++) {
                int right = j + i - 1;
                if (str.charAt(j) == '(' && str.charAt(right) == ')') {
                    flag[j][j + i] = flag[j + 1][j + i - 1];
                }
                if (flag[j][j + i]) continue;
                for (int k = j + 1; k <= right; k++) {
                    if (flag[j][k] && flag[k][j + i]) {
                        flag[j][j + i] = true;
                        break;
                    }
                }
            }
        }

        System.out.println(flag[0][str.length()] ? "YES" : "NO");
    }
}
