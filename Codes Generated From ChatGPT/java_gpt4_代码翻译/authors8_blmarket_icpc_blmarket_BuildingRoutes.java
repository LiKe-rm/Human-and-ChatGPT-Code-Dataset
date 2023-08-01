import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class BuildingRoutes {
    public static int build(List<String> dist, int T) {
        int n = dist.size();
        int[][] dd = new int[n][n];
        int[][] ff = new int[n][n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dd[i][j] = dist.get(i).charAt(j) - '0';
            }
        }

        for (int i = 0; i < n; i++) {
            System.arraycopy(dd[i], 0, ff[i], 0, n);
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dd[i][j] > dd[i][k] + dd[k][j]) {
                        dd[i][j] = dd[i][k] + dd[k][j];
                    }
                }
            }
        }

        int ret = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    int cnt = 0;
                    for (int a = 0; a < n; a++) {
                        for (int b = 0; b < n; b++) {
                            if (a != b) {
                                if (dd[a][b] == dd[a][i] + ff[i][j] + dd[j][b]) {
                                    cnt++;
                                }
                            }
                        }
                    }
                    if (cnt >= T) {
                        ret += ff[i][j];
                    }
                }
            }
        }

        return ret;
    }

    public static void main(String[] args) {
        List<String> dist = new ArrayList<>(Arrays.asList("011", "101", "110"));
        int T = 1;
        System.out.println(build(dist, T));
    }
}
