import java.util.*;

public class KeyOpening {

    private static Map<Set<Integer>, Boolean> memo = new HashMap<>();
    private static int[] types = new int[205];
    private static List<List<Integer>> inside = new ArrayList<>();
    private static int N;
    private static List<Integer> result = new ArrayList<>();
    private static int[] keys = new int[205];

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void process(Scanner scanner) {
        memo.clear();
        int initialKeys = scanner.nextInt();
        N = scanner.nextInt();
        Arrays.fill(keys, 0);

        for (int i = 0; i < initialKeys; i++) {
            int tmp = scanner.nextInt();
            keys[tmp]++;
        }

        inside.clear();
        for (int i = 0; i < N; i++) {
            types[i] = scanner.nextInt();
            int tmp = scanner.nextInt();
            List<Integer> chestKeys = new ArrayList<>();
            for (int j = 0; j < tmp; j++) {
                chestKeys.add(scanner.nextInt());
            }
            inside.add(chestKeys);
        }

        Set<Integer> currentSet = new HashSet<>();
        result.clear();
        if (go(currentSet)) {
            for (int i = result.size() - 1; i >= 0; i--) {
                System.out.print((result.get(i) + 1) + " ");
            }
            System.out.println();
        } else {
            System.out.println("IMPOSSIBLE");
        }
    }

    private static boolean go(Set<Integer> current) {
        if (memo.containsKey(current)) {
            return memo.get(current);
        }

        boolean found = false;
        for (int i = 0; i < N; i++) {
            if (!current.contains(i)) {
                found = true;
                if (keys[types[i]] > 0) {
                    keys[types[i]]--;
                    current.add(i);
                    for (int key : inside.get(i)) {
                        keys[key]++;
                    }

                    boolean result = go(current);
                    if (result) {
                        KeyOpening.result.add(i);
                        return true;
                    }

                    for (int key : inside.get(i)) {
                        keys[key]--;
                    }
                    current.remove(i);
                    keys[types[i]]++;
                }
            }
        }

        if (!found) {
            return true;
        }

        memo.put(current, false);
        return false;
    }
}
