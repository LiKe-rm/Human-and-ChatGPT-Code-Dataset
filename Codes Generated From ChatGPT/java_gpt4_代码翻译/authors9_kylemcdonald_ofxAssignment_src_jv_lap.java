import java.util.Arrays;

public class LAP {

    private static final int BIG = Integer.MAX_VALUE;

    public static int lap(int dim, int[][] assignCost, int[] rowSol, int[] colSol, int[] u, int[] v) {

        int[] free = new int[dim];
        int[] collist = new int[dim];
        int[] matches = new int[dim];
        int[] d = new int[dim];
        int[] pred = new int[dim];

        for (int i = 0; i < dim; i++) {
            matches[i] = 0;
        }

        for (int j = dim - 1; j >= 0; j--) {
            int min = assignCost[0][j];
            int imin = 0;
            for (int i = 1; i < dim; i++) {
                if (assignCost[i][j] < min) {
                    min = assignCost[i][j];
                    imin = i;
                }
            }
            v[j] = min;

            if (++matches[imin] == 1) {
                rowSol[imin] = j;
                colSol[j] = imin;
            } else {
                colSol[j] = -1;
            }
        }

        int numFree = 0;
        for (int i = 0; i < dim; i++) {
            if (matches[i] == 0) {
                free[numFree++] = i;
            } else if (matches[i] == 1) {
                int j1 = rowSol[i];
                int min = BIG;
                for (int j = 0; j < dim; j++) {
                    if (j != j1) {
                        if (assignCost[i][j] - v[j] < min) {
                            min = assignCost[i][j] - v[j];
                        }
                    }
                }
                v[j1] -= min;
            }
        }

        int loopCnt = 0;
        do {
            loopCnt++;

            int k = 0;
            int prvNumFree = numFree;
            numFree = 0;

            while (k < prvNumFree) {
                int i = free[k];
                k++;

                int umin = assignCost[i][0] - v[0];
                int j1 = 0;
                int usubmin = BIG;

                for (int j = 1; j < dim; j++) {
                    int h = assignCost[i][j] - v[j];
                    if (h < usubmin) {
                        if (h >= umin) {
                            usubmin = h;
                            j2 = j;
                        } else {
                            usubmin = umin;
                            umin = h;
                            j2 = j1;
                            j1 = j;
                        }
                    }
                }

                int i0 = colSol[j1];
                if (umin < usubmin) {
                    v[j1] -= (usubmin - umin);
                } else {
                    if (i0 >= 0) {
                        j1 = j2;
                        i0 = colSol[j2];
                    }
                }

                rowSol[i] = j1;
                colSol[j1] = i;

                if (i0 >= 0) {
                    if (umin < usubmin) {
                        free[--k] = i0;
                    } else {
                        free[numFree++] = i0;
                    }
                }
            }
        } while (loopCnt < 2);
        for (int f = 0; f < numFree; f++) {
            int freeRow = free[f];
    
            for (int j = 0; j < dim; j++) {
                d[j] = assignCost[freeRow][j] - v[j];
                pred[j] = freeRow;
                collist[j] = j;
            }
    
            int low = 0;
            int up = 0;
            boolean unassignedFound = false;
            do {
                if (up == low) {
                    int last = low - 1;
    
                    int min = d[collist[up++]];
                    for (int k = up; k < dim; k++) {
                        int j = collist[k];
                        int h = d[j];
                        if (h <= min) {
                            if (h < min) {
                                up = low;
                                min = h;
                            }
                            collist[k] = collist[up];
                            collist[up++] = j;
                        }
                    }
    
                    for (int k = low; k < up; k++) {
                        if (colSol[collist[k]] < 0) {
                            int endOfPath = collist[k];
                            unassignedFound = true;
                            break;
                        }
                    }
                }
    
                if (!unassignedFound) {
                    int j1 = collist[low];
                    low++;
                    int i = colSol[j1];
                    int h = assignCost[i][j1] - v[j1] - min;
    
                    for (int k = up; k < dim; k++) {
                        int j = collist[k];
                        int v2 = assignCost[i][j] - v[j] - h;
                        if (v2 < d[j]) {
                            pred[j] = i;
                            if (v2 == min) {
                                if (colSol[j] < 0) {
                                    int endOfPath = j;
                                    unassignedFound = true;
                                    break;
                                } else {
                                    collist[k] = collist[up];
                                    collist[up++] = j;
                                }
                            }
                            d[j] = v2;
                        }
                    }
                }
            } while (!unassignedFound);
    
            for (int k = 0; k <= last; k++) {
                int j1 = collist[k];
                v[j1] += (d[j1] - min);
            }
    
            int endOfPath;
            do {
                int i = pred[endOfPath];
                colSol[endOfPath] = i;
                int j1 = endOfPath;
                endOfPath = rowSol[i];
                rowSol[i] = j1;
            } while (i != freeRow);
        }
    
        int lapCost = 0;
        for (int i = 0; i < dim; i++) {
            int j = rowSol[i];
            u[i] = assignCost[i][j] - v[j];
            lapCost += assignCost[i][j];
        }
    
        return lapCost;
    }
    
    public static void main(String[] args) {
        int dim = 4;
        int[][] assignCost = { { 10, 19, 8, 15 }, { 10, 18, 7, 17 }, { 13, 16, 9, 14 }, { 12, 19, 8, 18 } };
        int[] rowSol = new int[dim];
        int[] colSol = new int[dim];
        int[] u = new int[dim];
        int[] v = new int[dim];
    
        int lapCost = lap(dim, assignCost, rowSol, colSol, u, v);
        System.out.println("Optimal cost: " + lapCost);
        System.out.println("Row assignments: " + Arrays.toString(rowSol));
        System.out.println("Column assignments: " + Arrays.toString(colSol));
        System.out.println("Dual variables for rows (u): " + Arrays.toString(u));
        System.out.println("Dual variables for columns (v): " + Arrays.toString(v));
    }
}    
    