import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Random;

public class ofApp extends JPanel {
    static {
        System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
    }

    private ArrayList<Float> grid;
    private int num, levels;
    private ArrayList<ArrayList<Float>> diffusion;
    private ArrayList<Float> stepSizes;
    private ArrayList<Integer> radii;
    private BufferedImage buffer;

    public ofApp() {
        setup();

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                bufferSaveImage();
                setup();
            }
        });

        new Timer(1000 / 60, e -> {
            update();
            drawBuffer(grid);
            repaint();
        }).start();
    }

    private void setup() {
        num = 4096;
        int n = num * num;

        levels = 9;
        radii = new ArrayList<>(levels);
        stepSizes = new ArrayList<>(levels);
        diffusion = new ArrayList<>(levels);
        for (int i = 0; i < levels; i++) {
            diffusion.add(new ArrayList<>(n));
        }
        float scale = 0.009f;
        float base = 0.008f;
        for (int i = 0; i < levels; i++) {
            int radius = (int) Math.pow(2.5, i);
            radii.add(radius);
            stepSizes.add((float) Math.log(radius) * scale + base);
        }

        grid = new ArrayList<>(n);
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            grid.add(random.nextFloat() * 2 - 1);
        }

        buffer = new BufferedImage(num, num, BufferedImage.TYPE_BYTE_GRAY);
    }

    private void update() {
        updateDiffusion();
        updateGridFromDiffusion();
    }

    private void updateGridFromDiffusion() {
        // Implement the updateGridFromDiffusion logic here
    }

    private void updateDiffusion() {
        Mat srcMat = new Mat(num, num, CvType.CV_32FC1);
        for (int i = 0; i < grid.size(); i++) {
            srcMat.put(i / num, i % num, grid.get(i));
        }

        for (int i = 0; i < diffusion.size(); i++) {
            Mat curMat = new Mat(num, num, CvType.CV_32FC1);
            int radius = radii.get(i);
            Imgproc.blur(i == 0 ? srcMat : new Mat(num, num, CvType.CV_32FC1), curMat,
                    new Size(radius * 2 + 1, radius * 2 + 1));

            for (int j = 0; j < num * num; j++) {
                diffusion.get(i).add((float) curMat.get(j / num, j % num)[0]);
            }
        }
    }

    private void drawBuffer(ArrayList<Float> grid) {
        for (int i = 0; i < grid.size(); i++) {
            buffer.setRGB(i % num, i / num, (int) (128 + 100 * grid.get(i)));
        }
        private void updateGridFromDiffusion() {
            float smallest = 10;
            float largest = -10;
            int n = num * num;
            for (int i = 0; i < n; i++) {
                float bestVariation = 0;
                int bestLevel = 0;
                for (int level = 0; level < diffusion.size() - 1; level++) {
                    float curVariation = Math.abs(diffusion.get(level).get(i) - diffusion.get(level + 1).get(i));
                    if (level == 0 || curVariation < bestVariation) {
                        bestLevel = level;
                        bestVariation = curVariation;
                    }
                }
                float curActivator = diffusion.get(bestLevel).get(i);
                float curInhibitor = diffusion.get(bestLevel + 1).get(i);
                if (curActivator > curInhibitor) {
                    grid.set(i, grid.get(i) + stepSizes.get(bestLevel));
                } else {
                    grid.set(i, grid.get(i) - stepSizes.get(bestLevel));
                }
    
                largest = Math.max(largest, grid.get(i));
                smallest = Math.min(smallest, grid.get(i));
            }
            float range = (largest - smallest) / 2;
            for (int i = 0; i < n; i++) {
                grid.set(i, ((grid.get(i) - smallest) / range) - 1);
            }
        }
    
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            g.drawImage(buffer, 0, 0, null);
            g.drawString(String.valueOf((int) (1000 / 60)), 10, 20);
        }
    
        private void bufferSaveImage() {
            // Implement buffer image saving logic here
        }
    
        public static void main(String[] args) {
            JFrame frame = new JFrame("ofApp");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setContentPane(new ofApp());
            frame.setSize(800, 800);
            frame.setVisible(true);
        }
    }
}
