import com.minisat.minisat.Solver;
import com.minisat.minisat.core.Lit;
import com.minisat.minisat.core.Vec;
import com.minisat.minisat.simp.SimpSolver;

public class MapleSolver {
    private SimpSolver mapleSolver;
    private Vec<Lit> lits;

    public MapleSolver() {
        this.mapleSolver = new SimpSolver();
        this.lits = new Vec<>();
        this.mapleSolver.setParsing(true);
        this.mapleSolver.setVerbosity(-1);
    }

    public void addLit(int lit0) {
        if (lit0 == 0) {
            mapleSolver.addClause(lits);
            lits.clear();
        } else {
            int var = Math.abs(lit0) - 1;
            while (var >= mapleSolver.nVars()) {
                mapleSolver.newVar();
            }
            lits.push((lit0 > 0) ? Lit.mkLit(var) : Lit.mkLit(var, true));
        }
    }

    public int startSolver() {
        mapleSolver.setParsing(false);
        mapleSolver.eliminate(true);
        Vec<Lit> dummy = new Vec<>();
        Solver.Lbool ret = mapleSolver.solveLimited(dummy);

        return ret.equals(Solver.Lbool.l_True) ? 1 : 0;
    }

    public int getBinding(int varNum) {
        if (varNum > mapleSolver.model.size()) {
            return 0;
        }
        return mapleSolver.model.get(varNum - 1).equals(Solver.Lbool.l_True) ? 1 : 0;
    }
}
