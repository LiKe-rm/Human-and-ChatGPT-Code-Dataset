import processing.opengl.*;

public class Fbo {
  PGraphics fbo;
  int width, height;
  float fov;

  public Fbo(int width, int height) {
    this.width = width;
    this.height = height;
    this.fov = 60;
    this.fbo = createGraphics(width, height, P3D);
  }

  public void begin() {
    fbo.beginDraw();
    setCamera();
  }

  public void end() {
    fbo.endDraw();
  }

  public void setBackground(float r, float g, float b, float a) {
    fbo.beginDraw();
    fbo.background(r, g, b, a);
    fbo.endDraw();
  }

  public void clearAlpha() {
    fbo.beginDraw();
    fbo.colorMode(RGB, 1);
    fbo.clear(0, 0, 0, 1);
    fbo.endDraw();
  }

  public void draw(float x, float y) {
    draw(x, y, width, height);
  }

  public void draw(float x, float y, float w, float h) {
    image(fbo, x, y, w, h);
  }

  public void setCamera() {
    float eyeX = (float) width / 2;
    float eyeY = (float) height / 2;
    float halfFov = PConstants.PI * fov / 360;
    float theTan = PApplet.tan(halfFov);
    float dist = eyeY / theTan;
    float nearDist = dist / 10;
    float farDist = dist * 10;
    float aspect = (float) width / height;

    fbo.camera(eyeX, eyeY, dist, eyeX, eyeY, 0, 0, 1, 0);
    fbo.perspective(fov, aspect, nearDist, farDist);
  }

  public int getWidth() {
    return width;
  }

  public int getHeight() {
    return height;
  }

  Fbo fbo;

    void setup() {
    size(800, 600, P3D);
    fbo = new Fbo(800, 600);
    }

    void draw() {
    background(0);
    
    fbo.begin();
    fbo.setBackground(50, 50, 150, 255);
    fbo.end();
    
    fbo.draw(0, 0);
    }

}
