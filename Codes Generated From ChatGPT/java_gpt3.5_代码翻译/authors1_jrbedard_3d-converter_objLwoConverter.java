import java.util.*;
import java.nio.*;

public class ObjLwoConverter {
    private LwoFile lwoFile;
    private ObjLwoOptions options;

    public ObjLwoConverter() {
        lwoFile = null;
        options = null;
    }

    public boolean parseOptions(String optionString) {
        options = new ObjLwoOptions();
        FromObjConverter.parseOptions(optionString, options);
        return true;
    }

    // Convert an OBJ file into a LWO file
    public boolean convert(ObjFile objFile, File otherFile) {
        // Initialize OBJ -> LWO
        lwoFile = initConversion(LwoFile.class, objFile, otherFile);
        if (lwoFile == null || options == null)
            return false;

        System.out.println("Converting OBJ file format into LWO file format...");

        List<ObjFile.Group> groups = objFile.getGroupVector();

        // Create the LWO layer
        short layerID = 0;
        LwoFile.Layer layer = new LwoFile.Layer(layerID);
        layer.setLayerName(groups.get(0).getGroupName()); // Set the name to the first group.

        short partID = 0;

        for (ObjFile.Group group : groups) {
            String objectName = group.getGroupName();

            // Verify that it is a valid group
            if (group.getFaceCount() <= 0)
                continue;

            // Add the LWO part name
            layer.getPartVector().add(objectName);

            // Extract only the referred block of vertex, texture coordinates, and normals
            ObjFile.Group.ChannelsRange channelsRange = group.getChannelsRange();

            // Vertex Positions
            {
                List<Vector3D> vertices = objFile.getVertexPositionVector();
                Pair<ListIterator<Vector3D>, ListIterator<Vector3D>> vertexCopyIterators = createVertexCopyIterators(
                        channelsRange, vertices);

                if (vertexCopyIterators != null) {
                    List<Vector3D> lwoLayerVertexVec = layer.getVertexPositionVector();
                    lwoLayerVertexVec.addAll(vertices.subList(vertexCopyIterators.getFirst().nextIndex(),
                            vertexCopyIterators.getSecond().nextIndex()));
                }
            }

            // Faces
            List<ObjFile.Face> faces = group.getFaceVector();
            layer.getFaceVector().ensureCapacity(faces.size());
            int faceIndex = 0;
            int vertexCount = 0;

            for (ObjFile.Face face : faces) {
                faceIndex = faces.indexOf(face);

                // Create LWO polygon "face"
                LwoFile.Layer.Face lwoFace = new LwoFile.Layer.Face();

                // Set the surface ID assigned to the polygon
                if (!options.isTranslateMaterials() || face.getMaterialID() == -1)
                    lwoFace.setSurface(0);
                else
                    lwoFace.setSurface(face.getMaterialID());

                // Set the part ID of the polygon
                lwoFace.setPart(partID);

                // Set the smoothing group of the polygon
                ObjFile.SmoothingGroupPair objSmoothingGroup = face.getSmoothingGroup();
                lwoFace.setSmoothingGroup(objSmoothingGroup);
                layer.getSGVector().add(objSmoothingGroup.getSecond());

                vertexCount = face.vertexCount();

                for (int v = 0; v < vertexCount; ++v) {
                    ObjFile.Vertex vertex = face.vertex(v);

                    // Vertex position index
                    int vertexIndex = vertex.position() - 1;
                    lwoFace.getVertexIndexVector().add(vertexIndex);
                    // Texture coordinate index
                    if (options.isTranslateUVs() && vertex.hasTextureCoordinate()) {
                        Vector3D uv = objFile.textureCoordinate(vertex.textureCoordinate());
                        LwoFile.Layer.TexCoord lwoTexCoord = new LwoFile.Layer.TexCoord();
                        lwoTexCoord.setFaceIndex(faceIndex);
                        lwoTexCoord.setTexCoord(uv);
                        layer.getTexCoordMap().get(vertexIndex).add(lwoTexCoord);
                    }
                }
                layer.addFace(lwoFace);
            }

            ++partID;
        }

        // Create Lwo material library
        if (options.isTranslateMaterials()) {
            createLwoMaterialLibrary(layer, objFile);
        }

        lwoFile.addLayer(layer);

        return true;
    }

    public boolean createLwoMaterialLibrary(LwoFile.Layer layer, ObjFile objFile) {
        MtlFile mtlFile = objFile.getMaterialFile();

        if (mtlFile == null) {
            return false;
        }

        int imageIndex = 0;

        Map<String, MtlFile.Material> materials = mtlFile.getMaterialMap();

        for (Map.Entry<String, MtlFile.Material> entry : materials.entrySet()) {
            String materialName = entry.getKey();
            MtlFile.Material material = entry.getValue();

            if (material == null) {
                continue;
            }

            LwoFile.Layer.Surface newSurface = new LwoFile.Layer.Surface();
            newSurface.setSurfaceName(materialName);

            // TODO: Parse other material information

            // Texture Map
            if (options.isTranslateMaps() && material.hasTexMap()) {
                // Add image path to the vector
                layer.addImage(imageIndex, material.getTexMap());

                // Add image index to the surface
                newSurface.setImageIndex(imageIndex);

                // Increment image index
                ++imageIndex;
            }

            layer.getSurfaceMap().put(materialName, newSurface);
        }

        return true;
    }

    // Helper methods and classes should be implemented here, such as Pair,
    // Vector3D, ObjFile, LwoFile, etc.
}
