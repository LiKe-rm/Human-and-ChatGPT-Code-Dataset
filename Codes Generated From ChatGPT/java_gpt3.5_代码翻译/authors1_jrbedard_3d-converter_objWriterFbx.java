import java.io.*;
import java.nio.file.Path;

public class ObjWriterFbx {
    private FbxFile fbxFile;
    private Path fileName;

    public ObjWriterFbx(File file, Path fileName) {
        this.fbxFile = (FbxFile) file;
        this.fileName = fileName;
    }

    public boolean write() {
        if (fbxFile == null) {
            return false;
        }

        String fileNameString = fileName.toString();

        FbxExporter exporter = fbxFile.getFbxSdkManager().createFbxExporter();

        if (!exporter.initialize(fileNameString)) {
            System.err.println("Call to FbxExporter.initialize() failed. Error Returned : " + exporter.getLastErrorString());
            return false;
        }

        System.out.println("Writing .OBJ file '" + fileNameString + "'.");

        exporter.setState(FbxExporter.ExportState.EXPORT_MODEL, true);
        exporter.setState(FbxExporter.ExportState.EXPORT_MATERIAL, true);
        exporter.setState(FbxExporter.ExportState.EXPORT_TEXTURE, true);

        exporter.setFileFormat(FbxExporter.FileFormat.ALIAS_OBJ);

        StreamOptions exportOptions = exporter.getExportOptions();

        boolean status = exporter.export(fbxFile.getFbxScene(), exportOptions);

        if (!status) {
            System.err.println("Error returned: " + exporter.getLastErrorString());
        }

        fbxFile.getFbxSdkManager().destroyFbxExporter(exporter);

        replaceFbxSdkHeader(fileNameString);

        Path mtlFilePath = fileName.resolveSibling(fileName.getFileName().toString().replaceAll("\\.obj$", ".mtl"));
        String mtlFileName = mtlFilePath.toString();

        // replaceFbxSdkHeader(mtlFileName);

        return status;
    }

    public boolean replaceFbxSdkHeader(String fileName) {
        try {
            FileInputStream fis = new FileInputStream(fileName);
            BufferedReader reader = new BufferedReader(new InputStreamReader(fis));
            StringBuilder tempStream = new StringBuilder();

            tempStream.append(reader.lines().skip(3).collect(Collectors.joining("\n")));

            reader.close();

            FileOutputStream fos = new FileOutputStream(fileName);
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(fos));

            writer.write("# File Created by the OBJ file format converter\n");
            writer.write("# jrbedard.com\n");
            writer.write("#\n");
            writer.write(tempStream.toString());

            writer.close();

            return true;
        } catch (IOException e) {
            System.err.println("Couldn't open file '" + fileName + "'");
            return false;
        }
    }
}
