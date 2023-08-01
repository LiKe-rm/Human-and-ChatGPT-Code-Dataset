import java.util.ArrayList;
import java.util.List;

public class ObjStlConverter {
    private StlFile stlFile;
    private ObjStlOptions options;

    public ObjStlConverter() {
        stlFile = null;
        options = null;
    }

    public boolean parseOptions(String optionString) {
        options = new ObjStlOptions();
        FromObjConverter.parseOptions(optionString, options);
        return true;
    }

    public boolean convert(File objFile, File otherFile) {
        stlFile = FromObjConverter.initConversion(StlFile.class, objFile, otherFile);
        if (stlFile == null || options == null) {
            return false;
        }

        System.out.println("Converting OBJ file format into STL file format...");

        List<ObjFile.Group> groups = ((ObjFile) objFile).getGroupVector();
        for (ObjFile.Group group : groups) {
            String objectName = group.getGroupName();

            if (group.getFaceCount() <= 0) {
                continue;
            }

            StlFile.Solid solid = new StlFile.Solid(objectName);

            List<ObjFile.Face> objFaces = group.getFaceVector();
            for (ObjFile.Face face : objFaces) {
                StlFile.Solid.Facet newFacet = new StlFile.Solid.Facet();

                int vertexCount = face.vertexCount();
                if (vertexCount > 3) {
                    vertexCount = 3;
                }

                for (int v = 0; v < vertexCount; ++v) {
                    ObjFile.Vertex vertex = face.vertex(v);
                    int vertexPosition = vertex.position() - 1;

                    if (vertexPosition >= ((ObjFile) objFile).getVertexPositionVector().size()) {
                        continue;
                    }

                    Vector3D vertPos = ((ObjFile) objFile).getVertexPositionVector().get(vertexPosition);
                    newFacet.getVertices().add(vertPos);

                    // TODO: process the facet normal...
                    // Vector3D normal = new Vector3D(0.0, 0.0, 1.0);
                    // newFacet.setNormal(normal);
                }

                solid.getFacetVector().add(newFacet);
            }

            stlFile.getSolidVector().add(solid);
        }

        return true;
    }
}
