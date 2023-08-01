public class ShellColor {
    public static final int White = 15;
    public static final int Black = 0;

    private int foreground;
    private int background;
    private boolean blinking;

    public ShellColor(int foreground, int background, boolean blinking) {
        if (foreground < 0) {
            this.foreground = White;
        } else {
            this.foreground = foreground;
        }

        if (background < 0) {
            this.background = Black;
        } else {
            this.background = background;
        }

        this.blinking = blinking;
    }

    public int getForeground() {
        return foreground;
    }

    public void setForeground(int color) {
        this.foreground = color;
    }

    public int getBackground() {
        return background;
    }

    public void setBackground(int color) {
        this.background = color;
    }

    public boolean isBlinking() {
        return blinking;
    }

    public void setBlinking(boolean blinking) {
        this.blinking = blinking;
    }

    public int getValue() {
        return (this.getBackground() * 16) + this.getForeground() | (this.isBlinking() ? 0x80 : 0);
    }
}
