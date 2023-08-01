import java.util.*;

class Main {
    private static final int MAX_SIZE = 55;
    private static int[][] nums = new int[MAX_SIZE][MAX_SIZE];
    private static boolean[][] chks = new boolean[MAX_SIZE][MAX_SIZE];
    private static int n;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int testCases = scanner.nextInt();
        for (int i = 1; i <= testCases; i++) {
            process(scanner);
        }
    }

    private static void process(Scanner scanner) {
        resetChks();
        n = scanner.nextInt();
        for (int i = 0; i < n; i++) {
            chks[i][i + 1] = true;
            nums[i][i + 1] = scanner.nextInt();
        }
        System.out.println(go(0, n));
    }

    private static int go(int s, int e) {
        if (chks[s][e]) {
            return nums[s][e];
        }

        chks[s][e] = true;
        nums[s][e] = nums[s][s + 1] - go(s + 1, e);
        int tmp;

        tmp = nums[e - 1][e] - go(s, e - 1);
        nums[s][e] = Math.max(nums[s][e], nums[e - 1][e] - go(s, e - 1));

        if (e - s >= 2) {
            nums[s][e] = Math.max(nums[s][e], -go(s, e - 2));
            nums[s][e] = Math.max(nums[s][e], -go(s + 2, e));
        }

        return nums[s][e];
    }

    private static void resetChks() {
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                chks[i][j] = false;
            }
            chks[i][i] = true;
            nums[i][i] = 0;
        }
    }
}
