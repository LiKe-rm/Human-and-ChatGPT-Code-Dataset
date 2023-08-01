import java.util.*;
import java.io.*;

class Main {
    private static int n, m;
    private static Map<String, String> mapper = new HashMap<>();
    private static Map<String, Integer> dict = new HashMap<>();

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int testCases = Integer.parseInt(br.readLine());
        for (int i = 1; i <= testCases; i++) {
            process(br);
        }
    }

    private static void process(BufferedReader br) throws IOException {
        mapper.clear();
        dict.clear();

        String[] input = br.readLine().split(" ");
        n = Integer.parseInt(input[0]);
        m = Integer.parseInt(input[1]);

        for (int i = 0; i < n; i++) {
            String[] tmpInput = br.readLine().split(" ");
            String tmp = tmpInput[0];
            int tmp2 = Integer.parseInt(tmpInput[1]);

            dict.put(tmp, tmp2);
            updateDict(tmp);
        }

        int ret = 0;
        for (int i = 0; i < m; i++) {
            String tmp = br.readLine().trim();
            String tmp2 = tmp;
            boolean done = false;

            for (int j = 0; j < tmp2.length() - 1; j++) {
                if (mapper.getOrDefault(tmp2.substring(0, j + 1), "").equals(tmp2)) {
                    done = true;
                    ret += j + 1 + 1 + 1;
                    break;
                }
            }

            if (!done) {
                ret += tmp2.length() + 1;
            }
        }

        System.out.println(ret - 1);
    }

    private static void updateDict(String tmp) {
        int tmp2 = dict.get(tmp);
        String tmp3 = tmp;

        while (!tmp3.isEmpty()) {
            String oth = mapper.getOrDefault(tmp3, "");
            int occ = dict.getOrDefault(oth, 0);

            if (occ < tmp2 || (occ == tmp2 && tmp.compareTo(oth) < 0)) {
                mapper.put(tmp3, tmp);
            }
            tmp3 = tmp3.substring(0, tmp3.length() - 1);
        }
    }
}
