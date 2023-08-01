import org.openkinect.processing.KinectPV2;
import processing.core.PApplet;
import processing.core.PVector;

import java.util.ArrayList;
import java.util.List;

public class TestApp extends PApplet {

    // Kinect frame width
    public static final int KW = 640;
    // Kinect frame height
    public static final int KH = 480;
    // For the average fps calculation
    public static final int FPS_MEAN = 30;

    // -------------- Estimator parameters
    // Maximum distance from the sensor - used to segment the person
    int maxZ = 2000;
    // Kinect motor tilt angle
    int kTilt = 0;
    // Stuff to calculate average fps
    float kFPS = 0;
    float avgkFPS = 0;
    int frameCount = 0;
    int lastMillis = 0;
    // Draw / hide point cloud
    boolean drawCloud = true;
    
    KinectPV2 kinect;
    
    public static void main(String[] args) {
        PApplet.main("TestApp", args);
    }

    public void settings() {
        size(KW, KH, P3D);
    }

    public void setup() {
        kinect = new KinectPV2(this);
        kinect.initDepth();
        kinect.initDevice();
    }

    public void draw() {
        // Update Kinect data
        kinect.update();
        
        // Clear the background
        background(0);

        // Calculate average FPS
        calcAvgFPS();

        // Draw point cloud
        if (drawCloud) {
            drawPointCloud();
        }

        // Draw report
        drawReport();
    }

    public void keyPressed() {
        switch (key) {
            case CODED:
                if (keyCode == UP) {
                    kTilt++;
                    if (kTilt > 30) kTilt = 30;
                } else if (keyCode == DOWN) {
                    kTilt--;
                    if (kTilt < -30) kTilt = -30;
                }
                break;
            case 'm':
                drawCloud = !drawCloud;
                break;
        }
    }

    private void calcAvgFPS() {
        int currMillis = millis();
        avgkFPS += (1000.0f / (currMillis - lastMillis)) / FPS_MEAN;
        lastMillis = currMillis;
        frameCount++;
        if (frameCount >= FPS_MEAN) {
            kFPS = avgkFPS;
            avgkFPS = 0;
            frameCount = 0;
        }
    }

    private void drawPointCloud() {
        pushMatrix();
        scale(1, -1, -1);
        translate(0, 0, -1000);

        int step = 2;
        for (int y = 0; y < KH; y += step) {
            for (int x = 0; x < KW; x += step) {
                float distance = kinect.getDepthAt(x, y);
                if (distance > 0 && distance < maxZ) {
                    PVector point = kinect.depthMapRealWorld()[x + y * KW];
                    stroke(255);
                    strokeWeight(3);
                    point(point.x, point.y, point.z);
                }
            }
        }
        popMatrix();
    }

    private void drawReport() {
        fill(255);
        textAlign(LEFT);
        text("framecount: " + frameCount + "   FPS: " + nf(kFPS, 0, 2), 10, 20);
    }
}
