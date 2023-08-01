import org.openkinect.processing.*;
import processing.core.PImage;
import processing.core.PVector;
import processing.data.XML;
import processing.video.Capture;
import processing.video.Movie;
import gab.opencv.*;
import org.opencv.core.Rect;
import oscP5.*;
import netP5.*;

public class TestApp extends PApplet {

    Kinect kinect;
    int nearThreshold, farThreshold, blobSize;
    boolean bThreshWithOpenCV, drawPC;
    float pointCloudRotationY;
    int angle;

    OpenCV opencv;
    PImage colorImg, grayImage, grayThresh, grayThreshFar;
    ContourFinder contourFinder;
    OscP5 oscSender;
    XML imageSettings;
    PVector curPoint;

    public static void main(String[] args) {
        PApplet.main("TestApp");
    }

    public void settings() {
        size(1280, 960);
    }

    public void setup() {
        // Kinect initialization
        kinect = new Kinect(this);
        kinect.initDepth();
        kinect.start();

        // Setting up images
        colorImg = createImage(kinect.width, kinect.height, RGB);
        grayImage = createImage(kinect.width, kinect.height, ALPHA);
        grayThresh = createImage(kinect.width, kinect.height, ALPHA);
        grayThreshFar = createImage(kinect.width, kinect.height, ALPHA);

        bThreshWithOpenCV = true;

        // Setting up OpenCV
        opencv = new OpenCV(this, kinect.width, kinect.height);
        contourFinder = new ContourFinder();

        frameRate(30);

        angle = -90;
        kinect.setTilt(angle);

        pointCloudRotationY = 180;

        drawPC = false;
        setupOsc();

        // Loading settings
        println("Loading mySettings.xml");

        imageSettings = loadXML("settings.xml");
        if (imageSettings != null) {
            println("settings.xml loaded!");
            nearThreshold = imageSettings.getInt("options:nearThreshold");
            farThreshold = imageSettings.getInt("options:farThreshold");
            blobSize = imageSettings.getInt("options:blobSize");
        } else {
            println("Unable to load mySettings.xml, check data/ folder");
            nearThreshold = 230;
            farThreshold = 70;
            blobSize = 400;
        }

        kinect.setDepthClipping(100, 500);
    }

    public void setupOsc() {
        XML settings = loadXML("osc.xml");
        if (settings == null) {
            println("Error: testApp::setupOsc(): couldn't load osc.xml");
            exit();
        }

        String address = settings.getString("address");
        int port = settings.getInt("port");

        println("Broadcasting to " + address + ":" + port);
        oscSender = new OscP5(this, new NetAddress(address, port));
    }

    public void update() {
        background(100, 100, 100);

        kinect.update();
        if (kinect.isDepthFrame()) {

            grayImage.copy(kinect.getDepthImage(), 0, 0, kinect.width, kinect.height, 0, 0, kinect.width,
                    kinect.height);

            if (bThreshWithOpenCV) {
                grayThreshFar.copy(grayImage, 0, 0, kinect.width, kinect.height, 0, 0, kinect.width, kinect.height);
                grayThresh.copy(grayImage, 0, 0, kinect.width, kinect.height);
                grayThresh.filter(THRESHOLD, nearThreshold);
                grayThreshFar.filter(THRESHOLD, 255 - farThreshold);
                grayImage.blend(grayThresh, 0, 0, kinect.width, kinect.height, 0, 0, kinect.width, kinect.height,
                        MULTIPLY);
            } else {
                byte[] pix = grayImage.pixels;
                int numPixels = grayImage.width * grayImage.height;

                for (int i = 0; i < numPixels; i++) {
                    if (pix[i] < nearThreshold && pix[i] > farThreshold) {
                        pix[i] = (byte) 255;
                    } else {
                        pix[i] = 0;
                    }
                }
                grayImage.updatePixels();
            }

            contourFinder.findContours(grayImage, blobSize, (kinect.width * kinect.height) / 2, 20, false);

            OscMessage message = new OscMessage("mouse");

            for (ContourBlob blob : contourFinder.blobs) {
                curPoint = new PVector(blob.centroid.x, blob.centroid.y);
                message.add(ofMap(curPoint.x, 0, 640, 0, 1, true));
                message.add(ofMap(curPoint.y, 0, 480, 0, 1, true));
            }
            oscSender.send(message);
        }
    }

