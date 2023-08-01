import java.io.*;
import java.util.*;

public class Main {

    private static final int[] dr = {-1, 0, 1, 0};
    private static final int[] dc = {0, -1, 0, 1};

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int cases = sc.nextInt();
        for (int cas = 0; cas < cases; cas++) {
            int N = sc.nextInt();
            int M = sc.nextInt();
            int K = sc.nextInt();
            int S = N * M;
            int ans = K;

            for (int mask = 1; mask < (1 << S); mask++) {
                if (Integer.bitCount(mask) > K)
                    continue;

                int[][] grid = new int[N][M];
                int empty = 0;
                Queue<int[]> queue = new LinkedList<>();

                for (int r = 0; r < N; r++) {
                    for (int c = 0; c < M; c++) {
                        int id = r * M + c;
                        if ((mask & (1 << id)) != 0)
                            grid[r][c] = 1;
                        else if (r == 0 || r == N - 1 || c == 0 || c == M - 1) {
                            grid[r][c] = 2;
                            empty++;
                            queue.add(new int[]{r, c});
                        }
                    }
                }

                while (!queue.isEmpty()) {
                    int[] current = queue.poll();
                    int r = current[0];
                    int c = current[1];

                    for (int d = 0; d < 4; d++) {
                        int r2 = r + dr[d];
                        int c2 = c + dc[d];
                        if (r2 >= 0 && r2 < N && c2 >= 0 && c2 < M && grid[r2][c2] == 0) {
                            grid[r2][c2] = 2;
                            empty++;
                            queue.add(new int[]{r2, c2});
                        }
                    }
                }

                if (S - empty >= K)
                    ans = Math.min(ans, Integer.bitCount(mask));
            }

            System.out.println("Case #" + (cas + 1) + ": " + ans);
        }
    }
}
