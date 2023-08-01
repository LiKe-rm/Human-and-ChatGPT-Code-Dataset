// Copyright(c) 2005-2006. All Rights Reserved
// By Jean-René Bédard (https://github.com/jrbedard/3d-converter)

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Path;

public class XsiReader {

    private XsiFile xsiFile;
    private Path fileName;

    public XsiReader(XsiFile file, Path fileName) {
        this.xsiFile = file;
        this.fileName = fileName;
    }

    public boolean read() {
        if (xsiFile == null) {
            return false;
        }

        String filePath = fileName.toString();

        // Check if it's 3.6 Binary // v1hack
        try (FileInputStream fis = new FileInputStream(new File(filePath))) {
            byte[] header = new byte[11];
            fis.read(header);
            String headerStr = new String(header);

            if (headerStr.contains("xsi 0360bin")) { // Detect v3.6 binary
                System.err.println("Sorry, the XSI importer does not support dotXSI binary file version 3.6.\n" +
                        "Please re-save this file in dotXSI version 3.6 ascii or 3.5 binary.");
                return false;
            }
        } catch (IOException e) {
            System.err.println("Couldn't open .XSI file '" + filePath + "'");
            return false;
        }

        // Read the scene
        Scene scene = xsiFile.getScene();

        if (scene == null) {
            return false;
        }

        System.out.println("Reading .XSI file '" + fileName.toString() + "'.");

        boolean result = scene.open(filePath);
        if (!result) {
            System.err.println("Failed to open dotXSI file: " + fileName.toString());
            return false;
        }

        result = scene.read();
        if (!result) {
            System.err.println("Failed to open dotXSI file: " + fileName.toString());
            return false;
        }

        return readXsiHeader();
    }

    public boolean readDebug() {
        return true;
    }

    public boolean readXsiHeader() {
        Scene scene = xsiFile.getScene();
        XsiParser parser = scene.getParser();

        if (parser == null) {
            return false;
        }

        // First, we dump the file information (header)
        System.out.println("File version: " + parser.getDotXSIFileVersionMajor() + "." + parser.getDotXSIFileVersionMinor());

        if (parser.getDotXSIFormat() == XsiParser.FORMAT_TEXT) {
            System.out.println("Format: TEXT");
        } else if (parser.getDotXSIFormat() == XsiParser.FORMAT_BINARY) {
            System.out.println("Format: BINARY");
        }

        return true;
    }
}
