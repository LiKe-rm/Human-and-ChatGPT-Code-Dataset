// Copyright(c) 2005-2006. All Rights Reserved
// By Jean-René Bédard (https://github.com/jrbedard/3d-converter)

import com.autodesk.fbx.FbxImporter;
import com.autodesk.fbx.FbxScene;
import com.autodesk.fbx.FbxManager;
import java.nio.file.Path;
import org.apache.commons.io.FilenameUtils;

public class Fbx3dsReader {

    private FbxFile fbxFile;
    private Path fileName;

    public Fbx3dsReader(FbxFile fbxFile, Path fileName) {
        this.fbxFile = fbxFile;
        this.fileName = fileName;
    }

    public boolean read() {
        if (fbxFile == null) {
            return false;
        }

        String nativeFilePath = FilenameUtils.separatorsToSystem(fileName.toString());
        FbxManager manager = fbxFile.getFbxSdkManager();
        FbxImporter importer = FbxImporter.create(manager, "");

        importer.setFileFormat(FbxImporter.e3D_STUDIO_3DS);

        if (!importer.initialize(nativeFilePath)) {
            System.err.println("Call to FbxImporter.initialize() failed. Error returned: " + importer.getLastErrorString());
            return false;
        }

        FbxScene scene = fbxFile.getFbxScene();
        boolean status = importer.importScene(scene);

        if (!status) {
            System.err.println("Error importing the 3DS scene: " + importer.getLastErrorString());
            return false;
        }

        return true;
    }

    public boolean readDebug() {
        return true;
    }
}
