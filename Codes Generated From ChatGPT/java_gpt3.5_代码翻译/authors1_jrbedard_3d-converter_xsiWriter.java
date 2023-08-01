import java.nio.file.Path;

public class XsiWriter {

    private XsiFile xsiFile;
    private Path fileName;
    private boolean writeBinary;

    public XsiWriter(File file, Path fileName) {
        this.xsiFile = (XsiFile) file;
        this.fileName = fileName;
    }

    public boolean write() {
        if (xsiFile == null) {
            return false;
        }

        String fileNameStr = fileName.toString();

        // Initialize result variable
        boolean result = true;

        // SL way of writing dotXSI, but does not write to Binary. So we use the Parser instead
        {
            // Save the file.
            // xsiFile.m_scene.write(fileNameStr);

            // Close the file.
            // xsiFile.m_scene.close();
        }

        Scene scene = xsiFile.getScene();
        if (scene == null) {
            return false;
        }

        scene.synchronize();

        XsiParser parser = scene.getParser();

        if (parser == null) {
            return false;
        }

        // Let's open the file using XsiParser::write
        parser.setOpenMode(OpenMode.WRITE);

        if (writeBinary) {
            parser.setDotXsiFormat(FileFormat.BINARY);
        } else {
            parser.setDotXsiFormat(FileFormat.TEXT);
        }

        result = parser.open(fileNameStr); // Open to write
        if (result) {
            System.out.println("Writing the dotXSI file '" + fileNameStr + "'");

            result = parser.write();
            if (result) {
                result = parser.close();
            } else {
                System.err.println("Error writing to the file '" + fileNameStr + "'");
                // Let's attempt to close the file
                parser.close();
            }
        } else {
            System.err.println("'" + fileNameStr + "' could not be open for writing");
        }

        return result;
    }
}