    public void draw() {
        update();
        image(kinect.getDepthImage(), 0, 0, 640 * 2, 480 * 2);
        image(kinect.getVideoImage(), 420, 10, 400, 300);

        image(grayImage, 10, 320, 400, 300);
        contourFinder.draw(10, 320, 400, 300);

        fill(255);
        String report = "set near threshold " + nearThreshold + " (press: + -)\n" + "set far threshold " + farThreshold
                + " (press: < >)\n" + "set blob size " + blobSize + " (press: [ ]) num blobs found "
                + contourFinder.blobs.size() + "\n" + "press 's' to save these settings";
        text(report, 20, 666);
    }

    public void keyPressed() {
        switch (key) {
            case ' ':
                bThreshWithOpenCV = !bThreshWithOpenCV;
                break;
            case 'p':
                drawPC = !drawPC;
                break;
            case '.':
            case '>':
                farThreshold++;
                if (farThreshold > 255)
                    farThreshold = 255;
                imageSettings.setInt("options:farThreshold", farThreshold);
                break;
            case ',':
            case '<':
                farThreshold--;
                if (farThreshold < 0)
                    farThreshold = 0;
                imageSettings.setInt("options:farThreshold", farThreshold);
                break;
            case '=':
            case '+':
                nearThreshold++;
                if (nearThreshold > 255)
                    nearThreshold = 255;
                imageSettings.setInt("options:nearThreshold", nearThreshold);
                break;
            case '-':
                nearThreshold--;
                if (nearThreshold < 0)
                    nearThreshold = 0;
                imageSettings.setInt("options:nearThreshold", nearThreshold);
                break;
            case '[':
                blobSize -= 10;
                if (blobSize < 0)
                    blobSize = 0;
                imageSettings.setInt("options:blobSize", blobSize);
                break;
            case ']':
                blobSize += 10;
                if (blobSize > 307200)
                    blobSize = 307200;
                imageSettings.setInt("options:blobSize", blobSize);
                break;
            case 's':
                imageSettings.save("settings.xml");
                println("saved xml settings");
                break;
            case 'w':
                kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
                break;
            case 'o':
                kinect.setCameraTiltAngle(angle); // go back to prev tilt
                kinect.open();
                break;
            case 'c':
                kinect.setCameraTiltAngle(0); // zero the tilt
                kinect.close();
                break;
            case CODED:
                if (keyCode == UP) {
                    angle++;
                    if (angle > 30)
                        angle = 30;
                    kinect.setCameraTiltAngle(angle);
                } else if (keyCode == DOWN) {
                    angle--;
                    if (angle < -30)
                        angle = -30;
                    kinect.setCameraTiltAngle(angle);
                }
                break;
        }
    }

    public void mouseMoved() {
        pointCloudRotationY = mouseX;
    }

    public void mousePressed() {
    }

    public void mouseReleased() {
    }

    public void mouseDragged() {
    }

    public void exit() {
        kinect.setCameraTiltAngle(0);
        kinect.close();
    }
}

class ContourBlob {
    PVector centroid;
    ArrayList<PVector> points;

    ContourBlob() {
        centroid = new PVector();
        points = new ArrayList<PVector>();
    }

    void addPoint(PVector point) {
        points.add(point);
        updateCentroid();
    }

    void updateCentroid() {
        PVector sum = new PVector();
        for (PVector point : points) {
            sum.add(point);
        }
        centroid.set(sum.div(points.size()));
    }
}

class ContourFinder {
    ArrayList<ContourBlob> blobs;
    int minBlobSize, maxBlobSize;

    ContourFinder() {
        blobs = new ArrayList<ContourBlob>();
    }

    void findContours(PImage image, int minSize, int maxSize) {
        blobs.clear();
        minBlobSize = minSize;
        maxBlobSize = maxSize;

        OpenCV opencv = new OpenCV(image);
        ArrayList<Contour> contours = opencv.findContours();

        for (Contour contour : contours) {
            ContourBlob blob = new ContourBlob();
            for (PVector point : contour.getPoints()) {
                blob.addPoint(point);
            }
            int blobSize = blob.points.size();
            if (blobSize >= minBlobSize && blobSize <= maxBlobSize) {
                blobs.add(blob);
            }
        }
    }

    void draw(float x, float y, float width, float height) {
        pushMatrix();
        translate(x, y);
        scale(width / (float) KinectApp.WIDTH, height / (float) KinectApp.HEIGHT);
        stroke(255, 0, 0);
        noFill();
        for (ContourBlob blob : blobs) {
            beginShape();
            for (PVector point : blob.points) {
                vertex(point.x, point.y);
            }
            endShape(CLOSE);
        }
        popMatrix();
    }
}
