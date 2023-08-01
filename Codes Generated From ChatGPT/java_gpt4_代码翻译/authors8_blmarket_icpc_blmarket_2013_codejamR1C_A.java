import java.util.ArrayList;
import java.util.Scanner;

public class ConsonantSubstring {

    private static String str;
    private static int N;
    private static ArrayList<Integer> spos;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        scanner.nextLine();
        for (int i = 1; i <= T; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void process(Scanner scanner) {
        str = scanner.next();
        N = scanner.nextInt();
        scanner.nextLine();
        spos = new ArrayList<>();

        int cnt = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == 'a' || str.charAt(i) == 'e' || str.charAt(i) == 'o' || str.charAt(i) == 'i' || str.charAt(i) == 'u') {
                cnt = 0;
            } else {
                cnt++;
                if (cnt >= N) {
                    spos.add(i);
                }
            }
        }

        long ret = 0;
        for (int i = 0; i < str.length(); i++) {
            int pos = lowerBound(spos, i + N - 1);
            if (pos == spos.size()) break;
            int rc = str.length() - spos.get(pos);
            ret += rc;
        }
        System.out.println(ret);
    }

    private static int lowerBound(ArrayList<Integer> array, int value) {
        int low = 0;
        int high = array.size();

        while (low < high) {
            int mid = (low + high) / 2;
            if (array.get(mid) < value) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
}
