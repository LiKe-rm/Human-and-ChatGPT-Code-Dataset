import java.util.*;

public class BigO {
    static final int MAXN = 55;
    boolean[][] gg = new boolean[MAXN][MAXN];
    boolean[][] mm = new boolean[MAXN][MAXN];
    int[] cnt = new int[MAXN];
    int n;

    int go(int a) {
        if (cnt[a] != -1) return cnt[a];
        int ret = 0;
        for (int i = 0; i < n; i++)
            if (mm[i][i] && mm[a][i] && !mm[i][a]) {
                int tmp = go(i) + 1;
                ret = Math.max(ret, tmp);
            }
        return cnt[a] = ret;
    }

    public int minK(List<String> graph) {
        n = graph.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                gg[i][j] = mm[i][j] = (graph.get(i).charAt(j) == 'Y');

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                if (mm[i][k])
                    for (int j = 0; j < n; j++)
                        if (mm[k][j])
                            mm[i][j] = true;

        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++)
                if (gg[i][j] && mm[j][i]) count++;
            if (count >= 2) return -1;
        }

        Arrays.fill(cnt, -1);

        int ret = 0;
        for (int i = 0; i < n; i++)
            if (cnt[i] == -1 && mm[i][i]) {
                int tmp = go(i);
                ret = Math.max(ret, tmp);
            }
        return ret;
    }

    public static void main(String[] args) {
        BigO bigO = new BigO();
        List<String> graph = Arrays.asList(
                "NYY",
                "YNY",
                "YYN"
        );
        System.out.println(bigO.minK(graph));
    }
}
