import processing.core.*;
import processing.data.*;
import processing.event.*;
import processing.opengl.*;

import java.util.ArrayList;

public class MainApp extends PApplet {
    String appName = "Test App";
    PhotoManager photoManager;
    Surface surface;
    Wall wall;
    OscManager oscManager;

    public static void main(String[] args) {
        PApplet.main("MainApp");
    }

    public void settings() {
        size(800, 600);
    }

    public void setup() {
        surface = new Surface(this);
        wall = new Wall(this, surface);
        photoManager = new PhotoManager(this, "~/Desktop/3rdiStream/resized/");
        oscManager = new OscManager(this, surface, wall);

        surface.setup(new PVector(60, 100));
    }

    public void draw() {
        background(0);
        oscManager.update();
        wall.draw();
    }

    public void keyPressed() {
        oscManager.keyPressed(key);
    }

    public void mouseMoved() {
        oscManager.mouseMoved(mouseX, mouseY);
    }
}

// Include other classes here, such as PhotoManager, Surface, Wall, and OscManager.
// These classes should be implemented according to the provided C++ code snippet,
// with methods and fields that match the original functionality.

