import java.util.ArrayList;
import java.util.List;

public class MayaObjConverter {
    private MayaFile mayaFile;
    private MayaObjOptions options;
    private ObjFile objFile;

    public MayaObjConverter() {
        this.mayaFile = null;
        this.options = null;
    }

    public boolean parseOptions(String optionString) {
        this.options = new MayaObjOptions();
        // Parse options here if necessary
        return true;
    }

    public boolean convert(MayaFile mayaFile, ObjFile objFile) {
        this.mayaFile = mayaFile;
        this.objFile = objFile;

        if (this.mayaFile == null || this.options == null) {
            return false;
        }

        System.out.println("Converting Maya file format into OBJ file format...");

        List<ObjFile.Group> groups = objFile.getGroupVector();
        List<MayaFile.Mesh> meshes = mayaFile.getMeshVector();

        for (MayaFile.Mesh mesh : meshes) {
            String meshName = mesh.getMeshName();

            if (mesh.getPolyFaceVector().size() <= 0) {
                continue;
            }

            System.out.println("Processing " + meshName + "...");

            ObjFile.Group group = new ObjFile.Group(meshName);

            // Append Vertex positions
            List<Vector3D> mayaVertexVector = mesh.getVertexPositionVector();
            List<Vector3D> objVertexVector = objFile.getVertexPositionVector();
            objVertexVector.addAll(mayaVertexVector);

            // Append Texture coordinates
            List<Vector3D> mayaUvVector = mesh.getTextureCoordVector();
            List<Vector3D> objUvVector = objFile.getTextureCoordVector();
            objUvVector.addAll(mayaUvVector);

            // Append Normals
            List<Vector3D> mayaNormalVector = mesh.getNormalVector();
            List<Vector3D> objNormalVector = objFile.getNormalVector();
            objNormalVector.addAll(mayaNormalVector);

            // Faces
            List<MayaFile.Mesh.PolyFace> polyFaces = mesh.getPolyFaceVector();
            List<ObjFile.Face> groupFaceVector = new ArrayList<>(polyFaces.size());

            for (MayaFile.Mesh.PolyFace polyFace : polyFaces) {
                MayaFile.Mesh.PolyFace.Face mayaFace = polyFace.getFace();
                MayaFile.Mesh.PolyFace.Mu mayaMu;

                if (polyFace.hasTextureCoordinate()) {
                    mayaMu = polyFace.getMu();
                }

                ObjFile.Face objFace = new ObjFile.Face();

                int edgeCount = mayaFace.edgeCount();

                for (int v = 0; v < edgeCount; ++v) {
                    int vIndex = 0;
                    int uvIndex = 0;
                    int normalIndex = 0;

                    int edgeIndex = mayaFace.getEdgeVector().get(v);

                    if (edgeIndex >= 0) {
                        vIndex = mesh.getEdgeVector().get(edgeIndex)[0] + 1;
                    } else {
                        vIndex = mesh.getEdgeVector().get(Math.abs(edgeIndex) - 1)[1] + 1;
                    }

                    // UVs
                    if (polyFace.hasTextureCoordinate()) {
                        uvIndex = mayaMu.getUvVector().get(v) + 1;
                    }

                    // Normals
                    if (polyFace.hasNormal()) {
                        normalIndex = mayaFace.getNormalVector().get(v) + 1;
                    }

                    // Add vertex to OBJ face
                    objFace.addVertex(new ObjFile.Vertex(vIndex, uvIndex, normalIndex));
                }

                group.addFace(objFace); // Add face to OBJ group
            }

            objFile.addGroup(group); // Add group to OBJ file
        }

        // Materials
        {
            MtlFile mtlFile = objFile.getMaterialFile();

            if (mtlFile != null) {
                // Retrieve and set material properties here
            }
        }

        return true;
    }
}

