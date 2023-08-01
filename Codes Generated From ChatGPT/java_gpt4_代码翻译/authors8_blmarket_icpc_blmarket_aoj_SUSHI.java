import java.util.Arrays;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    private static int n, m;
    private static int[][] data = new int[25][2];
    private static int[] dp = new int[5005];

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int testCases = Integer.parseInt(br.readLine());

        for (int i = 1; i <= testCases; i++) {
            process(br);
        }
    }

    private static void process(BufferedReader br) throws IOException {
        String[] input = br.readLine().split(" ");
        n = Integer.parseInt(input[0]);
        m = Integer.parseInt(input[1]) / 100;

        for (int i = 0; i < n; i++) {
            String[] dataInput = br.readLine().split(" ");
            data[i][0] = Integer.parseInt(dataInput[0]) / 100;
            data[i][1] = Integer.parseInt(dataInput[1]);
        }

        Arrays.fill(dp, 0);
        for (int i = 1; i <= 5000; i++) {
            dp[i] = dp[i - 1];
            for (int j = 0; j < n; j++) {
                if (i >= data[j][0]) {
                    dp[i] = Math.max(dp[i], dp[i - data[j][0]] + data[j][1]);
                }
            }
        }

        if (m <= 5000) {
            System.out.println(dp[m]);
            return;
        }

        int md = 0;
        for (int i = 1; i < n; i++) {
            if (data[i][0] * data[md][1] < data[md][0] * data[i][1]) {
                md = i;
            }
        }

        int nc = (m - 5001 + data[md][0]) / data[md][0];
        int ret = nc * data[md][1];
        m -= nc * data[md][0];
        System.out.println(ret + dp[m]);
    }
}
