import com.autodesk.fbx.FbxScene;
import com.autodesk.fbx.FbxSdkManager;
import com.autodesk.fbx.FbxExporter;
import com.autodesk.fbx.FbxIO;

import java.nio.file.Path;

public class FbxWriter {
    private FbxFile fbxFile;
    private Path fileName;

    public FbxWriter(FbxFile file, Path fileName) {
        this.fbxFile = file;
        this.fileName = fileName;
    }

    public boolean write() {
        if (fbxFile == null) {
            return false;
        }

        String filePath = fileName.toString();

        FbxSdkManager sdkManager = fbxFile.getFbxSdkManager();
        FbxScene scene = fbxFile.getFbxScene();

        boolean saveAsBinary = true;
        boolean embedMedia = false;
        boolean saveAsVersion5 = false;

        int major, minor, revision;

        FbxExporter exporter = sdkManager.createFbxExporter();

        if (!exporter.initialize(filePath)) {
            System.err.println("Call to FbxExporter::initialize() failed. Error returned: " + exporter.getLastErrorString());
            return false;
        }

        FbxIO.getCurrentVersion();
        System.out.println("FBX version number for this version of the FBX SDK is " + major + "." + minor + "." + revision);

        exporter.setState(FbxExporter.ExportOption.EXPORT_MATERIAL, true);
        exporter.setState(FbxExporter.ExportOption.EXPORT_TEXTURE, true);
        exporter.setState(FbxExporter.ExportOption.EXPORT_TEXTURE_AS_EMBEDDED, embedMedia);
        exporter.setState(FbxExporter.ExportOption.EXPORT_LINK, true);
        exporter.setState(FbxExporter.ExportOption.EXPORT_SHAPE, true);
        exporter.setState(FbxExporter.ExportOption.EXPORT_GOBO, true);
        exporter.setState(FbxExporter.ExportOption.EXPORT_ANIMATION, true);
        exporter.setState(FbxExporter.ExportOption.EXPORT_GLOBAL_SETTINGS, true);

        if (saveAsVersion5) {
            System.out.println("Writing FBX file version 5");
            exporter.setFileFormat(saveAsBinary ? FbxExporter.FileFormat.FBX_50_BINARY : FbxExporter.FileFormat.FBX_50_ASCII);
        } else {
            System.out.println("Writing FBX file version 6");
            exporter.setFileModeBinary(saveAsBinary);
        }

        boolean status = exporter.export(scene);

        if (!status) {
            System.err.println("Error Returned: " + exporter.getLastErrorString());
        }

        sdkManager.destroyFbxExporter(exporter);

        System.out.println("Done.");

        return status;
    }
}
