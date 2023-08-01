import processing.core.*;
import processing.opengl.*;
import peasy.*;

PeasyCam cam;
PShape faceShiftMesh;
PShape spikes;
PVector lightPosition = new PVector(500, 500, 500);
ArrayList<PVector> normals = new ArrayList<PVector>();
ArrayList<PVector> vertices = new ArrayList<PVector>();

public void setup() {
  size(800, 600, P3D);
  cam = new PeasyCam(this, 500);
  faceShiftSetup();
  lightPosition();
}

public void draw() {
  background(255);
  cam.begin();
  faceShiftRandomUpdate();
  drawFaceShift();
  cam.end();
}

public void faceShiftSetup() {
  faceShiftMesh = createShape();
  spikes = createShape();

  // Import the mesh (vertices, normals) here using your preferred method
  // Add vertices and normals to the ArrayLists
}

public void faceShiftRandomUpdate() {
  // Update the mesh using your preferred method
}

public void drawFaceShift() {
  lights();
  pushMatrix();
  rotateX(radians(180));
  shape(faceShiftMesh);

  pushStyle();
  stroke(0);
  shape(spikes);
  popStyle();

  popMatrix();
}

public void lightPosition() {
  pointLight(255, 255, 255, lightPosition.x, lightPosition.y, lightPosition.z);
}

public void createSpikes() {
  spikes.beginShape(LINES);
  for (int i = 0; i < vertices.size() - 3; i += 3) {
    PVector v1 = vertices.get(i);
    PVector v2 = vertices.get(i + 1);
    PVector v3 = vertices.get(i + 2);
    PVector normal = normals.get(i);
    float len = (v1.dist(v2) + v2.dist(v3) + v3.dist(v1)) / 3;
    PVector target = PVector.add(PVector.add(v1, v2), v3).div(3).add(PVector.mult(normal, len));

    spikes.vertex(target.x, target.y, target.z);
    spikes.vertex(v1.x, v1.y, v1.z);
    spikes.vertex(target.x, target.y, target.z);
    spikes.vertex(v2.x, v2.y, v2.z);
    spikes.vertex(target.x, target.y, target.z);
    spikes.vertex(v3.x, v3.y, v3.z);
  }
  spikes.endShape();
}
