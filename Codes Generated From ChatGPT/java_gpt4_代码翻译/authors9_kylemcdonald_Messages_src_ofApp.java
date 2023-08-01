import processing.core.*;
import processing.data.*;
import processing.event.*;
import processing.opengl.*;
import ddf.minim.*;

public class MainApp extends PApplet {
    public static void main(String[] args) {
        PApplet.main("MainApp");
    }

    PFont font;
    int side;
    PShader shader;
    String core;
    PGraphics fbo;
    AudioOutput audioOut;
    Minim minim;
    JSONObject config;
    PImage audioPixels;
    int time, curCount;
    boolean updateShader;

    public void settings() {
        size(800, 600, P3D);
    }

    public void setup() {
        config = loadJSONObject("config.json");

        noCursor();
        frameRate(30);
        side = config.getInt("side");

        fbo = createGraphics(side, side, P3D);
        time = 0;
        curCount = 0;
        updateShader = true;

        font = createFont("uni05_53.ttf", 6);

        minim = new Minim(this);
        audioOut = minim.getLineOut(Minim.STEREO, 256, 44100, 1);

        loadShader();
    }

    public void draw() {
        background(0);
        fill(255);

        fbo.begin();
        shader(shader);
        rect(0, 0, side, side);
        fbo.end();

        // Drawing logic

        if (updateShader) {
            loadShader();
            updateShader = false;
        }
    }

    int nextPowerOfTwo(int n) {
        return n < 2 ? 1 : 2 * nextPowerOfTwo(n / 2);
    }

    String buildShader(String bytebeat, int side) {
        return "uniform float time; const int width = " + side + "; void main() { int t = int(gl_FragCoord.y) * width + int(gl_FragCoord.x); int x = " + bytebeat + "; gl_FragColor = vec4(vec3(float(x % 256) / 256.),1.); }";
    }

    void loadShader() {
        core = buildCore(); // Replace this with your OneLiner::build() method
        shader = loadShader(buildShader(core, side));
    }

    String buildCore() {
        // Replace this with your OneLiner::build() method implementation
        return "t";
    }
}
