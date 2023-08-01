import processing.core.*;
import java.util.*;

public class ofApp extends PApplet {
    boolean drawTiles = false;

    int n, wh, side, levels;
    float[] grid;
    float[] diffusionLeft, diffusionRight, variation;
    float[] bestVariation;
    byte[] bestLevel;
    boolean[] direction;

    ArrayList<Float> stepSizes;
    ArrayList<Integer> radii;
    PImage buffer;

    public static void main(String[] args) {
        PApplet.main("ofApp");
    }

    public void settings() {
        size(800, 600, P3D);
    }

    public void setup() {
        side = 64;
        float base = 2;
        levels = (int) (Math.log(side) / Math.log(base));
        float stepScale = .09f;
        float stepOffset = .008f;

        wh = side * side;
        n = side * side * side;
        radii = new ArrayList<>(levels);
        stepSizes = new ArrayList<>(levels);
        grid = new float[n];
        diffusionLeft = new float[n];
        diffusionRight = new float[n];
        variation = new float[n];
        bestVariation = new float[n];
        bestLevel = new byte[n];
        direction = new boolean[n];
        buffer = createImage(side, side, ARGB);

        for (int i = 0; i < levels; i++) {
            int radius = (int) Math.pow(base, i);
            radii.add(radius);
            float diameterRatio = (float) ((2 * radius) + 1) / side;
            println(i + ":" + (int) (100 * diameterRatio) + "%");
            stepSizes.add((float) (Math.log(radius) * stepScale + stepOffset));
        }

        for (int i = 0; i < n; i++) {
            grid[i] = random(-1, 1);
        }

        buffer.loadPixels();
        for (int i = 0; i < wh; i++) {
            buffer.pixels[i] = color(255, 255, 255, 255);
        }
        buffer.updatePixels();
        blendMode(ADD);
    }

    void blur(float[] from, float[] to, float[] buffer, int w, int h, int d, int radius) {
        int i = 0;
        boolean hx, hy, hz;
        hz = false;
        for (int z = 0; z < d; z++) {
            hy = false;
            for (int y = 0; y < h; y++) {
                hx = false;
                for (int x = 0; x < w; x++) {
                    buffer[i] = from[i];

                    if (hx) {
                        buffer[i] += buffer[i - 1];
                        if (hy) {
                            buffer[i] -= buffer[i - 1 - w];
                            if (hz) {
                                buffer[i] += buffer[i - 1 - w - wh];
                            }
                        }
                        if (hz) {
                            buffer[i] -= buffer[i - 1 - wh];
                        }
                    }
                    if (hy) {
                        buffer[i] += buffer[i - w];
                        if (hz) {
                            buffer[i] -= buffer[i - w - wh];
                        }
                    }
                    if (hz) {
                        buffer[i] += buffer[i - wh];
                    }

                    i++;
                    hx = true;
                }
                hy = true;
            }
            hz = true;
        }

        i = 0;
        for (intz = 0; z < d; z++) {
            int minz = Math.max(0, z - radius);
            int maxz = Math.min(z + radius, d - 1);
            int minzi = minz * wh;
            int maxzi = maxz * wh;
            for (int y = 0; y < h; y++) {
                int miny = Math.max(0, y - radius);
                int maxy = Math.min(y + radius, h - 1);
                int minyi = miny * w;
                int maxyi = maxy * w;
                for (int x = 0; x < w; x++) {
                    int minx = Math.max(0, x - radius);
                    int maxx = Math.min(x + radius, w - 1);
                    int volume = (maxx - minx) * (maxy - miny) * (maxz - minz);
                    int nwf = minzi + minyi + minx;
                    int nef = minzi + minyi + maxx;
                    int swf = minzi + maxyi + minx;
                    int sef = minzi + maxyi + maxx;
                    int nwb = maxzi + minyi + minx;
                    int neb = maxzi + minyi + maxx;
                    int swb = maxzi + maxyi + minx;
                    int seb = maxzi + maxyi + maxx;

                    to[i] = (+buffer[nwb] - buffer[neb] - buffer[swb] + buffer[seb] - buffer[nwf] + buffer[nef]
                            + buffer[swf] - buffer[sef]) / volume;
                    i++;
                }
            }
        }
    }

    public void update() {
        float[] activator = grid;
        float[] inhibitor = diffusionRight;

        for (int level = 0; level < levels - 1; level++) {
            int radius = radii.get(level);
            blur(activator, inhibitor, variation, side, side, side, radius);

            for (int i = 0; i < n; i++) {
                variation[i] = Math.abs(activator[i] - inhibitor[i]);
            }

            if (level == 0) {
                for (int i = 0; i < n; i++) {
                    bestVariation[i] = variation[i];
                    bestLevel[i] = (byte) level;
                    direction[i] = activator[i] > inhibitor[i];
                }
                activator = diffusionRight;
                inhibitor = diffusionLeft;
            } else {
                for (int i = 0; i < n; i++) {
                    if (variation[i] < bestVariation[i]) {
                        bestVariation[i] = variation[i];
                        bestLevel[i] = (byte) level;
                        direction[i] = activator[i] > inhibitor[i];
                    }
                }
                float[] temp = activator;
                activator = inhibitor;
                inhibitor = temp;
            }
        }

        float smallest = 10;
        float largest = -10;
        for (int i = 0; i < n; i++) {
            float curStep = stepSizes.get(bestLevel[i]);
            if (direction[i]) {
                grid[i] += curStep;
            } else {
                grid[i] -= curStep;
            }
            smallest = Math.min(smallest, grid[i]);
            largest = Math.max(largest, grid[i]);
        }

        float range = (largest - smallest) / 2;
        for (int i = 0; i < n; i++) {
            grid[i] = ((grid[i] - smallest) / range) - 1;
        }
    }

    public void drawBuffer(float[] grid, int offset) {
        int[] pixels = buffer.getRGB(0, 0, side, side, null, 0, side);
        for (int i = 0; i < wh; i++) {
            float cur = grid[i + offset * wh];
            int alpha = (int) ((cur + 1) * 127.5);
            pixels[i] = (255 << 24) | (alpha << 16) | (alpha << 8) | alpha;
        }
        buffer.setRGB(0, 0, side, side, pixels, 0, side);
        buffer.flush();
    }

    public void draw() {
        ofBackground(0);

        cam.begin();
        ofScale(5, 5, 5);
        ofTranslate(-side / 2, -side / 2, -side / 2);
        for (int z = 0; z < side; z++) {
            ofPushMatrix();
            ofTranslate(0, 0, z);
            drawBuffer(grid, z);
            ofPopMatrix();
        }
        cam.end();

        if (drawTiles) {
            int i = 0;
            for (int y = 0; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    ofPushMatrix();
                    ofTranslate(x * side, y * side);
                    drawBuffer(grid, i++);
                    ofPopMatrix();
                }
            }
        }
    }

    public void mousePressed(int x, int y, int button) {
        setup();
    }

    public void keyPressed(int key) {
        if (key == KeyEvent.VK_SPACE) {
            try {
                ImageIO.write(buffer, "png", new File(ofGetFrameNum() + ".png"));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        if (key == KeyEvent.VK_TAB) {
            setup();
        }
    }

    public static void main(String[] args) {
        ofApp app = new ofApp();
        app.setup();
        // Add your custom drawing and interaction code here
    }
}
