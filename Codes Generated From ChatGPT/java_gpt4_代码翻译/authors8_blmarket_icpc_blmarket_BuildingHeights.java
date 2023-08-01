import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class BuildingHeights {

    public static int minimum(List<Integer> heights) {
        List<Long> prefixSums = new ArrayList<>();
        Collections.sort(heights);
        prefixSums.add(0L);
        int n = heights.size();

        for (int i = 0; i < n; i++) {
            prefixSums.add(prefixSums.get(prefixSums.size() - 1) + heights.get(i));
        }

        int ret = 0;

        for (int i = 1; i < n; i++) {
            int minDiff = Integer.MAX_VALUE;

            for (int j = 0; j + i < n; j++) {
                long sum = heights.get(j + i) * (i + 1) - (prefixSums.get(j + i + 1) - prefixSums.get(j));

                if (sum < minDiff) {
                    minDiff = (int) sum;
                }
            }
            ret ^= minDiff;
        }
        return ret;
    }

    public static void main(String[] args) {
        List<Integer> heights = new ArrayList<>();
        heights.add(1);
        heights.add(2);
        heights.add(3);
        heights.add(4);
        heights.add(5);

        System.out.println(minimum(heights));
    }
}
