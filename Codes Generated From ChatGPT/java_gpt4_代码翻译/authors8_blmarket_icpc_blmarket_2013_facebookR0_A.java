import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int T = Integer.parseInt(br.readLine().trim());
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(br);
        }
    }

    private static void process(BufferedReader br) throws IOException {
        String str = br.readLine().trim().toLowerCase();
        Map<Character, Integer> charCountMap = new HashMap<>();

        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c >= 'a' && c <= 'z') {
                charCountMap.put(c, charCountMap.getOrDefault(c, 0) + 1);
            }
        }

        List<Integer> counts = new ArrayList<>(charCountMap.values());
        Collections.sort(counts, Collections.reverseOrder());

        int result = 0;
        for (int i = 0; i < counts.size(); i++) {
            result += (26 - i) * counts.get(i);
        }

        System.out.println(result);
    }
}
