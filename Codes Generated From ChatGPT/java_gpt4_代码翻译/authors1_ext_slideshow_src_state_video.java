import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.TimeUnit;

public class VideoState extends State {
    private String filename;
    private Process mplayerProcess;
    private PrintWriter mplayerInput;
    private BufferedReader mplayerOutput;

    public VideoState(State state, String filename) {
        super(state);
        this.filename = filename;
        init();
    }

    @Override
    public State action(boolean flip) {
        if (mplayerProcess == null) {
            return new SwitchState(null); // Provide an appropriate constructor argument
        }

        mplayerInput.println("get_property filename");
        mplayerInput.flush();

        try {
            while (true) {
                String ans = readMplayerOutput();

                if (ans == null) {
                    continue;
                }

                if ("ANS_ERROR=PROPERTY_UNAVAILABLE".equals(ans)) {
                    return new SwitchState(null); // Provide an appropriate constructor argument
                }

                return this;
            }
        } catch (IOException e) {
            e.printStackTrace();
            return new SwitchState(null); // Provide an appropriate constructor argument
        }
    }

    private String readMplayerOutput() throws IOException {
        if (mplayerOutput.ready()) {
            String line = mplayerOutput.readLine();
            if (line.startsWith("ANS_")) {
                return line;
            } else {
                System.out.println("mplayer: " + line);
            }
        }
        return null;
    }

    private void init() {
        ProcessBuilder builder = new ProcessBuilder("mplayer", "-slave", "-idle", "-quiet",
                "-msglevel", "all=-1:global=4", "-fs", "-");
        builder.redirectErrorStream(true);

        try {
            mplayerProcess = builder.start();
            mplayerInput = new PrintWriter(new OutputStreamWriter(mplayerProcess.getOutputStream()));
            mplayerOutput = new BufferedReader(new InputStreamReader(mplayerProcess.getInputStream()));

            String videoPath = new File(filename).toPath().toString();
            mplayerInput.println("loadfile " + videoPath);
            mplayerInput.flush();
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("no mplayer process, cannot play video");
            mplayerProcess = null;
        }
    }

    public void cleanup() {
        if (mplayerProcess != null) {
            mplayerInput.println("quit");
            mplayerInput.flush();

            try {
                mplayerProcess.waitFor(3, TimeUnit.SECONDS);
                mplayerProcess.destroy();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void poll() {
        if (mplayerProcess == null || !mplayerProcess.isAlive()) {
            return;
        }

        try {
            String ans = readMplayerOutput();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
