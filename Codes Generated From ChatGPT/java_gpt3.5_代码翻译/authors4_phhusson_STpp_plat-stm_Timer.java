import java.util.HashMap;
import java.util.Map;
import java.util.function.Consumer;

public class Timer {
    private final int number;
    private final TIM_TypeDef base;
    private static final Map<Integer, Consumer<Integer>> topCBs = new HashMap<>();

    public Timer(TIM_TypeDef base, int number) {
        this.base = base;
        this.number = number;

        // Perform initialization logic based on the timer number
        // ...
    }

    public int getNumber() {
        return number;
    }

    // Implement the rest of the methods similarly to the C++ code
    // ...

    public static void callTopCb(int nr) {
        topCBs.get(nr).accept(nr);
    }

    public Timer setTopCB(Consumer<Integer> cb) {
        topCBs.put(number, cb);
        return this;
    }

    // Implement other required classes or interfaces, such as TIM_TypeDef
    // ...
}
