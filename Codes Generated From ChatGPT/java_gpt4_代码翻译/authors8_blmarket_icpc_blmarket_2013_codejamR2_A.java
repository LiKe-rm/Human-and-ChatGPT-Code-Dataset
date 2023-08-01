import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Main {
    private static int N, M;
    private static List<Integer> s, e, f;
    private static List<Integer> ss, ee;
    private static int[][] arr = new int[1024][1024];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(sc);
            System.err.println(i);
        }
        sc.close();
    }

    private static void process(Scanner sc) {
        N = sc.nextInt();
        M = sc.nextInt();
        s = new ArrayList<>(M);
        e = new ArrayList<>(M);
        f = new ArrayList<>(M);
        for (int i = 0; i < M; i++) {
            s.add(sc.nextInt());
            e.add(sc.nextInt());
            f.add(sc.nextInt());
        }
        ss = new ArrayList<>(s);
        ee = new ArrayList<>(e);
        ss.sort(Integer::compareTo);
        ee.sort(Integer::compareTo);
        ss = removeDuplicates(ss);
        ee = removeDuplicates(ee);

        long cur = 0;
        Arrays.fill(arr, 0);
        for (int i = 0; i < M; i++) {
            long dist = e.get(i) - s.get(i);
            cur += dist * (dist - 1) * f.get(i);
            int p1 = indexOf(ss, s.get(i));
            int p2 = indexOf(ee, e.get(i));
            arr[p1][p2] += f.get(i);
        }

        long ret = 0;

        while (true) {
            boolean change = false;
            for (int i = 0; i < ss.size(); i++) {
                for (int j = 0; j < ee.size(); j++) {
                    if (arr[i][j] == 0) continue;
                    for (int ii = i + 1; ii < ss.size(); ii++) {
                        if (ee.get(j) < ss.get(ii)) continue;
                        if (arr[i][j] == 0) break;
                        for (int jj = 0; jj < ee.size(); jj++) {
                            if (arr[ii][jj] == 0) continue;
                            if (ee.get(jj) < ss.get(i)) continue;
                            if (arr[i][j] == 0) break;

                            long p1 = ee.get(j) - ss.get(i);
                            long p2 = ee.get(jj) - ss.get(ii);
                            long c1 = p1 * (p1 - 1) + p2 * (p2 - 1);

                            long p3 = ee.get(jj) - ss.get(i);
                            long p4 = ee.get(j) - ss.get(ii);
                            long c2 = p3 * (p3 - 1) + p4 * (p4 - 1);

                            if (c2 > c1) {
                                change = true;
                                int minf = Math.min(arr[i][j], arr[ii][jj]);
                                c2 -= c1;
                                c2 %= 1000002013L;
                                ret += c2 * minf;
                                ret %= 1000002013L;
                                arr[i][j] -= minf;
                                arr[ii][jj] -= minf;
                                arr[i][jj] += minf;
                                arr[ii][j] += minf;
                            }
                        }
                    }
                }
            }
            if (!change) break;
        }

        if (ret % 2 != 0) {
            ret += 1000002013L;
        }
        ret /= 2;
        ret %= 1000002013L;

        System.out.println(ret);
    }

    private static List<Integer> removeDuplicates(List<Integer> list) {
        List<Integer> newList = new ArrayList<>();
        for (Integer element : list) {
            if (!newList.contains(element)) {
                newList.add(element);
            }
        }
        return newList;
    }

    private static int indexOf(List<Integer> list, int value) {
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) == value) {
                return i;
            }
        }
        return -1;
    }
}

