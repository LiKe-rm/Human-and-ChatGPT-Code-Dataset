import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.zip.Deflater;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;
import java.util.zip.Inflater;

public class GZipJava {

    public static byte[] compress(byte[] data, String filename, String comment) throws IOException {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        try (GZIPOutputStream gzos = new GZIPOutputStream(baos)) {
            gzos.setComment(comment);
            gzos.write(filename.getBytes(StandardCharsets.ISO_8859_1));
            gzos.write(0); // NULL terminator for filename
            gzos.write(data);
        }
        return baos.toByteArray();
    }

    public static byte[] decompress(byte[] compressedData) throws IOException {
        ByteArrayInputStream bais = new ByteArrayInputStream(compressedData);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        try (GZIPInputStream gzis = new GZIPInputStream(bais)) {
            byte[] buffer = new byte[1024];
            int len;

            while ((len = gzis.read(buffer)) > 0) {
                baos.write(buffer, 0, len);
            }
        }

        return baos.toByteArray();
    }

    public static String getFilename(byte[] compressedData) throws IOException {
        ByteArrayInputStream bais = new ByteArrayInputStream(compressedData);
        try (GZIPInputStream gzis = new GZIPInputStream(bais)) {
            return gzis.getFilename();
        }
    }

    public static String getComment(byte[] compressedData) throws IOException {
        ByteArrayInputStream bais = new ByteArrayInputStream(compressedData);
        try (GZIPInputStream gzis = new GZIPInputStream(bais)) {
            return gzis.getComment();
        }
    }
}
