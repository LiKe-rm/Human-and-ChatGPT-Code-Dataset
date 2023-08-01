import java.util.*;

public class BichromePainting {
    public String isThatPossible(String[] board, int k) {
        int n = board.length;
        boolean[][] poss = new boolean[25][25];

        for (int i = 0; i < 25; i++) {
            Arrays.fill(poss[i], false);
        }

        boolean change;
        do {
            change = false;

            for (int i = 0; i + k <= n; i++) {
                for (int j = 0; j + k <= n; j++) {
                    boolean fail = false;
                    for (int a = 0; a < k; a++) {
                        char cc = 0;
                        int ii = i + a;
                        for (int b = 0; b < k; b++) {
                            int jj = j + b;
                            if (poss[ii][jj]) continue;
                            if (cc == 0) cc = board[ii].charAt(jj);
                            if (board[ii].charAt(jj) != cc) {
                                fail = true;
                                break;
                            }
                        }
                        if (fail) break;
                    }
                    if (!fail) {
                        for (int a = 0; a < k; a++) {
                            for (int b = 0; b < k; b++) {
                                change |= !poss[i + a][j + b];
                                poss[i + a][j + b] = true;
                            }
                        }
                    }
                }
            }
        } while (change);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!poss[i][j]) {
                    return "Impossible";
                }
            }
        }
        return "Possible";
    }

    public static void main(String[] args) {
        BichromePainting test = new BichromePainting();
        String[] board1 = {"BBBW", "BWWW", "BWWW", "WWWW"};
        System.out.println(test.isThatPossible(board1, 3)); // Should output "Possible"

        String[] board2 = {"BW", "WB"};
        System.out.println(test.isThatPossible(board2, 2)); // Should output "Impossible"

        // Add more test cases as needed
    }
}
