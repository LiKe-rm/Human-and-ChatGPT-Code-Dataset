import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.function.Consumer;

public class Shell {
    private static final int LINE_SIZE = 256;
    private static final int N_FUNCTIONS = 32;

    private List<String[]> cbsName = new ArrayList<>();
    private List<Consumer<Stack>> cbs = new ArrayList<>();
    private InputStream in;
    private PrintStream out;
    private String[][] history = new String[4][];
    private int historyPos = 0;
    private boolean gotName = false;
    private String currentObject;

    public Shell() {
        this(System.in, System.out);
    }

    public Shell(InputStream in, OutputStream out) {
        this.in = in;
        this.out = new PrintStream(out);

        add(s -> {
            int a = s.pop().toInt();
            int b = s.pop().toInt();
            s.push(a + b);
        }, "+");

        add(s -> {
            Object o = s.pop();
            out.println("# " + o.toInt());
        }, ".");

        add(s -> s.push(1), "on");

        add(s -> s.push(0), "off");
    }

    public void add(Consumer<Stack> cb, String name1, String name2) {
        cbsName.add(new String[]{name1, name2});
        cbs.add(cb);
        if (cbs.size() == N_FUNCTIONS) {
            throw new RuntimeException("Too many functions");
        }
    }

    public void add(Consumer<Stack> cb, String name1) {
        add(cb, name1, null);
    }

    // The rest of the Shell class implementation
    // ...

}
