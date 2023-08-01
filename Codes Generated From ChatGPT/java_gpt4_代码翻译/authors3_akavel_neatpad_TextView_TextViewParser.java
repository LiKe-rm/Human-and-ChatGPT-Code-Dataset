import java.awt.*;

class Rule {
    String ruleName;
    Color fg;
    Color bg;

    public Rule(String ruleName, Color fg, Color bg) {
        this.ruleName = ruleName;
        this.fg = fg;
        this.bg = bg;
    }
}

enum Test {
    NONE, EQUAL, NOT_EQUAL, IN_RANGE, OUT_RANGE
}

class State {
    char arg1;
    char arg2;
    Test test;
    int next;

    public State(char arg1, char arg2, Test test, int next) {
        this.arg1 = arg1;
        this.arg2 = arg2;
        this.test = test;
        this.next = next;
    }
}

public class TextViewParser {
    public static boolean init(String buf, int len) {
        return true;
    }

    public static void machine(String str, int len, int initialState) {
        State[] machine = {
                new State('a', '\0', Test.EQUAL, 0),
                new State('b', '\0', Test.EQUAL, 0)
        };

        int state = initialState;

        for (int i = 0; i < len; i++) {
            Test status = Test.NONE;

            switch (machine[state].test) {
                case EQUAL:
                    if (str.charAt(i) == machine[state].arg1)
                        status = Test.EQUAL;
                    break;

                case NOT_EQUAL:
                    if (str.charAt(i) != machine[state].arg1)
                        status = Test.NOT_EQUAL;
                    break;

                case IN_RANGE:
                    if (str.charAt(i) >= machine[state].arg1 && str.charAt(i) <= machine[state].arg2)
                        status = Test.IN_RANGE;
                    break;

                case OUT_RANGE:
                    if (str.charAt(i) < machine[state].arg1 || str.charAt(i) > machine[state].arg2)
                        status = Test.OUT_RANGE;
                    break;
            }

            if (status == Test.NONE)
                state++;
            else
                state = machine[state].next;
        }
    }

    public static void main(String[] args) {
        String input = "abcdef";
        int len = input.length();
        int initialState = 0;

        machine(input, len, initialState);
    }
}
