import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Random;

public class ofApp extends JPanel {
    private ArrayList<Float> grid;
    private int num;
    private ArrayList<TuringPattern> patterns;
    private BufferedImage buffer;

    public ofApp() {
        num = 512;
        int n = num * num;

        float scale = 0.009f;
        float base = 0.008f;
        patterns = new ArrayList<>();
        for (int i = 0; i < 6; i++) {
            int baseSize = (int) Math.pow(2.5, i);
            patterns.add(new TuringPattern(num, baseSize, baseSize * 2, (float) Math.log(baseSize) * scale + base));
        }

        grid = new ArrayList<>(n);
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            grid.add(random.nextFloat() * 2 - 1);
        }

        buffer = new BufferedImage(num, num, BufferedImage.TYPE_BYTE_GRAY);

        setup();
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                setup();
            }
        });

        new Timer(1000 / 60, e -> {
            step();
            updateBuffer();
            repaint();
        }).start();
    }

    private void setup() {
        // Implement your setup logic here
    }

    private void step() {
        for (TuringPattern pattern : patterns) {
            pattern.step(grid);
        }
        updateGrid();
    }

    private void updateGrid() {
        // Implement the updateGrid logic here
    }

    private void updateBuffer() {
        // Implement the updateBuffer logic here
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(buffer, 0, 0, null);
        g.drawString(String.valueOf((int) Toolkit.getDefaultToolkit().getScreenSize().getWidth()), 10, 20);
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Turing Patterns");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new ofApp());
        frame.pack();
        frame.setVisible(true);
    }
}
