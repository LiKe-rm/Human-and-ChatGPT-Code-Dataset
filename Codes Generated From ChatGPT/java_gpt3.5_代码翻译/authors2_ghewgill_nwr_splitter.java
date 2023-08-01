import java.io.*;
import java.util.ArrayList;

public class DataSplitter {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.err.println("Usage: java DataSplitter <command1> <command2> ...");
            System.exit(1);
        }

        ArrayList<Process> processes = new ArrayList<>();
        ArrayList<OutputStream> outputStreams = new ArrayList<>();

        try {
            for (String command : args) {
                ProcessBuilder processBuilder = new ProcessBuilder("sh", "-c", command);
                processBuilder.redirectInput(ProcessBuilder.Redirect.PIPE);
                Process process = processBuilder.start();
                processes.add(process);
                outputStreams.add(process.getOutputStream());
            }

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = System.in.read(buffer)) != -1) {
                for (OutputStream outputStream : outputStreams) {
                    outputStream.write(buffer, 0, bytesRead);
                }
            }

            for (OutputStream outputStream : outputStreams) {
                outputStream.close();
            }

            for (Process process : processes) {
                process.waitFor();
            }

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
