import javax.media.j3d.Appearance;
import javax.media.j3d.Geometry;
import javax.media.j3d.QuadArray;
import javax.media.j3d.Shape3D;
import javax.vecmath.Point3f;
import javax.vecmath.TexCoord2f;
import javax.vecmath.Vector3f;

public class Sphere {
    private Point3f center;
    private Vector3f direction;
    private float radius;
    private int resolution;

    public Sphere() {
        center = new Point3f(0.0f, 0.0f, 0.0f);
        direction = new Vector3f(0.0f, 0.0f, 0.0f);
        radius = 1.0f;
        resolution = 15;
    }

    public void renderGL() {
        Shape3D shape = new Shape3D();
        shape.setGeometry(createGeometry());
        shape.setAppearance(createAppearance());
        // Add the shape to your scene graph
    }

    private Geometry createGeometry() {
        int numDivisions = resolution;
        int numVertices = numDivisions * numDivisions * 4;
        int numTexCoords = numVertices;

        Point3f[] vertices = new Point3f[numVertices];
        Vector3f[] normals = new Vector3f[numVertices];
        TexCoord2f[] texCoords = new TexCoord2f[numTexCoords];

        int vertexIndex = 0;
        int texCoordIndex = 0;

        for (int j = 0; j < numDivisions / 2; j++) {
            float theta1 = j * 2 * (float) Math.PI / numDivisions - (float) Math.PI / 2;
            float theta2 = (j + 1) * 2 * (float) Math.PI / numDivisions - (float) Math.PI / 2;

            for (int i = 0; i <= numDivisions; i++) {
                float theta3 = i * 2 * (float) Math.PI / numDivisions;

                Vector3f e1 = new Vector3f(
                        (float) Math.cos(theta2) * (float) Math.cos(theta3),
                        (float) Math.sin(theta2),
                        (float) Math.cos(theta2) * (float) Math.sin(theta3)
                );

                Point3f p1 = new Point3f(
                        center.x + radius * e1.x,
                        center.y + radius * e1.y,
                        center.z + radius * e1.z
                );

                Vector3f e2 = new Vector3f(
                        (float) Math.cos(theta1) * (float) Math.cos(theta3),
                        (float) Math.sin(theta1),
                        (float) Math.cos(theta1) * (float) Math.sin(theta3)
                );

                Point3f p2 = new Point3f(
                        center.x + radius * e2.x,
                        center.y + radius * e2.y,
                        center.z + radius * e2.z
                );

                vertices[vertexIndex] = p1;
                normals[vertexIndex] = e1;
                texCoords[texCoordIndex] = new TexCoord2f(i / (float) numDivisions, 2 * (j + 1) / (float) numDivisions);

                vertexIndex++;
                texCoordIndex++;

                vertices[vertexIndex] = p2;
                normals[vertexIndex] = e2;
                texCoords[texCoordIndex] = new TexCoord2f(i / (float) numDivisions, 2 * j / (float) numDivisions);

                vertexIndex++;
                texCoordIndex++;
            }
        }
    
        QuadArray geometry = new QuadArray(numVertices, QuadArray.COORDINATES | QuadArray.NORMALS | QuadArray.TEXTURE_COORDINATE_2);
        geometry.setCoordinates(0, vertices);
        geometry.setNormals(0, normals);
        geometry.setTextureCoordinates(0, 0, texCoords);
    
        return geometry;
    }
    
    private Appearance createAppearance() {
        Appearance appearance = new Appearance();
        // Set up your appearance properties, such as material, texture, etc.
        return appearance;
    }
    
    public Point3f getCenter() {
        return center;
    }
    
    public void setCenter(Point3f center) {
        this.center = center;
    }
    
    public Vector3f getDirection() {
        return direction;
    }
    
    public void setDirection(Vector3f direction) {
        this.direction = direction;
    }
    
    public float getRadius() {
        return radius;
    }
    
    public void setRadius(float radius) {
        this.radius = radius;
    }
    
    public int getResolution() {
        return resolution;
    }
    
    public void setResolution(int resolution) {
        this.resolution = resolution;
    }
}    
