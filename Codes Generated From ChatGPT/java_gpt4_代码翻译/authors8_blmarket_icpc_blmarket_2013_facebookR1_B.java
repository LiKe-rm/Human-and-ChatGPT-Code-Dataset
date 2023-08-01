import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

    private static int m, l;
    private static String k1, k2;
    private static String[] block1 = new String[105], block2 = new String[105];
    private static boolean[][] links = new boolean[105][105];
    private static boolean[] visit = new boolean[105];
    private static int[] back = new int[105];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine().trim());
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(br);
        }
    }

    private static boolean matches(String a, String b) {
        for (int i = 0; i < l; i++) {
            if (a.charAt(i) == '?' || b.charAt(i) == '?') continue;
            if (a.charAt(i) != b.charAt(i)) return false;
        }
        return true;
    }

    private static void assign(String a, String[] target) {
        for (int i = 0; i < m; i++) {
            target[i] = a.substring(i * l, (i + 1) * l);
        }
    }

    private static boolean checkFlow(int a) {
        if (visit[a]) return false;
        visit[a] = true;
        for (int i = 0; i < m; i++) {
            if (links[a][i]) {
                if (back[i] == -1 || checkFlow(back[i])) {
                    back[i] = a;
                    return true;
                }
            }
        }
        return false;
    }

    private static boolean tryFlow() {
        for (int i = 0; i < m; i++) {
            back[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                visit[j] = false;
            }
            if (!checkFlow(i)) return false;
        }
        return true;
    }

    private static boolean checkIt(int a) {
        for (int i = 0; i < m; i++) {
            links[a][i] = matches(block1[a], block2[i]);
        }
        return tryFlow();
    }

    private static void process(BufferedReader br) throws IOException {
        m = Integer.parseInt(br.readLine().trim());
        k1 = br.readLine().trim();
        l = k1.length() / m;
        k2 = br.readLine().trim();
        assign(k1, block1);
        assign(k2, block2);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                links[i][j] = matches(block1[i], block2[j]);
            }
        }

        if (!tryFlow()) {
            System.out.println("IMPOSSIBLE");
            return;
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < l; j++) {
                if (block1[i].charAt(j) == '?') {
                    for (int k = 0; k < 6; k++) {
                        char[] temp = block1[i].toCharArray();
                        temp[j] = (char) ('a' + k);
                        block1[i] = new String(temp);
                        if (checkIt(i)) break;
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            System.out.print(block1[i]);
        }
        System.out.println();
    }
}
                        
