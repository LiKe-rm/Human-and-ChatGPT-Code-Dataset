import com.autodesk.fbx.*;

import java.util.*;

public class FbxObjConverter {
    private FbxFile mFbxFile;
    private FbxObjOptions mOptions;
    private int mMaterialIndexOffset;
    private ObjFile mObjFile;

    public FbxObjConverter() {
        mFbxFile = null;
        mOptions = null;
        mMaterialIndexOffset = 0;
    }

    public boolean parseOptions(String optionString) {
        mOptions = new FbxObjOptions();
        ObjConverter.parseOptions(optionString, mOptions);
        return true;
    }

    // Convert a FBX file into an OBJ file
    public boolean convert(FbxFile otherFile, ObjFile objFile) {
        // Initialize FBX -> OBJ
        mFbxFile = FbxFile.initConversion(otherFile, objFile);
        mObjFile = objFile;
        if (mFbxFile == null || mOptions == null) {
            return false;
        }

        System.out.println("Converting FBX file format into OBJ file format...");

        // Get FBX SDK objects
        FbxSdkManager fbxSdkManager = mFbxFile.getFbxSdkManager();
        FbxScene scene = mFbxFile.getFbxScene();

        if (fbxSdkManager == null || scene == null) {
            return false;
        }

        // Get the scene meta data
        FbxSdkUtil.getSceneInfo(scene);

        FbxNode rootNode = scene.getRootNode();

        if (rootNode != null) {
            for (int i = 0; i < rootNode.getChildCount(); ++i) {
                nodeRecurse(rootNode.getChild(i));
            }
        }

        return true;
    }

    public boolean nodeRecurse(FbxNode node) {
        if (node == null) {
            return false;
        }

        FbxNodeAttribute.EType attributeType;

        if (node.getNodeAttribute() == null) {
            System.out.println("Warning: NULL Node Attribute");
        } else {
            attributeType = node.getNodeAttribute().getAttributeType();
            switch (attributeType) {
                case eMARKER:
                    System.out.println("Marker detected and skipped");
                    break;
                case eSKELETON:
                    System.out.println("Skeleton detected and skipped");
                    break;
                case eMESH:
                    convertMesh(node);
                    break;
                case eNURB:
                    System.out.println("NURB detected and skipped");
                    break;
                case ePATCH:
                    System.out.println("Patch detected and skipped");
                    break;
                case eCAMERA:
                    System.out.println("Camera detected and skipped");
                    break;
                case eLIGHT:
                    System.out.println("Light detected and skipped");
                    break;
            }
        }

        for (int i = 0; i < node.getChildCount(); ++i) {
            nodeRecurse(node.getChild(i));
        }

        return true;
    }

    public boolean convertMesh(FbxNode node) {
        if (node == null) {
            return false;
        }

        FbxMesh mesh = node.getMesh();
        if (mesh == null) {
            return false;
        }

        boolean status = false;

        ObjFile.Group group = new ObjFile.Group(node.getName());

        // Conversion methods omitted for brevity
        // ...

        return true;
    }
}
