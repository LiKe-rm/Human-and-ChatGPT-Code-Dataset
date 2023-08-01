import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class StlAsciiWriter {
    private StlFile stlFile;
    private Path fileName;

    public StlAsciiWriter(StlFile stlFile, String fileName) {
        this.stlFile = stlFile;
        this.fileName = Paths.get(fileName);
    }

    public boolean write() {
        if (stlFile.getSolidVector().isEmpty()) {
            System.err.println("No STL information to write!");
            return false;
        }

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName.toFile()))) {
            for (StlFile.Solid solid : stlFile.getSolidVector()) {
                String solidName = solid.getSolidName();
                writer.write("solid " + solidName + "\n");

                List<StlFile.Solid.Facet> facets = solid.getFacetVector();

                if (facets.isEmpty()) {
                    continue;
                }

                for (StlFile.Solid.Facet facet : facets) {
                    double[] normal = facet.getNormal();
                    writer.write("  facet normal " + normal[0] + " " + normal[1] + " " + normal[2] + "\n");

                    List<double[]> vertices = facet.getVertices();
                    writer.write("    outer loop\n");

                    for (double[] vertex : vertices) {
                        writer.write("      vertex " + vertex[0] + " " + vertex[1] + " " + vertex[2] + "\n");
                    }

                    writer.write("    endloop\n");
                    writer.write("  endfacet\n");
                }

                writer.write("endsolid " + solidName + "\n");
            }
            return true;
        } catch (IOException e) {
            System.err.println("Couldn't write to STL file: " + fileName);
            return false;
        }
    }
}
