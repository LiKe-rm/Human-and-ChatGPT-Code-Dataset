import java.util.*;

public class BallsSeparating {

    public int minOperations(int[] red, int[] green, int[] blue) {
        int n = red.length;
        int ret = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    for (int k = 0; k < n; k++) {
                        if (k != i && k != j) {
                            int tmp = 0;
                            for (int a = 0; a < n; a++) {
                                int[] state = {red[a], green[a], blue[a]};
                                int sum = red[a] + green[a] + blue[a];
                                int pick = -1;
                                if (a == i) {
                                    pick = 0;
                                } else if (a == j) {
                                    pick = 1;
                                } else if (a == k) {
                                    pick = 2;
                                }
                                if (pick == -1) {
                                    pick = 0;
                                    if (green[a] > red[a]) {
                                        pick = 1;
                                    }
                                    if (blue[a] > state[pick]) {
                                        pick = 2;
                                    }
                                }
                                tmp += sum - state[pick];
                            }
                            if (ret == -1 || ret > tmp) {
                                ret = tmp;
                            }
                        }
                    }
                }
            }
        }
        return ret;
    }

    public static void main(String[] args) {
        BallsSeparating test = new BallsSeparating();
        System.out.println(test.minOperations(new int[]{1, 1, 1}, new int[]{1, 1, 1}, new int[]{1, 1, 1})); // 6
        System.out.println(test.minOperations(new int[]{5}, new int[]{6}, new int[]{8})); // -1
        System.out.println(test.minOperations(new int[]{4, 6, 5, 7}, new int[]{7, 4, 6, 3}, new int[]{6, 5, 3, 8})); // 37
        System.out.println(test.minOperations(new int[]{7, 12, 9, 9, 7}, new int[]{7, 10, 8, 8, 9}, new int[]{8, 9, 5, 6, 13})); // 77
        System.out.println(test.minOperations(new int[]{842398, 491273, 958925, 849859, 771363, 67803, 184892, 391907, 256150, 75799}, new int[]{268944, 342402, 894352, 228640, 903885, 908656, 414271, 292588, 852057, 889141}, new int[]{662939, 340220, 600081, 390298, 376707, 372199, 435097, 40266, 145590, 505103})); // 7230607
    }
}
