import java.util.Random;

public class CRayTracer {
    private int numspheres = 5;
    private Scene scene = new Scene();
    private Sphere[] sphere;
    private Box[] box = new Box[6];
    private Material[] m = new Material[7];
    private Light light = new Light();
    private byte[] screen;
    private Random random = new Random();

    public CRayTracer() {
        numspheres = 5;
    }

    public void setRes(int width, int height) {
        scene.setResolution(width, height);
        scene.resetObjectsOnly();
    }

    public void updateScene(Point3 viewposition, byte[] screen, char unique) {
        int i;
        float angle = System.currentTimeMillis() * 0.0001f;

        for (i = 0; i < numspheres; i++) {
            if (sphere[i].centre.x > 75 || sphere[i].centre.x < -75) {
                sphere[i].direction.set(-sphere[i].direction.x, sphere[i].direction.y, 0);
            }

            if (sphere[i].centre.y > 75 || sphere[i].centre.y < -75) {
                sphere[i].direction.set(sphere[i].direction.x, -sphere[i].direction.y, 0);
            }

            if (sphere[i].direction.x == 0 && sphere[i].direction.y == 0) {
                sphere[i].direction = new Vector(random.nextInt(4) - 2, random.nextInt(4) - 2, 0);
            }

            sphere[i].centre.add(sphere[i].direction);
        }

        float radius = (float) (Math.cos(angle * 3.0f) * 10.0f + 75.0f);
        float height = (float) (Math.cos(angle * 5.0f) * 25.0f + 35.0f);
        scene.camera.p.set((float) Math.cos(angle) * radius, height, (float) Math.sin(angle) * radius);
        scene.camera.lookAt(new Vector(0.0f), 0.0f);

        light.p.set(0, -20, 60);

        scene.beginFrame();
        scene.useHardware = 0;

        if (screen == null) {
            scene.renderGL(unique);
        } else {
            scene.useHardware = unique;
            scene.render(viewposition, screen);
        }
    }

    public int initScene() {
        // Set initial properties for the scene, materials, spheres, boxes, and lights
        // ...
        // ...

        screen = new byte[1000 * 1000 * 3];

        return 0;
    }

    public void destroyScene() {
        screen = null;
        sphere = null;
    }
}
