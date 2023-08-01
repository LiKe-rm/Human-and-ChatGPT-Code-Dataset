import java.io.*;
import java.util.*;

class ForkSolver {
    private int nchilds;
    private Map<Integer, Process> processes;

    public ForkSolver() {
        this.nchilds = 0;
        this.processes = new HashMap<>();
    }

    public void solve(int dataId) {
        System.out.printf("Case #%d: ", dataId);
    }

    public void process(int dataId) {
    }

    public void runSolve(int dataId) throws IOException, InterruptedException {
        while (nchilds >= 2) {
            Process completedProcess = null;
            int completedDataId = -1;
            for (Map.Entry<Integer, Process> entry : processes.entrySet()) {
                if (!entry.getValue().isAlive()) {
                    completedProcess = entry.getValue();
                    completedDataId = entry.getKey();
                    break;
                }
            }
            if (completedProcess != null) {
                nchilds--;
                processes.remove(completedDataId);
                completedProcess.waitFor();
            }
        }

        ProcessBuilder pb = new ProcessBuilder("java", "ForkSolverChild");
        Process process = pb.start();

        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(process.getOutputStream()));
        writer.write(String.valueOf(dataId));
        writer.newLine();
        writer.flush();
        writer.close();

        processes.put(dataId, process);
        nchilds++;
    }
}

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        ForkSolver solver = new ForkSolver();
        for (int i = 1; i <= N; i++) {
            solver.process(i);
            solver.runSolve(i);
        }
        for (int i = 1; i <= N; i++) {
            Process process = solver.processes.get(i);
            process.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        }
    }
}

import java.io.*;

public class ForkSolverChild {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int dataId = Integer.parseInt(reader.readLine());
        System.out.printf("Case #%d: ", dataId);
    }
}
