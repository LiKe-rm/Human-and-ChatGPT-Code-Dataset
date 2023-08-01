import org.sat4j.core.VecInt;
import org.sat4j.minisat.SolverFactory;
import org.sat4j.minisat.core.Solver;
import org.sat4j.specs.ContradictionException;
import org.sat4j.specs.IProblem;
import org.sat4j.specs.ISolver;
import org.sat4j.specs.TimeoutException;
import org.sat4j.specs.IVecInt;

import java.util.ArrayList;

public class MapleInterface {
    private static ISolver solver;

    public static void mapleInit() {
        solver = SolverFactory.newDefault();
        solver.setTimeout(3600);
    }

    public static void mapleAddLit(int lit0) {
        if (lit0 == 0) {
            try {
                solver.addClause(new VecInt(convertIntegers(lits)));
            } catch (ContradictionException e) {
                e.printStackTrace();
            }
            lits.clear();
        } else {
            lits.add(lit0);
        }
    }

    public static int mapleStartSolver() {
        IProblem problem = solver;
        boolean isSatisfiable = false;
        try {
            isSatisfiable = problem.isSatisfiable();
        } catch (TimeoutException e) {
            e.printStackTrace();
        }
        return isSatisfiable ? 1 : 0;
    }

    public static int mapleGetBinding(int varNum) {
        if (varNum > solver.nVars()) {
            return 0;
        }
        return solver.model(varNum - 1) ? 1 : 0;
    }

    private static ArrayList<Integer> lits = new ArrayList<>();

    private static int[] convertIntegers(ArrayList<Integer> integers) {
        int[] ret = new int[integers.size()];
        for (int i = 0; i < ret.length; i++) {
            ret[i] = integers.get(i);
        }
        return ret;
    }
}
