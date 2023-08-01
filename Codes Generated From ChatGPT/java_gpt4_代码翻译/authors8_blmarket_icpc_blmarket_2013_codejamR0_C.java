import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Lawnmower {
    private static List<List<Integer>> matrix;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = scanner.nextInt();
        for (int i = 1; i <= t; i++) {
            System.out.printf("Case #%d: ", i);
            process(scanner);
        }
        scanner.close();
    }

    private static void process(Scanner scanner) {
        int n = scanner.nextInt();
        int m = scanner.nextInt();

        matrix = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            List<Integer> row = new ArrayList<>();
            for (int j = 0; j < m; j++) {
                row.add(scanner.nextInt());
            }
            matrix.add(row);
        }

        if (canMow()) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
    }

    private static boolean canMow() {
        if (matrix.isEmpty()) {
            return true;
        }

        int smallest = 101;
        for (List<Integer> row : matrix) {
            for (int element : row) {
                smallest = Math.min(smallest, element);
            }
        }

        for (int i = 0; i < matrix.size(); i++) {
            boolean good = true;
            for (int j = 0; j < matrix.get(i).size(); j++) {
                if (matrix.get(i).get(j) != smallest) {
                    good = false;
                    break;
                }
            }
            if (good) {
                matrix.remove(i);
                return canMow();
            }
        }

        for (int i = 0; i < matrix.get(0).size(); i++) {
            boolean good = true;
            for (List<Integer> row : matrix) {
                if (row.get(i) != smallest) {
                    good = false;
                    break;
                }
            }
            if (good) {
                for (List<Integer> row : matrix) {
                    row.remove(i);
                }
                return canMow();
            }
        }

        return false;
    }
}
