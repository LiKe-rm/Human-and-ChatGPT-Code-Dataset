import java.util.*;

public class CellRemoval {
    public int cellsLeft(int[] parent, int deletedCell) {
        if (parent[deletedCell] == -1) {
            return 0;
        }
        boolean[] leaf = new boolean[55];
        Arrays.fill(leaf, true);

        for (int i = 0; i < parent.length; i++) {
            int tmp = i;
            while (parent[tmp] != -1) {
                leaf[parent[tmp]] = false;
                tmp = parent[tmp];
            }
        }

        int ret = 0;
        for (int i = 0; i < parent.length; i++) {
            if (!leaf[i]) {
                continue;
            }
            int tmp = i;
            boolean fail = false;
            while (parent[tmp] != -1) {
                if (tmp == deletedCell) {
                    fail = true;
                    break;
                }
                tmp = parent[tmp];
            }
            ret += !fail ? 1 : 0;
        }
        return ret;
    }

    public static void main(String[] args) {
        CellRemoval cellRemoval = new CellRemoval();
        int[] test1 = {-1, 0, 0, 1, 1};
        System.out.println(cellRemoval.cellsLeft(test1, 2)); // Expected output: 2

        int[] test2 = {-1, 0, 0, 1, 1};
        System.out.println(cellRemoval.cellsLeft(test2, 1)); // Expected output: 1

        int[] test3 = {-1, 0, 0, 1, 1};
        System.out.println(cellRemoval.cellsLeft(test3, 0)); // Expected output: 0

        int[] test4 = {-1, 0, 0, 2, 2, 4, 4, 6, 6};
        System.out.println(cellRemoval.cellsLeft(test4, 4)); // Expected output: 2

        int[] test5 = {26, 2, 32, 36, 40, 19, 43, 24, 30, 13, 21, 14, 24, 21, 19, 4, 30, 10, 44, 12, 7, 32, 17, 43,
                35, 18, 7, 36, 10, 16, 5, 38, 35, 4, 13, -1, 16, 26, 1, 12, 2, 5, 18, 40, 1, 17, 38, 44, 14};
        System.out.println(cellRemoval.cellsLeft(test5, 24)); // Expected output: 14
    }
}
