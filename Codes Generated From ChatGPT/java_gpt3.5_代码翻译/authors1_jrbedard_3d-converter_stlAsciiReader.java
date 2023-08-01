import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class StlAsciiReader {
    private StlFile stlFile;
    private Path fileName;

    public StlAsciiReader(StlFile stlFile, String fileName) {
        this.stlFile = stlFile;
        this.fileName = Paths.get(fileName);
    }

    public boolean read() {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName.toFile()))) {
            String line;
            int lineNum = 0;

            while ((line = reader.readLine()) != null) {
                lineNum++;

                String[] tokens = line.trim().split("\\s+");

                if (tokens.length == 0) {
                    continue;
                }

                String command = tokens[0];

                if (command.equalsIgnoreCase("solid")) {
                    String name = tokens.length > 1 ? tokens[1] : "";
                    StlFile.Solid solid = new StlFile.Solid(name);
                    stlFile.getSolidVector().add(solid);
                }

                if (command.equalsIgnoreCase("facet")) {
                    double[] normal = new double[3];
                    for (int i = 0; i < 3; i++) {
                        normal[i] = Double.parseDouble(tokens[i + 2]);
                    }
                    StlFile.Solid.Facet newFacet = new StlFile.Solid.Facet();
                    stlFile.getCurrentSolid().getFacetVector().add(newFacet);
                    stlFile.getCurrentSolid().getCurrentFacet().setNormal(normal);
                }

                if (command.equalsIgnoreCase("vertex")) {
                    double[] vertex = new double[3];
                    for (int i = 0; i < 3; i++) {
                        vertex[i] = Double.parseDouble(tokens[i + 1]);
                    }
                    stlFile.getCurrentSolid().getCurrentFacet().getVertices().add(vertex);
                }
            }
            return true;
        } catch (IOException e) {
            System.err.println("Couldn't open Ascii .STL file: " + fileName);
            return false;
        }
    }
}
