import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.List;

public class Demux {
    private static List<OutputStream> outputStreams = new ArrayList<>();

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("usage: demux leftcmd rightcmd");
            System.exit(1);
        }

        for (int a = 0; a < 2; a++) {
            ProcessBuilder pb = new ProcessBuilder("sh", "-c", args[a]);
            try {
                Process process = pb.start();
                InputStream processIn = process.getInputStream();
                OutputStream processOut = process.getOutputStream();
                outputStreams.add(processOut);
            } catch (IOException e) {
                System.err.println("Error executing command: " + args[a]);
                e.printStackTrace();
                System.exit(1);
            }
        }

        try {
            ByteBuffer buffer = ByteBuffer.allocate(4096).order(ByteOrder.nativeOrder());
            byte[][] out = new byte[2][buffer.capacity() / 2];

            while (true) {
                buffer.clear();
                int bytesRead = System.in.read(buffer.array(), buffer.arrayOffset(), buffer.capacity());
                if (bytesRead < 0) {
                    System.err.println("demux: eof on input");
                    break;
                } else if (bytesRead == 0) {
                    continue;
                }

                buffer.limit(bytesRead);
                for (int i = 0; i < bytesRead; ) {
                    for (int j = 0; j < outputStreams.size(); j++) {
                        short value = buffer.getShort(i);
                        ByteBuffer.wrap(out[j]).order(ByteOrder.nativeOrder()).putShort(i / (outputStreams.size() * 2) * 2, value);
                        i += 2;
                    }
                }

                for (int i = 0; i < outputStreams.size(); i++) {
                    OutputStream os = outputStreams.get(i);
                    int bytesWritten = os.write(out[i], 0, bytesRead / outputStreams.size());
                    os.flush();
                    if (bytesWritten < bytesRead / outputStreams.size()) {
                        System.err.printf("short write: %d < %d%n", bytesWritten, bytesRead / outputStreams.size());
                        System.exit(1);
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading from input or writing to output");
            e.printStackTrace();
            System.exit(1);
        } finally {
            for (OutputStream os : outputStreams) {
                try {
                    os.close();
                } catch (IOException e) {
                    // Ignore
                }
            }
        }
    }
}
