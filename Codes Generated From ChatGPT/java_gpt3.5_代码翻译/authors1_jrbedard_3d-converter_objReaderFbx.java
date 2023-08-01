import com.autodesk.fbx.*;

import java.nio.file.Path;

public class ObjReaderFbx {
    private FbxFile fbxFile;
    private Path fileName;

    public ObjReaderFbx(File file, Path fileName) {
        this.fbxFile = (FbxFile) file;
        this.fileName = fileName;
    }

    public boolean read() {
        if (fbxFile == null) {
            return false;
        }

        String fileNameString = fileName.toString();
        int major, minor, revision;

        System.out.println("Parsing .OBJ file '" + fileNameString + "'.");

        // Create an importer.
        FbxImporter importer = FbxImporter.Create(fbxFile.getFbxSdkManager(), "");
        importer.setFileFormat(FbxIO.FileFormat.eALIAS_OBJ);

        // Initialize the importer by providing a filename.
        if (!importer.Initialize(fileNameString)) {
            System.err.println("Call to FbxImporter.Initialize() failed. Error returned: " + importer.GetLastErrorString());

            if (importer.GetLastErrorID() == FbxStatus.ErrorCode.eFileVersionNotSupportedYet ||
                    importer.GetLastErrorID() == FbxStatus.ErrorCode.eFileVersionNotSupportedAnymore) {
                FbxIO.GetCurrentVersion();
                major = FbxIO.sMajor;
                minor = FbxIO.sMinor;
                revision = FbxIO.sRevision;
                importer.GetFileVersion();
                System.err.println("FBX version number for this version of the FBX SDK is " + major + "." + minor + "." + revision +
                        " FBX version number for file '" + fileName.toString() + "' is " + major + "." + "." + minor + "." + revision);
            }

            return false;
        }

        // Import the scene.
        boolean status = importer.Import(fbxFile.getFbxScene());

        if (!status) {
            System.err.println("Error importing the OBJ scene: " + importer.GetLastErrorString());
            return false;
        }

        return true;
    }

    public boolean readDebug() {
        return true;
    }
}
