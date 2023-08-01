import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.Path;

public class MayaBinaryReader {
    private MayaFile mayaFile;
    private Path fileName;
    private RandomAccessFile randomAccessFile;
    private long pc;
    private long fileSize;

    public MayaBinaryReader(MayaFile mayaFile, Path fileName) {
        this.mayaFile = mayaFile;
        this.fileName = fileName;
    }

    public void movePC(long forward) {
        pc += forward;
        try {
            randomAccessFile.seek(pc);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public boolean readBlock(byte[] dest, long size) {
        pc = randomAccessFile.getFilePointer();
        try {
            if (randomAccessFile.read(dest) != -1 && randomAccessFile.length() == pc) {
                return false;
            }
            pc += size;
            randomAccessFile.seek(pc);
            return true;
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public void fileSize() {
        try {
            randomAccessFile.seek(0);
            fileSize = randomAccessFile.length();
            randomAccessFile.seek(0);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public boolean read() {
        if (mayaFile == null) {
            return false;
        }

        String fileNameString = fileName.toString();
        File file = new File(fileNameString);

        try {
            randomAccessFile = new RandomAccessFile(file, "r");
        } catch (IOException e) {
            System.err.println("Couldn't open .MB file '" + fileNameString + "'");
            return false;
        }

        String FOR4 = "FOR4";
        String XFRMCREA = "XFRMCREA";
        String DMSHCREA = "DMSHCREA";

        String FLGS = "FLGS";
        String DBLE = "DBLE";
        String FLT2 = "FLT2";
        String STR = "STR";
        String MESH = "MESH";

        // Too difficult to parse, and probably illegal...

        try {
            randomAccessFile.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return true;
    }
}
