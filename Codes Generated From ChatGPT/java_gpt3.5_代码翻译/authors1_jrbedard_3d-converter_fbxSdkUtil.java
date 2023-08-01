import com.autodesk.fbx.FbxScene;
import com.autodesk.fbx.FbxNode;
import com.autodesk.fbx.FbxVector4;
import com.autodesk.fbx.FbxMatrix;

public class FbxSdkUtil {

    public static boolean getSceneInfo(FbxScene scene) {
        if (scene == null) {
            return false;
        }

        FbxSceneInfo sceneInfo = scene.getSceneInfo();
        if (sceneInfo != null) {
            System.out.println("Meta-Data:");
            System.out.println("Title: " + sceneInfo.getTitle());
            System.out.println("Subject: " + sceneInfo.getSubject());
            System.out.println("Author: " + sceneInfo.getAuthor());
            System.out.println("Keywords: " + sceneInfo.getKeywords());
            System.out.println("Revision: " + sceneInfo.getRevision());
            System.out.println("Comment: " + sceneInfo.getComment());
        }

        return true;
    }

    public static FbxMatrix getGeometricTransform(FbxNode node) {
        if (node == null) {
            return new FbxMatrix();
        }

        FbxMatrix transMat = node.getGlobalMatrix(FbxNode.DestinationSet);
        return transMat;
    }

    public static Vector3D transformAndConvertFbxVector(FbxVector4 vec, FbxMatrix transMat) {
        vec.set(3, 1.0f); // allow transformations
        Vector3D vector = new Vector3D(3);

        FbxVector4 transCol0 = transMat.getColumn(0);
        FbxVector4 transCol1 = transMat.getColumn(1);
        FbxVector4 transCol2 = transMat.getColumn(2);

        vector.set(0, transCol0.get(0) * vec.get(0) + transCol0.get(1) * vec.get(1) + transCol0.get(2) * vec.get(2) + transCol0.get(3) * vec.get(3));
        vector.set(1, transCol1.get(0) * vec.get(0) + transCol1.get(1) * vec.get(1) + transCol1.get(2) * vec.get(2) + transCol1.get(3) * vec.get(3));
        vector.set(2, transCol2.get(0) * vec.get(0) + transCol2.get(1) * vec.get(1) + transCol2.get(2) * vec.get(2) + transCol2.get(3) * vec.get(3));
        return vector;
    }
}
