import oscP5.OscMessage;
import oscP5.OscP5;
import processing.core.PApplet;
import processing.core.PVector;
import processing.data.XML;

public class TestApp extends PApplet {
    private OscP5 oscSender;
    private PVector curPoint = new PVector();
    private float t = 0;
    private String address = "255.255.255.255";
    private int port = 8888;

    public static void main(String[] args) {
        PApplet.main("TestApp");
    }

    public void settings() {
        size(640, 480);
    }

    public void setup() {
        frameRate(60);
        setupOsc();
    }

    public void setupOsc() {
        XML settings = loadXML("osc.xml");
        if (settings == null) {
            println("testApp::setupOsc(): couldn't load osc.xml");
        } else {
            address = settings.getString("address", "255.255.255.255");
            port = settings.getInt("port", 8888);
        }

        println("Broadcasting to " + address + ":" + port);
        oscSender = new OscP5(this, address, port);
    }

    public void update() {
        t += (1.0 / frameRate) * noise(millis() * 0.001f) * 0.1f;
        curPoint.set(noise(t), noise(t + 100));
    }

    public void draw() {
        update();

        background(0);
        fill(255);
        noStroke();

        PVector screenPoint1 = new PVector(curPoint.x * width, curPoint.y * height);
        PVector screenPoint2 = new PVector(curPoint.x * width, 0.9f * height);
        
        ellipse(screenPoint1.x, screenPoint1.y, 32, 32);
        ellipse(screenPoint2.x, screenPoint2.y, 32, 32);

        OscMessage message = new OscMessage("mouse");
        message.add(curPoint.x);
        message.add(map(curPoint.y, 0, 1, 0.8f, 0.9f));
        message.add(curPoint.x);
        message.add(curPoint.y);
        oscSender.send(message);
    }
}
