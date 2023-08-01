import com.autodesk.fbx.FbxIO;
import com.autodesk.fbx.FbxImporter;
import com.autodesk.fbx.FbxScene;
import com.autodesk.fbx.FbxSdkManager;
import com.autodesk.fbx.FbxTakeInfo;

import java.io.File;
import java.nio.file.Path;
import java.util.Scanner;

public class FbxReader {
    private FbxFile mFbxFile;
    private Path mFileName;

    public FbxReader(FbxFile pFile, Path fileName) {
        this.mFbxFile = pFile;
        this.mFileName = fileName;
    }

    public boolean read() {
        if (mFbxFile == null) {
            return false;
        }

        String fileName = mFileName.toString();
        return loadScene(mFbxFile.getFbxSdkManager(), mFbxFile.getFbxScene(), fileName);
    }

    public boolean readDebug() {
        return true;
    }

    private boolean loadScene(FbxSdkManager pSdkManager, FbxScene pScene, String pFilename) {
        int lMajor, lMinor, lRevision;
        int i, lTakeCount;
        String lCurrentTakeName;
        boolean bStatus;
        String lPassword;

        FbxImporter lImporter = pSdkManager.createFbxImporter();
        setFileFormat(pFilename, lImporter);

        if (!lImporter.initialize(pFilename)) {
            System.err.println("Call to FbxImporter::initialize() failed. Error returned: " + lImporter.getLastErrorString());

            if (lImporter.getLastErrorID() == FbxIO.FileVersionNotSupportedYet || lImporter.getLastErrorID() == FbxIO.FileVersionNotSupportedAnymore) {
                int[] version = FbxIO.getCurrentVersion();
                lMajor = version[0];
                lMinor = version[1];
                lRevision = version[2];
                System.err.println("FBX version number for this version of the FBX SDK is " + lMajor + "." + lMinor + "." + lRevision);
                System.err.println("FBX version number for file " + pFilename + " is " + lMajor + "." + lMinor + "." + lRevision);
            }

            return false;
        }

        int[] currentVersion = FbxIO.getCurrentVersion();
        lMajor = currentVersion[0];
        lMinor = currentVersion[1];
        lRevision = currentVersion[2];
        System.out.println("FBX version number for this version of the FBX SDK is " + lMajor + "." + lMinor + "." + lRevision);

        boolean isFbx = lImporter.getFileFormat() == FbxImporter.FBX_ENCRYPTED ||
                        lImporter.getFileFormat() == FbxImporter.FBX_ASCII ||
                        lImporter.getFileFormat() == FbxImporter.FBX_BINARY;

        if (isFbx) {
            int[] fileVersion = lImporter.getFileVersion();
            lMajor = fileVersion[0];
            lMinor = fileVersion[1];
            lRevision = fileVersion[2];
            System.out.println("FBX version number for file " + pFilename + " is " + lMajor + "." + lMinor + "." + lRevision);

            System.out.println("Take Information");

            lTakeCount = lImporter.getTakeCount();

            System.out.println("\tNumber of takes: " + lTakeCount);
            System.out.println("\tCurrent take: \"" + lImporter.getCurrentTakeName() + "\"");

            for (i = 0; i < lTakeCount; i++) {
                FbxTakeInfo lTakeInfo = lImporter.getTakeInfo(i);
                System.out.println("\t\tTake " + i);
                System.out.println("\t\t\tName: \"" + lTakeInfo.getName() + "\"");
                System.out.println("\t\t\tDescription: \"" + lTakeInfo.getDescription() + "\"");
                System.out.println("\t\t\tImport Name: \"" + lTakeInfo.getImportName() + "\"");
                System.out.println("\t\t\tImport State: " + (lTakeInfo.isSelected() ? "true" : "false"));
            }

            lImporter.setState(FbxImporter.IMPORT_MATERIAL, true);
            lImporter.setState(FbxImporter.IMPORT_TEXTURE, true);
            lImporter.setState(FbxImporter.IMPORT_LINK, true);
            lImporter.setState(FbxImporter.IMPORT_SHAPE, true);
            lImporter.setState(FbxImporter.IMPORT_GOBO, true);
            lImporter.setState(FbxImporter.IMPORT_ANIMATION, true);
            lImporter.setState(FbxImporter.IMPORT_GLOBAL_SETTINGS, true);
        }

        bStatus = lImporter.importScene(pScene);

        if (!bStatus && lImporter.getLastErrorID() == FbxIO.PasswordError) {
            System.out.println("Please enter password: ");

            Scanner scanner = new Scanner(System.in);
            lPassword = scanner.next();

            lImporter.setPassword(lPassword);

            bStatus = lImporter.importScene(pScene);

            if (!bStatus && lImporter.getLastErrorID() == FbxIO.PasswordError) {
                System.err.println("Password is wrong, import aborted");
            }
        }

        pSdkManager.destroyFbxImporter(lImporter);

        return bStatus;
    }

    private void setFileFormat(String pFilename, FbxImporter pImporter) {
        if (pFilename == null || pImporter == null) {
            return;
        }

        pImporter.setFileFormat(FbxImporter.FBX_BINARY);
        String ext = getFileExtension(pFilename);

        if ("obj".equalsIgnoreCase(ext)) {
            pImporter.setFileFormat(FbxImporter.ALIAS_OBJ);
        } else if ("3ds".equalsIgnoreCase(ext)) {
            pImporter.setFileFormat(FbxImporter.D_STUDIO_3DS);
        } else if ("dxf".equalsIgnoreCase(ext)) {
            pImporter.setFileFormat(FbxImporter.AUTOCAD_DXF);
        }
        // Add other formats if necessary
    }

    private String getFileExtension(String fileName) {
        int dotIndex = fileName.lastIndexOf('.');
        if (dotIndex > 0 && dotIndex < fileName.length() - 1) {
            return fileName.substring(dotIndex + 1);
        }
        return "";
    }
}
