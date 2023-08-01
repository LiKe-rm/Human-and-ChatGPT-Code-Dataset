import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Assignment {
    public static double getCost(Vec2f a, Vec2f b) {
        return a.squareDistance(b);
    }

    public static double getCost(Vec3f a, Vec3f b) {
        return a.squareDistance(b);
    }

    public static double getCost(List<Double> a, List<Double> b) {
        if (a.size() != b.size()) {
            throw new IllegalArgumentException("Vectors must have the same size.");
        }
        int n = a.size();
        double sum = 0;
        for (int i = 0; i < n; i++) {
            double diff = a.get(i) - b.get(i);
            sum += diff * diff;
        }
        return sum;
    }

    public static <T> List<List<Double>> getCostMatrix(List<T> a, List<T> b, CostFunction<T> costFunction) {
        if (a.size() != b.size()) {
            throw new IllegalArgumentException("Vectors must have the same size.");
        }
        int n = a.size();
        List<List<Double>> costs = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            List<Double> row = new ArrayList<>(n);
            for (int j = 0; j < n; j++) {
                row.add(costFunction.getCost(a.get(i), b.get(j)));
            }
            costs.add(row);
        }
        return costs;
    }

    public static <T> List<T> match(List<T> a, List<T> b, CostFunction<T> costFunction, boolean normalize) {
        if (a.size() != b.size()) {
            throw new IllegalArgumentException("Vectors must have the same size.");
        }
        int n = a.size();
        if (normalize) {
            normalizeToLimits(a);
            normalizeToLimits(b);
        }
        List<List<Double>> costMatrix = getCostMatrix(a, b, costFunction);
        // Call the LAP algorithm to solve the assignment problem.
        int[] assignments = LapSolver.solve(costMatrix);
        List<T> matched = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            int match = assignments[i];
            matched.add(b.get(match));
        }
        return matched;
    }

    // Implement the normalization, min, max, and other utility functions here.
    // Implement the LapSolver class to solve the linear assignment problem.

    public interface CostFunction<T> {
        double getCost(T a, T b);
    }
}
