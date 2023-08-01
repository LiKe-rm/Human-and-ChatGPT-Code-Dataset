import java.util.ArrayList;
import java.util.List;

public class CandidatesSelection {
    private static boolean isOrder(List<Integer> a) {
        for (int i = 1; i < a.size(); i++) {
            if (a.get(i) < a.get(i - 1)) {
                return false;
            }
        }
        return true;
    }

    public static String possible(List<String> score, List<Integer> result) {
        int m = score.get(0).length();
        List<List<Integer>> gs = new ArrayList<>();
        gs.add(result);

        while (true) {
            boolean all = true;

            for (List<Integer> g : gs) {
                if (!isOrder(g)) {
                    all = false;
                    break;
                }
            }

            if (all) {
                return "Possible";
            }

            boolean findOne = false;

            for (int i = 0; i < m; i++) {
                boolean fail = false;
                boolean change = false;
                List<List<Integer>> gs2 = new ArrayList<>();

                for (List<Integer> v : gs) {
                    List<Integer> cur = new ArrayList<>();
                    cur.add(v.get(0));

                    for (int k = 1; k < v.size(); k++) {
                        if (score.get(v.get(k)).charAt(i) < score.get(v.get(k - 1)).charAt(i)) {
                            fail = true;
                            break;
                        }

                        if (score.get(v.get(k)).charAt(i) != score.get(v.get(k - 1)).charAt(i)) {
                            change = true;
                            gs2.add(cur);
                            cur = new ArrayList<>();
                        }

                        cur.add(v.get(k));
                    }

                    gs2.add(cur);

                    if (fail) {
                        break;
                    }
                }

                if (!fail && change) {
                    gs = gs2;
                    findOne = true;
                    break;
                }
            }

            if (!findOne) {
                return "Impossible";
            }
        }
    }

    public static void main(String[] args) {
        List<String> score = List.of("CC", "AA", "BB");
        List<Integer> result = List.of(1, 2, 0);
        System.out.println(possible(score, result));
    }
}
