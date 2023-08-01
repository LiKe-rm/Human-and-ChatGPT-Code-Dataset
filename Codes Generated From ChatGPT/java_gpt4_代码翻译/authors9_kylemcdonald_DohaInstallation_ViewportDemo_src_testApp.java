import processing.core.*;
import processing.data.*;
import processing.event.*;
import processing.opengl.*;

public class MainApp extends PApplet {
    public static void main(String[] args) {
        PApplet.main("MainApp");
    }

    public void settings() {
        size(800, 600, P3D);
    }

    public void setup() {
        ellipseMode(CENTER);
        noFill();
        stroke(255);
    }

    public void draw() {
        background(0);
        camera();
        viewport(mouseX, mouseY, 128, 128);
        perspective();
        drawSingle();
    }

    public void viewport(int left, int top, int width, int height) {
        top = height() - (height + top);
        getSurface().setNativePixels(left, top, width, height);
    }

    public void drawSingle() {
        ellipse(width / 2, height / 2, 256, 256);
        ellipse(width / 2, height / 2, 128, 128);
        line(width / 2, height / 2, width / 2, 0);
    }

    public void keyPressed() {
    }

    public void keyReleased() {
    }

    public void mouseMoved() {
    }

    public void mouseDragged() {
    }

    public void mousePressed() {
    }

    public void mouseReleased() {
    }

    public void windowResized() {
    }
}
