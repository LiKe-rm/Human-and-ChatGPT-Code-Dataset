import processing.core.PApplet;
import processing.core.PImage;
import processing.core.PVector;

class Photo {
    static int photoWidth = 816 / 2;
    static int photoHeight = 612 / 2;
    static float aspectRatio = (float) photoWidth / photoHeight;
    static float rotationDamping = 0.9f;
    static float maxSpeed = 5;
    static float sizeDamping = 0.9f;

    private PImage img;
    private PVector nw, ne, sw, se;
    private PVector position = new PVector();
    private PVector baseColor = new PVector();
    private float size;
    private float rotation;
    private float brightness;

    static float angleLerp(float from, float to, float t) {
        PVector fromVec = new PVector(1, 0);
        PVector toVec = new PVector(1, 0);
        fromVec.rotate(from);
        toVec.rotate(to);
        fromVec.lerp(toVec, t);
        return PApplet.atan2(fromVec.y, fromVec.x);
    }

    void setup(ControlSurface surface, float x, float y) {
        img = PhotoManager.randomPhoto();
        nw = surface.get(PApplet.floor(x), PApplet.floor(y));
        ne = surface.get(PApplet.ceil(x), PApplet.floor(y));
        sw = surface.get(PApplet.floor(x), PApplet.ceil(y));
        se = surface.get(PApplet.ceil(x), PApplet.ceil(y));
        baseColor.set(PApplet.random(0, 1), PApplet.random(0, 1), PApplet.random(0, 1));
    }

    void update() {
        float curSize = nw.dist(se) + ne.dist(sw);
        curSize /= 4;
        size = PApplet.lerp(curSize, size, sizeDamping);

        PVector curPosition = PVector.add(PVector.add(nw, ne), PVector.add(sw, se));
        curPosition.div(4);

        if (position.mag() == 0) {
            position = curPosition; // start things off on the right foot
        } else {
            PVector diff = PVector.sub(curPosition, position);
            if (diff.mag() > maxSpeed) {
                diff.normalize();
                diff.mult(maxSpeed);
            }
            position.add(diff);
        }

        PVector o1 = PVector.sub(sw, se);
        PVector o2 = PVector.sub(nw, ne);
        float curRotation = PApplet.atan2(o1.y, o1.x) + PApplet.atan2(o2.y, o2.x);
        rotation = angleLerp(curRotation, rotation, rotationDamping);

        brightness = PApplet.map(size, 200, 400, 1, 0, true);
    }

    void draw(PApplet p) {
        p.pushMatrix();

        p.translate(position.x, position.y);
        p.rotate(rotation);

        p.scale(size * aspectRatio, size);

        p.imageMode(p.CENTER);
        p.tint(brightness * baseColor.x * 255, brightness * baseColor.y * 255, brightness * baseColor.z * 255);
        p.image(img, 0, 0, photoWidth, photoHeight);

        p.popMatrix();
    }

    boolean inside(PApplet p, float x, float y, float width, float height) {
        float halfWidth = size * aspectRatio / 2;
        float halfHeight = size / 2;
        float halfDiagonal = PApplet.sqrt(halfWidth * halfWidth + halfHeight * halfHeight);
        return position.x + halfDiagonal > x && position.y + halfDiagonal > y && position.x - halfDiagonal < x + width
                && position.y - halfDiagonal < y + height;
    }
}

class ControlSurface {
    // Assuming you have a ControlSurface class with appropriate methods, e.g.
    // get(int x, int y).
}

class PhotoManager {
    static PImage randomPhoto() {
        // Assuming you have a PhotoManager class with appropriate methods, e.g.
        // randomPhoto().
    }
}

public class MainApp extends PApplet {
    Photo photo = new Photo();
    ControlSurface surface = new ControlSurface();

    public static void main(String[] args) {
        PApplet.main("MainApp");
    }

    public void settings() {
        size(800, 600);
    }

    public void setup() {
        photo.setup(surface, width / 2, height / 2);
    }

    public void draw() {
        background(0);
        photo.update();
        photo.draw(this);
    }
}