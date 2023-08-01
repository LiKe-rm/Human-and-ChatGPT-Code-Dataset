import java.util.ArrayList;
import processing.opengl.PShader;

class Vec3 {
    float x, y, z;

    Vec3(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    Vec3 add(Vec3 other) {
        return new Vec3(this.x + other.x, this.y + other.y, this.z + other.z);
    }

    Vec3 sub(Vec3 other) {
        return new Vec3(this.x - other.x, this.y - other.y, this.z - other.z);
    }

    Vec3 mult(float scalar) {
        return new Vec3(this.x * scalar, this.y * scalar, this.z * scalar);
    }

    Vec3 lerp(Vec3 other, float t) {
        return this.mult(1 - t).add(other.mult(t));
    }
}

ArrayList<Vec3> initial, grid;
long startTime;
PShader pointShader;

void setup() {
    size(400, 400, P3D);
    initGridAndPoints();
    pointShader = loadShader("shaders/pointfrag.glsl", "shaders/pointvert.glsl");
}

void draw() {
    background(0);
    shader(pointShader);
    pointShader.set("pointSize", 6.0);

    float t = map(cos(millis() * 0.001f), -1, 1, 0, 1);
    translate(width / 2, height / 2);
    rotateY(radians(frameCount * 0.5f));
    float scale = width / 2;
    scale(scale, scale, scale);
    translate(-0.5, -0.5, -0.5);

    beginShape(POINTS);
    for (int i = 0; i < initial.size(); i++) {
        Vec3 v = initial.get(i).lerp(grid.get(i), t);
        stroke(initial.get(i).x * 255, initial.get(i).y * 255, initial.get(i).z * 255);
        vertex(v.x, v.y, v.z);
    }
    endShape();
}

void keyPressed() {
    if (key == ' ') {
        initGridAndPoints();
    }
}

void initGridAndPoints() {
    int side = 12;
    int n = side * side * side;

    initial = new ArrayList<>();
    Vec3 cur = new Vec3(0, 0, 0);
    randomSeed(System.nanoTime());
    for (int i = 0; i < n; i++) {
        cur = cur.add(new Vec3(random(-1, 1), random(-1, 1), random(-1, 1)).mult(0.01f));
        cur.x = cur.x % 1;
        cur.y = cur.y % 1;
        cur.z = cur.z % 1;
        initial.add(cur);
    }

    grid = makeGrid(side, side, side);
}

ArrayList<Vec3> makeGrid(int width, int height, int depth) {
    ArrayList<Vec3> grid = new ArrayList<>();
    float xStep = 1.0f / width;
    float yStep = 1.0f / height;
    float zStep = 1.0f / depth;

    for (int z = 0; z < depth; z++) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                float xPos = x * xStep;
                float yPos = y * yStep;
                float zPos = z * zStep;
                grid.add(new Vec3(xPos, yPos, zPos));
            }
        }
    }

    return grid;
}
