import java.io.*;
import java.nio.file.*;
import java.util.Arrays;

public class LzmaCompression {

    public static void main(String[] args) throws IOException {
        String filePath = "path/to/input/file";
        String outputDirectory = "path/to/output/directory";

        byte[] fileData = Files.readAllBytes(Paths.get(filePath));
        byte[] compressedData = compressLzma(fileData);
        
        if (compressedData != null) {
            String compressedFilePath = outputDirectory + "/compressed.lzma";
            Files.write(Paths.get(compressedFilePath), compressedData);
        } else {
            System.err.println("Compression failed.");
        }
    }

    private static byte[] loadInputFile(String fileName) throws IOException {
        return Files.readAllBytes(Paths.get(fileName));
    }

    public static byte[] compressLzma(byte[] inputData) {
        int inSize = inputData.length;
        if (inSize == 0) return null;

        net.jpountz.lzma.LZMACompressor compressor = new net.jpountz.lzma.LZMACompressor();
        compressor.setLevel(9);
        compressor.setFb(273);
        compressor.setLc(8);
        compressor.setLp(0);
        compressor.setPb(2);
        compressor.setAlgo(1);
        compressor.setNumThreads(4);

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        try (InputStream inputStream = new ByteArrayInputStream(inputData)) {
            compressor.compress(inputStream, outputStream);
        } catch (IOException e) {
            System.err.println("Compression error: " + e.getMessage());
            return null;
        }

        byte[] compressedData = outputStream.toByteArray();
        return compressedData.length >= inSize ? null : compressedData;
    }
}
