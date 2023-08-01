// Copyright(c) 2005-2006. All Rights Reserved
// By Jean-René Bédard (https://github.com/jrbedard/3d-converter)

import com.autodesk.fbx.*; // FBX SDK for Java

import java.nio.file.Path;

public class Writer3dsFbx {
    private FbxFile fbxFile;
    private Path fileName;
    private boolean writeBinary;

    public Writer3dsFbx(FbxFile pFile, Path fileName) {
        this.fbxFile = pFile;
        this.fileName = fileName;
        this.writeBinary = true;
    }

    public boolean write() {
        if (fbxFile == null) {
            return false;
        }

        int[] version = FbxIO.getCurrentVersion();
        String fileNameStr = fileName.toString();

        System.out.println("Writing .3DS file '" + fileNameStr + "'.");

        FbxExporter exporter = FbxExporter.create(fbxFile.getFbxSdkManager());

        if (!exporter.initialize(fileNameStr)) {
            System.err.println("Call to FbxExporter::initialize() failed. Error returned: " + exporter.getLastErrorString());
            return false;
        }

        exporter.setState(FbxExporter.ExportStates.EXPORT_MODEL, true);
        exporter.setState(FbxExporter.ExportStates.EXPORT_MATERIAL, true);
        exporter.setState(FbxExporter.ExportStates.EXPORT_TEXTURE, true);
        exporter.setState(FbxExporter.ExportStates.EXPORT_LINK, true);
        exporter.setState(FbxExporter.ExportStates.EXPORT_SHAPE, true);

        exporter.setFileFormat(FbxExporter.FileFormat.e3D_STUDIO_3DS);

        boolean status = exporter.exportScene(fbxFile.getFbxScene());

        if (!status) {
            System.err.println("Error returned: " + exporter.getLastErrorString());
        }

        fbxFile.getFbxSdkManager().destroyFbxExporter(exporter);

        return status;
    }
}
