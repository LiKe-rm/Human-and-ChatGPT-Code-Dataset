import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

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
        int[] occ = new int[100005];
        int N, K;

        String[] input = br.readLine().split(" ");
        N = Integer.parseInt(input[0]);
        K = Integer.parseInt(input[1]);

        input = br.readLine().split(" ");
        int a = Integer.parseInt(input[0]);
        int b = Integer.parseInt(input[1]);
        int c = Integer.parseInt(input[2]);
        int r = Integer.parseInt(input[3]);

        int[] arr = new int[200005];
        arr[0] = a;
        if (a < 100005) occ[a]++;

        for (int i = 1; i < K; i++) {
            long tmp = arr[i - 1];
            tmp *= (long) b;
            tmp += c;
            tmp %= r;
            arr[i] = (int) tmp;

            if (tmp < 100005) occ[(int) tmp]++;
        }

        int j = 0;
        for (int i = K; i <= K * 2; i++) {
            while (occ[j] != 0) j++;
            arr[i] = j;
            occ[j]++;

            if (arr[i - K] < 100005) {
                if (--occ[arr[i - K]] == 0) {
                    if (j > arr[i - K]) j = arr[i - K];
                }
            }
        }

        N -= K;
        N %= (K + 1);
        System.out.println(arr[N + K - 1]);
    }
}
