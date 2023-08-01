import java.util.ArrayList;
import oscP5.OscMessage;
import oscP5.OscP5;
import processing.core.PApplet;
import processing.core.PVector;
import controlP5.ControlP5;

public class TestApp extends PApplet {
    private boolean master = true;
    private OscP5 oscReceiver;
    private OscP5 oscSender;
    private ArrayList<PVector> points = new ArrayList<>();
    private int port = 8888;
    private String address = "255.255.255.255";

    public static void main(String[] args) {
        PApplet.main("TestApp");
    }

    public void settings() {
        size(640, 480);
    }

    public void setup() {
        if (master) {
            println("Connecting to " + address + ":" + port);
            oscSender = new OscP5(this, address, port);
        }
        println("Listening on port " + port);
        oscReceiver = new OscP5(this, port);
    }

    public void draw() {
        background(0);
        stroke(255);
        noFill();

        beginShape(LINES);
        for (PVector point : points) {
            vertex(point.x, point.y);
        }
        endShape();
    }

    public void oscEvent(OscMessage message) {
        String addr = message.addrPattern();
        if (addr.equals("/mouse")) {
            int mx = message.get(0).intValue();
            int my = message.get(1).intValue();
            points.add(new PVector(mx, my));
        } else if (addr.equals("/reset")) {
            points.clear();
        }
    }

    public void keyPressed() {
    }

    public void keyReleased() {
    }

    public void mouseMoved() {
        int x = mouseX * 4;
        int y = mouseY * 4;

        if (master) {
            OscMessage message = new OscMessage("/mouse");
            message.add(x);
            message.add(y);
            oscSender.send(message);
        }
    }

    public void mouseDragged() {
    }

    public void mousePressed() {
        if (master) {
            OscMessage message = new OscMessage("/reset");
            oscSender.send(message);
        }
    }

    public void mouseReleased() {
    }
}
