import java.util.ArrayList;

class Vec2 {
    float x, y;

    Vec2(float x, float y) {
        this.x = x;
        this.y = y;
    }

    Vec2 add(Vec2 other) {
        return new Vec2(this.x + other.x, this.y + other.y);
    }

    Vec2 sub(Vec2 other) {
        return new Vec2(this.x - other.x, this.y - other.y);
    }

    Vec2 mult(float scalar) {
        return new Vec2(this.x * scalar, this.y * scalar);
    }

    Vec2 lerp(Vec2 other, float t) {
        return this.mult(1 - t).add(other.mult(t));
    }
}

ArrayList<Vec2> initial, grid;
long startTime;
float padding = 128;

void setup() {
    size(400, 400);
    initGridAndPoints();
}

void draw() {
    background(0);
    strokeWeight(6);
    translate(padding, padding);
    float scale = width - 2 * padding;
    scale(scale, scale);

    float t = map(cos(millis() * 0.001f), -1, 1, 0, 1);
    for (int i = 0; i < initial.size(); i++) {
        Vec2 v = initial.get(i).lerp(grid.get(i), t);
        stroke(255, initial.get(i).x * 255, initial.get(i).y * 255);
        point(v.x, v.y);
    }
}

void keyPressed() {
    if (key == ' ') {
        initGridAndPoints();
    }
}

void initGridAndPoints() {
    int side = 32;
    int n = side * side;

    initial = new ArrayList<>();
    Vec2 cur = new Vec2(0, 0);
    randomSeed(System.nanoTime());
    for (int i = 0; i < n; i++) {
        cur = cur.add(new Vec2(random(-1, 1), random(-1, 1)).mult(0.01f));
        cur.x = cur.x % 1;
        cur.y = cur.y % 1;
        initial.add(cur);
    }

    grid = makeGrid(side, side);
}

ArrayList<Vec2> makeGrid(int width, int height) {
    ArrayList<Vec2> grid = new ArrayList<>();
    float xStep = 1.0f / width;
    float yStep = 1.0f / height;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid.add(new Vec2(x * xStep, y * yStep));
        }
    }

    return grid;
}
