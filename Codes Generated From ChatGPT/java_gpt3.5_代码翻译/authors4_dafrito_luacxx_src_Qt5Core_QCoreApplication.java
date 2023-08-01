import java.util.ArrayList;
import java.util.List;
import javax.swing.SwingUtilities;

public class QCoreApplication {
    private static QCoreApplication instance;

    private List<String> arguments;

    public QCoreApplication(String[] args) {
        this.arguments = new ArrayList<>();
        for (String arg : args) {
            this.arguments.add(arg);
        }
        instance = this;
    }

    public static QCoreApplication getInstance() {
        return instance;
    }

    public void processEvents() {
        SwingUtilities.invokeLater(() -> {
        });
    }

    public void exec() {
        try {
            while (true) {
                processEvents();
                Thread.sleep(10);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public List<String> getArguments() {
        return arguments;
    }
}
