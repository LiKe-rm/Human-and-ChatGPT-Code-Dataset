import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class ofApp extends JPanel {

    private static final int width = 800;
    private static final int height = 800;
    private static final int num = 400;
    private static final int levels = 5;
    private List<List<Float>> grid;
    private List<List<Float>> tmp;
    private List<TuringPattern> patterns;
    private int counter;
    private Random random;

    public ofApp() {
        setPreferredSize(new Dimension(width, height));
        random = new Random();
        grid = new ArrayList<>();
        tmp = new ArrayList<>();
        patterns = new ArrayList<>(levels);
        setup();
    }

    public void setup() {
        for (int i = 0; i < num; i++) {
            grid.add(new ArrayList<>());
            tmp.add(new ArrayList<>());
            for (int j = 0; j < num; j++) {
                grid.get(i).add(random.nextFloat() * 2 - 1);
                tmp.get(i).add(0.0f);
            }
        }

        patterns.add(new TuringPattern(num, 100, 200, 100, 200, 1, 0.05f));
        patterns.add(new TuringPattern(num, 50, 100, 50, 100, 1, 0.04f));
        patterns.add(new TuringPattern(num, 10, 20, 10, 20, 1, 0.03f));
        patterns.add(new TuringPattern(num, 5, 10, 5, 10, 1, 0.02f));
        patterns.add(new TuringPattern(num, 2, 4, 2, 4, 1, 0.01f));
    }

    public void draw(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(new Color(0, 0, 0));
        g2d.fillRect(0, 0, width, height);

        for (int i = 0; i < 5; i++) {
            step();
        }

        render(g2d);
    }

    public void render(Graphics2D g2d) {
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                int gray = (int) (120 + 120 * grid.get(i).get(j));
                g2d.setColor(new Color(gray, gray, gray));
                g2d.fillRect(i, j, 1, 1);
            }
        }
    }

    public void step() {
        for (int i = 0; i < levels; i++) {
            patterns.get(i).step(grid, tmp);
        }
        updateGrid();
    }

    public void updateGrid() {
        float smallest = 10;
        float largest = -10;
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                float bestVariation = patterns.get(0).getVariations(i, j);
                int bestLevel = 0;
                for (int k = 1; k < levels; k++) {
                    if (patterns.get(k).getVariations(i, j) < bestVariation) {
                        bestLevel = k;
                        bestVariation = patterns.get(k).getVariations(i, j);
                    }
                }
                if (patterns.get(bestLevel).getActivator(i, j) > patterns.get(bestLevel).getInhibitor(i, j)) {
                    grid.get(i).set(j, grid.get(i).get(j) + patterns.get(bestLevel).getStepSize());
                } else {
                    grid.get(i).set(j, grid.get(i).get(j) - patterns.get(bestLevel).getStepSize());
                }
                largest = Math.max(largest, grid.get(i).get(j));
                smallest = Math.min(smallest, grid.get(i).get(j));
            }
        }
        float range = 0.5f * (largest - smallest);
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                grid.get(i).set(j, (grid.get(i).get(j) - smallest) / range - 1);
            }
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        draw(g);
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Turing Patterns");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new ofApp());
        frame.pack();
        frame.setVisible(true);
    }
}