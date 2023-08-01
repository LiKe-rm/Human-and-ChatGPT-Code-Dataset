package org.doesntexist.lulzkey;

import java.io.PrintStream;

public class Shell {
    private static final int COLUMNS = 80;
    private static final int LINES = 25;

    private PrintStream out;
    private int x;
    private int y;
    private ShellColor color;

    private static Shell instance;

    public static Shell getInstance() {
        if (instance == null) {
            instance = new Shell(System.out);
        }
        return instance;
    }

    private Shell(PrintStream out) {
        this.out = out;
        this.x = 0;
        this.y = 0;
        this.color = new ShellColor();
        clear();
    }

    public void clear() {
        ShellColor tmp = color;
        color = new ShellColor();
        for (int y = 0; y < LINES; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                print(' ');
            }
            print('\n');
        }
        x = 0;
        y = 0;
        color = tmp;
    }

    public void print(char c) {
        if (c == '\n') {
            out.println();
            x = 0;
            y++;
        } else {
            out.print(c);
            x++;
            if (x >= COLUMNS) {
                x = 0;
                y++;
            }
        }
    }

    public void print(String s) {
        for (char c : s.toCharArray()) {
            print(c);
        }
    }

    public void setColor(ShellColor color) {
        this.color = color;
    }

    public ShellColor getColor() {
        return color;
    }

    public static class ShellColor {
        private int foreground;
        private int background;
        private boolean blinking;

        public ShellColor() {
            this(7, 0, false);
        }

        public ShellColor(int foreground, int background, boolean blinking) {
            this.foreground = foreground;
            this.background = background;
            this.blinking = blinking;
        }

        public int getForeground() {
            return foreground;
        }

        public void setForeground(int foreground) {
            this.foreground = foreground;
        }

        public int getBackground() {
            return background;
        }

        public void setBackground(int background) {
            this.background = background;
        }

        public boolean isBlinking() {
            return blinking;
        }

        public void setBlinking(boolean blinking) {
            this.blinking = blinking;
        }
    }
}
