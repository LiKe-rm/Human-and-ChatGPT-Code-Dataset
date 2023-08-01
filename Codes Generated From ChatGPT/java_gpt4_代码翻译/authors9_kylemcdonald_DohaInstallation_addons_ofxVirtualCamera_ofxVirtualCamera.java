import org.openkinect.processing.Kinect;
import processing.core.PApplet;
import processing.core.PConstants;
import processing.core.PGraphics;
import processing.core.PImage;
import processing.core.PVector;

import java.util.ArrayList;
import java.util.List;

public class VirtualCamera {

    private static final float FOV_WIDTH = 1.0144686707507438f;
    private static final float FOV_HEIGHT = 0.78980943449644714f;
    private static final float XtoZ = (float) Math.tan(FOV_WIDTH / 2) * 2;
    private static final float YtoZ = (float) Math.tan(FOV_HEIGHT / 2) * 2;
    private static final int CAM_WIDTH = 640;
    private static final int CAM_HEIGHT = 480;

    private final PApplet parent;
    private final Kinect kinect;
    private final PGraphics fbo;
    private final PImage fboGrayImage;

    private List<PVector> surface;
    private List<Integer> indices;
    private boolean newFrame;
    private float maxLen;
    private int stepSize;
    private float nearClipping;
    private float farClipping;
    private float orthoScale;
    private PVector position;
    private PVector rotation;

    public VirtualCamera(PApplet parent) {
        this.parent = parent;
        this.kinect = new Kinect(parent);
        this.fbo = parent.createGraphics(CAM_WIDTH, CAM_HEIGHT, PConstants.P3D);
        this.fboGrayImage = new PImage(CAM_WIDTH, CAM_HEIGHT);

        this.surface = new ArrayList<>(CAM_WIDTH * CAM_HEIGHT);
        this.indices = new ArrayList<>(CAM_WIDTH * CAM_HEIGHT * 3);
        this.newFrame = false;
        this.maxLen = 1;
        this.stepSize = 1;
        this.nearClipping = -1024;
        this.farClipping = 1024;
        this.orthoScale = 1;
        this.position = new PVector(0, 0, 0);
        this.rotation = new PVector(0, 0, 0);
    }

    public void setup() {
        surface.clear();
        for (int i = 0; i < CAM_WIDTH * CAM_HEIGHT; i++) {
            surface.add(new PVector());
        }
        indices.clear();

        kinect.initDepth();
        kinect.enableMirror(true);
    }

    private PVector convertProjectiveToRealWorld(float x, float y, float z) {
        return new PVector(-(x / CAM_WIDTH - 0.5f) * z * XtoZ,
                (y / CAM_HEIGHT - 0.5f) * z * YtoZ,
                z);
    }

    public void updateSurface() {
        int[] depth = kinect.getRawDepth();

        for (int y = 0; y < CAM_HEIGHT; y++) {
            for (int x = 0; x < CAM_WIDTH; x++) {
                int i = y * CAM_WIDTH + x;
                int z = depth[i];
                if (z != 0) {
                    surface.set(i, convertProjectiveToRealWorld(x, y, -z));
                }
            }
        }
    }

    public void updateMesh() {
        indices.clear();
        int[] depth = kinect.getRawDepth();

        for (int y = 0; y < CAM_HEIGHT - stepSize; y += stepSize) {
            for (int x = 0; x < CAM_WIDTH - stepSize; x += stepSize){
                int i = y * CAM_WIDTH + x;
                int nwi = i;
                int nei = nwi + stepSize;
                int swi = nwi + (stepSize * CAM_WIDTH);
                int sei = swi + stepSize;

                int nw = depth[nwi];
                int ne = depth[nei];
                int sw = depth[swi];
                int se = depth[sei];

                if (nw != 0 && ne != 0 && sw != 0 &&
                        Math.abs(nw - ne) < maxLen && Math.abs(nw - sw) < maxLen) {
                    indices.add(nwi);
                    indices.add(nei);
                    indices.add(swi);
                }

                if (ne != 0 && se != 0 && sw != 0 &&
                        Math.abs(sw - se) < maxLen && Math.abs(ne - se) < maxLen) {
                    indices.add(nei);
                    indices.add(sei);
                    indices.add(swi);
                }
            }
        }
    }

    public void renderCamera() {
        fbo.beginDraw();
        fbo.background(0, 0, 0, 255);
        fbo.pushMatrix();

        fbo.ortho(-CAM_WIDTH / 2f * orthoScale, CAM_WIDTH / 2f * orthoScale,
                -CAM_HEIGHT / 2f * orthoScale, CAM_HEIGHT / 2f * orthoScale,
                nearClipping, farClipping);

        fbo.translate(position.x, position.y, position.z);
        fbo.rotateX(rotation.x);
        fbo.rotateY(rotation.y);
        fbo.rotateZ(rotation.z);

        fbo.fill(255);
        fbo.noStroke();
        fbo.beginShape(PConstants.TRIANGLES);
        for (int i : indices) {
            PVector v = surface.get(i);
            fbo.vertex(v.x, v.y, v.z);
        }
        fbo.endShape();

        fbo.popMatrix();
        fbo.endDraw();
    }

    public void updatePixels() {
        fbo.loadPixels();
        fboGrayImage.loadPixels();

        for (int i = 0; i < CAM_WIDTH * CAM_HEIGHT; i++) {
            int gray = (fbo.pixels[i] >> 16) & 0xFF;
            fboGrayImage.pixels[i] = parent.color(gray);
        }

        fboGrayImage.updatePixels();
    }

    public void update() {
        kinect.update();
        if (kinect.isFrameNew()) {
            newFrame = true;

            updateSurface();
            updateMesh();
            renderCamera();
            updatePixels();
        }
    }

    public boolean isFrameNew() {
        boolean curNewFrame = newFrame;
        newFrame = false;
        return curNewFrame;
    }

    public int[] getPixels() {
        return fboGrayImage.pixels;
    }

    public void draw(float x, float y) {
        parent.image(fbo, x, y);
    }

    public void setMaxLen(float maxLen) {
        this.maxLen = maxLen;
    }

    public void setStepSize(int stepSize) {
        this.stepSize = stepSize;
    }

    public void setClipping(float nearClipping, float farClipping) {
        this.nearClipping = nearClipping;
        this.farClipping = farClipping;
    }

    public void setOrthoScale(float orthoScale) {
        this.orthoScale = orthoScale;
    }

    public void setPosition(PVector position) {
        this.position = position;
    }

    public void setRotation(PVector rotation) {
        this.rotation = rotation;
    }

    public int getWidth() {
        return CAM_WIDTH;
    }

    public int getHeight() {
        return CAM_HEIGHT;
    }

    public void close() {
        kinect.stop();
    }
}


            
