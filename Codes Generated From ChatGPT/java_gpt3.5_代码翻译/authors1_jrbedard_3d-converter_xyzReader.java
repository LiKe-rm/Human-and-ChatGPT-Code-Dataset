import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Path;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class XyzReader {

    private XyzFile xyzFile;
    private Path fileName;
    private int sampling;

    public XyzReader(File file, Path fileName, short sampling) {
        this.xyzFile = (XyzFile) file;
        this.fileName = fileName;
        this.sampling = 1 << (sampling - 9);
        if (this.sampling < 1) {
            this.sampling = 1; // avoid dividing by 0
        }
    }

    public boolean read() {
        if (xyzFile == null) {
            return false;
        }

        String fileNameStr = fileName.toString();

        System.out.println("Reading .XYZ file '" + fileNameStr + "'.");

        try (BufferedReader br = new BufferedReader(new FileReader(fileNameStr))) {
            String line;
            int lineNum = 0;

            Pattern pattern = Pattern.compile("(\\d+\\.?\\d*)\\s+(\\d+\\.?\\d*)\\s+(\\d+\\.?\\d*)\\s*(\\d+\\.?\\d*)?\\s*(\\d+\\.?\\d*)?\\s*(\\d+\\.?\\d*)?");

            while ((line = br.readLine()) != null) {
                lineNum++;

                Matcher matcher = pattern.matcher(line);
                if (matcher.find()) {
                    Vector3D vertex = new Vector3D(
                            Double.parseDouble(matcher.group(1)),
                            Double.parseDouble(matcher.group(2)),
                            Double.parseDouble(matcher.group(3))
                    );

                    Vector3D texCoord = new Vector3D(
                            matcher.group(4) != null ? Double.parseDouble(matcher.group(4)) : 0,
                            matcher.group(5) != null ? Double.parseDouble(matcher.group(5)) : 0,
                            matcher.group(6) != null ? Double.parseDouble(matcher.group(6)) : 0
                    );

                    if (lineNum % sampling == 0) {
                        xyzFile.getVertexPositionVector().add(vertex);
                        xyzFile.getTextureCoordVector().add(texCoord);
                    }
                } else {
                    System.err.println("Invalid line, file: '" + fileNameStr + "', line: " + lineNum);
                }
            }
            return true;
        } catch (IOException e) {
            System.err.println("Couldn't open .XYZ file '" + fileNameStr + "'");
            return false;
        }
    }
}
