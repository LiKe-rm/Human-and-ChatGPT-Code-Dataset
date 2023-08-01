import java.util.*;

class Tile extends PVector {
  int side;
  PImage img;

  Tile(int x, int y, int side, PImage img) {
    super(x, y);
    this.side = side;
    this.img = img;
  }

  static ArrayList<Tile> buildTiles(PImage img, int side) {
    ArrayList<Tile> tiles = new ArrayList<>();
    int w = img.width;
    int h = img.height;
    int nx = w / side;
    int ny = h / side;

    for (int y = 0; y < h; y += side) {
      for (int x = 0; x < w; x += side) {
        PImage croppedImg = img.get(x, y, side, side);
        tiles.add(new Tile(x, y, side, croppedImg));
      }
    }
    return tiles;
  }
}

public class StereoTiles extends PApplet {
  Capture video;
  PImage leftImage, rightImage;
  ArrayList<Tile> leftTiles, rightTiles;
  int side = 20;

  public static void main(String[] args) {
    PApplet.main("StereoTiles");
  }

  public void settings() {
    size(1280, 720);
  }

  public void setup() {
    video = new Capture(this, 1280, 720);
    video.start();
  }

  public void draw() {
    if (video.available()) {
      video.read();
    }
    image(video, 0, 0);

    leftImage = video.get(0, 0, video.width / 2, video.height);
    rightImage = video.get(video.width / 2, 0, video.width / 2, video.height);

    leftTiles = Tile.buildTiles(leftImage, side);
    rightTiles = Tile.buildTiles(rightImage, side);

    // You will need to implement an assignment algorithm here to match
    // leftTiles with rightTiles based on some similarity metric.
    // The given C++ code uses the ofxAssignment library, which doesn't
    // have a direct equivalent in Java. You can use the Hungarian algorithm
    // or other similar algorithms for this purpose.

    // For now, we will display the images side by side without matching.
    for (int i = 0; i < leftTiles.size(); i++) {
      Tile left = leftTiles.get(i);
      Tile right = rightTiles.get(i);
      image(left.img, left.x, left.y);
      image(right.img, video.width / 2 + right.x, right.y);
    }
  }
}
