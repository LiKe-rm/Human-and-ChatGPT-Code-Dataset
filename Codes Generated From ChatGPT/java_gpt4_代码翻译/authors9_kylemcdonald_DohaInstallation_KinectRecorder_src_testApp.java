import org.openkinect.processing.*;
import processing.core.PImage;
import java.util.ArrayList;

public class TestApp extends PApplet {
  Kinect kinect;
  boolean recording;
  int maxFrames, curFrame;
  ArrayList<PImage> images;

  public static void main(String[] args) {
    PApplet.main("TestApp");
  }

  public void settings() {
    size(640, 480);
  }

  public void setup() {
    kinect = new Kinect(this);
    kinect.initDepth();
    kinect.start();

    recording = false;
    maxFrames = 30 * 15;
    curFrame = 0;

    images = new ArrayList<>(maxFrames);
    for (int i = 0; i < maxFrames; i++) {
      PImage img = createImage(640, 480, ALPHA);
      img.loadPixels();
      images.add(img);
    }

    kinect.setDepthClipping(100, 500);
  }

  public void update() {
    kinect.update();
    if (kinect.isDepthFrame() && recording) {
      System.out.println("Recording frame " + curFrame + "/" + maxFrames);

      PImage currentDepth = kinect.getDepthImage();
      images.get(curFrame).copy(currentDepth, 0, 0, currentDepth.width, currentDepth.height, 0, 0, currentDepth.width, currentDepth.height);
      curFrame++;

      if (curFrame >= maxFrames) {
        for (int i = 0; i < maxFrames; i++) {
          images.get(i).save("1000_" + i + ".png");
        }

        recording = false;
      }
    }
  }

  public void draw() {
    update();

    background(100, 100, 100);
    image(kinect.getDepthImage(), 0, 0);
  }

  public void exit() {
    kinect.quit();
    super.exit();
  }

  public void keyPressed() {
    if (key == '\t') {
      recording = !recording;
    }
  }
}
